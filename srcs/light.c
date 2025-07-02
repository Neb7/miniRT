/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:34:18 by llemmel           #+#    #+#             */
/*   Updated: 2025/05/19 18:12:31 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
#include "../includes/camera.h"

static bool	light_in_object(const t_scene *scene)
{
	t_object		*obj;
	t_light			light;
	size_t			i;

	i = 0;
	light = ((t_light *)scene->lights->buf)[0];
	scene->actual_light.ac_l->check = true;
	while (i < scene->objects->index)
	{
		obj = &((t_object *)scene->objects->buf)[i];
		if (obj->type == SPHERE && light_in_sphere(&light, obj->data))
			return (true);
		else if (obj->type == PLANE && light_in_plane(&light, obj->data))
			return (true);
		else if (obj->type == CYLINDER && light_in_cylinder(&light, obj->data))
			return (true);
		i++;
	}
	return (false);
}

static t_vec3	final_color(t_vec3 color, const t_hit_point *hit_point, \
	const t_light *light, const t_ray *ray)
{
	const t_vec3	normal = get_normal(hit_point);
	t_vec3			light_contrib;
	t_vec3			spec_contrib;
	t_vec3			reflect;
	float			factor[2];

	reflect = vec3_reflect(ray->direction, normal);
	reflect = vec3_normalize(reflect);
	factor[0] = fmax(0.0f, \
		fabs(vec3_dot(normal, ray->direction))) * light->brightness;
	factor[1] = powf(fmax(vec3_dot(reflect, hit_point->ray->direction), 0.0f), \
					SHININESS);
	light_contrib = vec3_mul(get_object_color(hit_point->object), \
						vec3_mul_scalar(light->color, factor[0]));
	spec_contrib = vec3_mul_scalar(light->color, factor[1] * SPEC_STRENGHT);
	return (vec3_add(color, vec3_add(light_contrib, spec_contrib)));
}

static bool	check_sens(const t_hit_point *hit_point, const t_ray *ray)
{
	float	a;
	float	b;

	a = vec3_dot(get_normal(hit_point), hit_point->ray->direction);
	b = vec3_dot(get_normal(hit_point), ray->direction);
	if ((a < -EPSILON && b < -EPSILON) || (a > EPSILON && b > EPSILON))
		return (true);
	return (false);
}

static void	init_ray_light(t_ray *ray, const t_light *light, \
	float *light_dist, const t_hit_point *hit)
{
	ray->origin = vec3_add(hit->p, \
		vec3_mul_scalar(get_normal(hit), EPSILON));
	ray->direction = vec3_sub(light->origin, ray->origin);
	*light_dist = vec3_length(ray->direction);
	ray->direction = vec3_normalize(ray->direction);
}

t_vec3	calc_light(const t_scene *scene, const t_hit_point *hit_point)
{
	static bool			light_hide_in_object = false;
	const t_light		*light = &((t_light *)scene->lights->buf)[0];
	t_hit_point			hit_point_2;
	t_ray				ray;
	t_vec3				color;

	color = get_object_color(hit_point->object);
	color = vec3_mul(color, vec3_mul_scalar(scene->ambiant_ligth.color, \
					scene->ambiant_ligth.ratio));
	if (!light->check)
		light_hide_in_object = light_in_object(scene);
	if (light_hide_in_object)
		return (color);
	init_ray_light(&ray, light, &hit_point_2.t, hit_point);
	if (check_sens(hit_point, &ray))
		return (color);
	get_closest_hit(&ray, scene->objects, &hit_point_2, hit_point->object);
	if (!hit_point_2.object)
		color = final_color(color, hit_point, light, &ray);
	return (color);
}
