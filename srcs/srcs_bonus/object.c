/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:55:52 by llemmel           #+#    #+#             */
/*   Updated: 2025/05/22 14:26:39 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

/**
 * @brief	Get the normal object
 * 
 * @param	hit_point The hit point containing the object
 * @return	t_vec3 The normal vector of the object
 */
t_vec3	get_normal(const t_hit_point *hit_point)
{
	if (hit_point->object->type == SPHERE)
		return (normal_sphere(hit_point));
	else if (hit_point->object->type == PLANE)
		return (normal_plane(hit_point));
	else if (hit_point->object->type == CYLINDER)
		return (normal_cylinder(hit_point));
	else if (hit_point->object->type == CONE)
		return (normal_cone(hit_point));
	else
		return (hit_point->p);
}

/**
 * @brief	Check if the ray hit the object and get the hit point.
 * 
 * @param	ray ray to test
 * @param	object object to test
 * @param	hit_point hit point to fill
 */
static void	ray_hit_object(const t_ray *ray, const t_object *object, \
	t_hit_point *hit_point)
{
	if (object->type == SPHERE)
		ray_hit_sphere(ray, object->data, object, hit_point);
	else if (object->type == PLANE)
		ray_hit_plane(ray, object->data, object, hit_point);
	else if (object->type == CYLINDER)
		ray_hit_cylinder(ray, object->data, object, hit_point);
	else if (object->type == CONE)
		ray_hit_cone(ray, object->data, object, hit_point);
	else
		*hit_point = (t_hit_point){NULL, -1.0f, (t_point){0, 0, 0}, NULL, 0};
}

/**
 * @brief	Get the closest hit point in the scene.
 * 
 * It will iterate through all the objects 
 * in the scene and get the closest hit point.
 */
void	get_closest_hit(const t_ray *ray, const t_vector *objects, \
	t_hit_point *closest_hit, const t_object *ignore)
{
	size_t		i;
	t_hit_point	hit_point;
	float		light_dist;

	i = 0;
	light_dist = closest_hit->t;
	*closest_hit = (t_hit_point){NULL, FLT_MAX, (t_point){0, 0, 0}, NULL, 0};
	while (i < objects->index)
	{
		ray_hit_object(ray, &((t_object *)objects->buf)[i], &hit_point);
		if ((hit_point.t > EPSILON && hit_point.t < light_dist) \
			&& hit_point.t < closest_hit->t && hit_point.object != ignore)
			*closest_hit = hit_point;
		else if (!ignore && (hit_point.t > EPSILON && hit_point.t < light_dist) \
			&& hit_point.t < closest_hit->t)
			*closest_hit = hit_point;
		++i;
	}
	if (closest_hit->t == FLT_MAX)
		*closest_hit = (t_hit_point){NULL, -1.0f, (t_point){0, 0, 0}, NULL, 0};
}

/**
 * @brief	Get the object color of the object in the hit_point.
 * 
 * @param	hit The hit point containing the object
 * @return	t_vec3 The color of the object
 */
t_vec3	get_object_color_hit(const t_hit_point *hit)
{
	if (hit->object->type == SPHERE)
		return (((t_sphere *)hit->object->data)->color);
	else if (hit->object->type == PLANE \
		&& !((t_plane *)hit->object->data)->checkerboard)
		return ((((t_plane *)hit->object->data)->color));
	else if (hit->object->type == PLANE \
		&& ((t_plane *)hit->object->data)->checkerboard)
		return (checkerboard_plane(hit));
	else if (hit->object->type == CYLINDER)
		return ((((t_cylinder *)hit->object->data)->color));
	else if (hit->object->type == CONE)
		return ((((t_cone *)hit->object->data)->color));
	else
		return ((t_vec3){0, 0, 0});
}
