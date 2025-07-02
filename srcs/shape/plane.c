/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:03:36 by llemmel           #+#    #+#             */
/*   Updated: 2025/05/22 14:26:26 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	ray_hit_plane(const t_ray *ray, const t_plane *plane, \
						const void *obj_addr, t_hit_point *hit_point)
{
	float	t;
	float	nom;
	float	denom;

	nom = -1.0f * vec3_dot(vec3_sub(ray->origin, plane->origin), plane->normal);
	if (nom == 0)
	{
		*hit_point = (t_hit_point){NULL, -1.0f, (t_point){0, 0, 0}, NULL, 0};
		return ;
	}
	denom = vec3_dot(ray->direction, plane->normal);
	if (denom == 0)
	{
		*hit_point = (t_hit_point){NULL, -1.0f, (t_point){0, 0, 0}, NULL, 0};
		return ;
	}
	t = nom / denom;
	if (t < 0 || t < EPSILON)
	{
		*hit_point = (t_hit_point){NULL, -1.0f, (t_point){0, 0, 0}, NULL, 0};
		return ;
	}
	*hit_point = ((t_hit_point){(t_ray *)ray, t, \
		ray_at(ray, t), (void *)obj_addr, 0});
}

t_vec3	normal_plane(const t_hit_point *hit_point)
{
	return (((t_plane *)hit_point->object->data)->normal);
}

bool	light_in_plane(const t_light *light, const t_plane *plane)
{
	const t_vec3	pl = vec3_sub(light->origin, plane->origin);

	return (vec3_dot(pl, plane->normal) == 0.0f);
}
