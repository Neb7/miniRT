/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:01:12 by llemmel           #+#    #+#             */
/*   Updated: 2025/05/22 14:27:29 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "camera.h"

/**
 * @brief	Check if a ray hit a sphere
 * 
 * The function check if the ray hit the sphere. If it hit, the function
 * fill the hit_point with all the information about the hit. Otherwise,
 * the hit_point is set to MISS hit point
 * 
 * @param	ray			The ray to test
 * @param	sphere		The sphere to test
 * @param	obj_addr	The adress of the sphere object
 * @param	hit_point	The hit point, if ray it the sphere, hit_point contain 
 * 						all information about the hit.	
 */
void	ray_hit_sphere(const t_ray *ray, const t_sphere *sphere, \
						const void *obj_addr, t_hit_point *hit_point)
{
	float				t;
	float				coeff[2];
	float				discriminant;
	const t_vec3		oc = vec3_sub(ray->origin, sphere->origin);

	coeff[0] = -2.0f * \
		(oc.x * ray->direction.x + oc.y * ray->direction.y + \
			oc.z * ray->direction.z);
	coeff[1] = -4.0f * \
		((oc.x * oc.x + oc.y * oc.y + oc.z * oc.z) - sphere->squarred_radius);
	discriminant = coeff[0] * coeff[0] + coeff[1];
	if (discriminant < 0)
	{
		*hit_point = (t_hit_point){NULL, -1.0f, (t_point){0, 0, 0}, NULL, 0};
		return ;
	}
	t = (coeff[0] - sqrt(discriminant)) * 0.5f;
	if (t > EPSILON)
		*hit_point = (t_hit_point){(t_ray *)ray, t, \
			ray_at(ray, t), (void *)obj_addr, 0};
	else
		*hit_point = (t_hit_point){NULL, -1.0f, (t_point){0, 0, 0}, NULL, 0};
}

/**
 * @brief	Get the normal of a sphere at a hit point
 * 
 * @param	hit_point	The hit point
 * @return	t_vec3		The normal of the sphere at the hit point
 */
t_vec3	normal_sphere(const t_hit_point *hit_point)
{
	if (((t_sphere *)hit_point->object->data)->bump)
		return (bump_map_sphere(hit_point));
	return (vec3_normalize(vec3_sub(
				hit_point->p,
				((t_sphere *)hit_point->object->data)->origin
			)));
}

/**
 * @brief	Check if a light is in a sphere
 * 
 * @param	light	The light to check
 * @param	sphere	The sphere to check
 * @return	true if the light is in the sphere otherwise false 
 */
bool	light_in_sphere(const t_light *light, const t_sphere *sphere)
{
	t_vec3	ol;

	ol = vec3_sub(light->origin, sphere->origin);
	return (vec3_squarred_length(ol) < sphere->squarred_radius);
}
