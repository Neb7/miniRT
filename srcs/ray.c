/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:34:27 by llemmel           #+#    #+#             */
/*   Updated: 2025/05/19 16:29:53 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "camera.h"

t_ray	generate_ray(const t_camera *camera, const float px, const float py)
{
	t_ray	ray;
	t_point	tmp;
	t_point	p;
	float	x;
	float	y;

	x = ((px / camera->win_size[0]) * 2 - 1);
	y = ((py / camera->win_size[1]) * 2 - 1);
	tmp = vec3_add(\
			vec3_mul_scalar(camera->u, x), \
			vec3_mul_scalar(camera->v, y) \
		);
	p = vec3_add(camera->center, tmp);
	ray.origin = camera->origin;
	ray.direction = vec3_normalize(vec3_sub(p, ray.origin));
	return (ray);
}

t_point	ray_at(const t_ray *ray, const float t)
{
	return ((t_point){
		.x = ray->origin.x + t * ray->direction.x,
		.y = ray->origin.y + t * ray->direction.y,
		.z = ray->origin.z + t * ray->direction.z
	});
}
