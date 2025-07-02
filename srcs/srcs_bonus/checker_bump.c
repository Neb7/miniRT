/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bump.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:15:34 by llemmel           #+#    #+#             */
/*   Updated: 2025/05/21 13:19:34 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

#define SCALE 10
#define NOISE_DENSITY 20.0f
#define BUMP_STRENGHT 0.2f

/**
 * @brief	Get the color of the checkerboard pattern on a plane.
 * 
 * @param	hit_point The hit point on the plane.
 * @return	t_vec3 The color of the checkerboard pattern at the hit point.
 */
t_vec3	checkerboard_plane(const t_hit_point *hit_point)
{
	const t_plane	*plane = hit_point->object->data;
	const t_vec3	local = vec3_sub(hit_point->p, plane->origin);
	float			coord[2];
	t_vec3			uv[2];
	t_vec3			ref;

	if (fabsf(plane->normal.y) < 0.99)
		ref = (t_vec3){0, 1, 0};
	else
		ref = (t_vec3){1, 0, 0};
	uv[0] = vec3_normalize(vec3_cross(ref, plane->normal));
	uv[1] = vec3_normalize(vec3_cross(plane->normal, uv[0]));
	coord[0] = vec3_dot(local, uv[0]);
	coord[1] = vec3_dot(local, uv[1]);
	if (((int)floorf(coord[0] / SCALE) + (int)floorf(coord[1] / SCALE)) % 2)
		return ((t_vec3){1 - plane->color.x, \
			1 - plane->color.y, 1 - plane->color.z});
	else
		return (plane->color);
}

inline float	perlin_noise_interpolation(float t)
{
	return (t * t * t * (t * (t * 6 - 15) + 10));
}

inline float	lerp(float a, float b, float t)
{
	return (a + t * (b - a));
}

/**
 * @brief	Create a bump map texture on a sphere using Perlin noise.
 * 
 * @param	hit_point The hit point on the sphere.
 * @return	t_vec3 The normal vector of the bump map at the hit point.
 */
t_vec3	bump_map_sphere(const t_hit_point *hit_point)
{
	const t_sphere	*sphere = hit_point->object->data;
	const t_vec3	p = vec3_mul_scalar(vec3_div_scalar(\
		vec3_sub(hit_point->p, sphere->origin), sphere->radius), NOISE_DENSITY);
	const t_vec3	normal = vec3_normalize(\
		vec3_sub(hit_point->p, sphere->origin));
	t_vec3			noise_grad;
	t_vec3			bump_normal;

	noise_grad.x = perlin_noise_at_point((t_vec3){p.x + EPSILON, p.y, p.z}) - \
					perlin_noise_at_point((t_vec3){p.x - EPSILON, p.y, p.z});
	noise_grad.y = perlin_noise_at_point((t_vec3){p.x, p.y + EPSILON, p.z}) - \
					perlin_noise_at_point((t_vec3){p.x, p.y - EPSILON, p.z});
	noise_grad.z = perlin_noise_at_point((t_vec3){p.x, p.y, p.z + EPSILON}) - \
					perlin_noise_at_point((t_vec3){p.x, p.y, p.z - EPSILON});
	noise_grad = vec3_normalize(noise_grad);
	bump_normal = vec3_add(normal, vec3_mul_scalar(noise_grad, BUMP_STRENGHT));
	return (vec3_normalize(bump_normal));
}
