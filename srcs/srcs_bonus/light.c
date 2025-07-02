/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:34:18 by llemmel           #+#    #+#             */
/*   Updated: 2025/05/20 16:20:17 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
#include "../includes/camera.h"

/**
 * @brief	Check if the light is in the object
 * 
 * @param	scene The scene to check
 * @param	light The light to check
 * @return	true if the light is in the object, false otherwise
 */
static bool	light_in_object(const t_scene *scene, const t_light *light)
{
	t_object	*object;
	size_t		i;

	i = 0;
	while (i < scene->objects->index)
	{
		object = &((t_object *)scene->objects->buf)[i];
		if (object->type == SPHERE && light_in_sphere(light, object->data))
			return (true);
		else if (object->type == PLANE && light_in_plane(light, object->data))
			return (true);
		else if (object->type == CYLINDER && \
			light_in_cylinder(light, object->data))
			return (true);
		i++;
	}
	return (false);
}

/**
 * @brief	Get the final color of the pixel.
 * It will calculate the color based on the light and the hit point.
 * It will also add the specular color and the diffuse color.
 * 
 * @param	color The color
 * @param	hit_point The hit point
 * @param	light The light
 * @param	ray The ray
 * @return	t_vec3 The final color
 */
static t_vec3	final_color(const t_vec3 color, const t_hit_point *hit_point, \
	const t_light *light, const t_ray *ray)
{
	const t_vec3	normal = get_normal(hit_point);
	const t_vec3	reflect = vec3_reflect(ray->direction, normal);
	t_vec3			light_contrib;
	t_vec3			spec_contrib;
	float			factor[2];

	factor[0] = fmax(0.0f, \
		fabs(vec3_dot(normal, ray->direction))) * light->brightness;
	factor[1] = powf(fmax(vec3_dot(reflect, hit_point->ray->direction), 0.0f), \
					SHININESS);
	light_contrib = vec3_mul(get_object_color_hit(hit_point), \
								vec3_mul_scalar(light->color, factor[0]));
	spec_contrib = vec3_mul_scalar(light->color, factor[1] * SPEC_STRENGHT);
	return (vec3_add(color, vec3_add(light_contrib, spec_contrib)));
}

/**
 * @brief	Check if ray and hit point are in the same direction
 * 
 * @param	hit_point Hit point
 * @param	ray Ray
 * @return	true if they are in the same direction, false otherwise 
 */
static bool	check_sens(const t_hit_point *hit_point, const t_ray *ray)
{
	const float	a = vec3_dot(get_normal(hit_point), hit_point->ray->direction);
	const float	b = vec3_dot(get_normal(hit_point), ray->direction);

	if ((a < -EPSILON && b < -EPSILON) || (a > EPSILON && b > EPSILON))
		return (true);
	return (false);
}

/**
 * @brief	Utils function to initialize the ray and the light distance
 */
static void	init_ray_light(t_ray *ray, const t_light *light, \
	float *light_dist, const t_hit_point *hit)
{
	ray->origin = vec3_add(hit->p, \
		vec3_mul_scalar(get_normal(hit), EPSILON));
	ray->direction = vec3_sub(light->origin, ray->origin);
	*light_dist = vec3_length(ray->direction);
	ray->direction = vec3_normalize(ray->direction);
}

/**
 * @brief	Calculate the light color of the hit point.
 * It will iterate through all the lights in the scene
 * and calculate the color based on the light and the hit point.
 * 
 * @param	scene The scene to check
 * @param	hit_point The hit point to check
 * @return	t_vec3 The color calculated
 */
t_vec3	calc_light(const t_scene *scene, const t_hit_point *hit_point)
{
	t_light				*light;
	int					i;
	t_hit_point			hit_point_2;
	t_ray				ray;
	t_vec3				colors[2];

	i = -1;
	colors[0] = (t_vec3){0, 0, 0};
	while (++i < (int)scene->lights->index)
	{
		light = &((t_light *)scene->lights->buf)[i];
		colors[1] = vec3_mul(get_object_color_hit(hit_point), \
	vec3_mul_scalar(scene->ambiant_ligth.color, scene->ambiant_ligth.ratio));
		init_ray_light(&ray, light, &hit_point_2.t, hit_point);
		if (light_in_object(scene, light) || check_sens(hit_point, &ray))
		{
			colors[0] = vec3_add(colors[0], colors[1]);
			continue ;
		}
		get_closest_hit(&ray, scene->objects, &hit_point_2, hit_point->object);
		if (!hit_point_2.object)
			colors[1] = final_color(colors[1], hit_point, light, &ray);
		colors[0] = vec3_add(colors[0], colors[1]);
	}
	return (colors[0]);
}
