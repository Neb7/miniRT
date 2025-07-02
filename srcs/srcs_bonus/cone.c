/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:39:16 by llemmel           #+#    #+#             */
/*   Updated: 2025/05/22 14:26:26 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

/**
 * @brief	Init coefficients of the cone equation.
 */
static void	init_coeff_cone(const t_ray *ray, const t_cone *cone, \
	float coeff[3])
{
	const t_vec3	co = vec3_sub(ray->origin, cone->pos);
	const float		co_d = vec3_dot(co, cone->orientation);
	const float		d_cod = vec3_dot(ray->direction, cone->orientation);

	coeff[0] = vec3_dot(ray->direction, ray->direction) - 2 * d_cod * d_cod;
	coeff[1] = 2 * (vec3_dot(ray->direction, co) - 2 * d_cod * co_d);
	coeff[2] = vec3_dot(co, co) - 2 * co_d * co_d;
}

/**
 * @brief	Check if the ray hit the core of the cone.
 */
static bool	hit_core_cone(const t_ray *ray, float *closest_t, \
	float t, const t_cone *cone)
{
	t_point	p;
	t_vec3	co_p;
	float	height;
	t_vec3	proj;
	t_vec3	normal;

	if (t > EPSILON && t < *closest_t)
	{
		p = ray_at(ray, t);
		co_p = vec3_sub(p, cone->pos);
		height = vec3_dot(co_p, cone->orientation);
		if (height >= 0 && height <= cone->height)
		{
			proj = vec3_mul_scalar(cone->orientation, height);
			normal = vec3_sub(co_p, vec3_mul_scalar(proj, 2));
			normal = vec3_normalize(normal);
			if (vec3_dot(ray->direction, normal) > 0)
				normal = vec3_mul_scalar(normal, -1);
			*closest_t = t;
			return (true);
		}
	}
	return (false);
}

/**
 * @brief	Check if the ray hit the base of the cone.
 */
static bool	hit_base_cone(const t_ray *ray, float *closest_t, \
	const t_cone *cone)
{
	const t_point	cone_height = \
	vec3_add(cone->pos, vec3_mul_scalar(cone->orientation, cone->height));
	const float		denom = vec3_dot(ray->direction, cone->orientation);
	float			t_cap;
	t_vec3			p_cap;

	if (fabsf(denom) > EPSILON)
	{
		t_cap = \
		vec3_dot(vec3_sub(cone_height, ray->origin), cone->orientation) / denom;
		if (t_cap > EPSILON && t_cap < *closest_t)
		{
			p_cap = ray_at(ray, t_cap);
			if (vec3_squarred_length(vec3_sub(p_cap, cone_height)) \
			<= cone->radius * cone->radius)
			{
				*closest_t = t_cap;
				return (true);
			}
		}
	}
	return (false);
}

/**
 * @brief	Check if the ray hit the cone.
 */
void	ray_hit_cone(const t_ray *ray, const t_cone *cone, \
	const void *obj_addr, t_hit_point *hit_point)
{
	float		coeff[3];
	float		discriminant;
	float		sqrt_discriminant;
	float		t[3];

	t[2] = FLT_MAX;
	*hit_point = (t_hit_point){NULL, -1.0f, (t_point){0, 0, 0}, NULL, 0};
	init_coeff_cone(ray, cone, coeff);
	discriminant = coeff[1] * coeff[1] - 4 * coeff[0] * coeff[2];
	if (discriminant >= 0 && fabsf(coeff[0]) > EPSILON)
	{
		sqrt_discriminant = sqrtf(discriminant);
		t[0] = (-coeff[1] - sqrt_discriminant) / (2 * coeff[0]);
		t[1] = (-coeff[1] + sqrt_discriminant) / (2 * coeff[0]);
		if (hit_core_cone(ray, &t[2], t[0], cone))
			*hit_point = (t_hit_point){(t_ray *)ray, t[0], \
				ray_at(ray, t[0]), (void *)obj_addr, 0};
		if (hit_core_cone(ray, &t[2], t[1], cone))
			*hit_point = (t_hit_point){(t_ray *)ray, t[1], \
				ray_at(ray, t[1]), (void *)obj_addr, 0};
	}
	if (hit_base_cone(ray, &t[2], cone))
		*hit_point = (t_hit_point){(t_ray *)ray, t[2], \
			ray_at(ray, t[2]), (void *)obj_addr, 1};
}

/**
 * @brief	Get the normal of the cone at the hit point.
 * 
 * If the hit type is 1, it means the ray hit the base of the cone,
 * so we return the normal of the base.
 * If the hit type is 0, it means the ray hit the core of the cone, 
 * so we calculate the normal based on the hit point and the cone orientation.
 * 
 * @param	hit_point The hit point of the ray
 * @return	t_vec3 The normal vector of the cone at the hit point
 */
t_vec3	normal_cone(const t_hit_point *hit_point)
{
	const t_cone	*cone = hit_point->object->data;
	t_vec3			co_p;
	float			m;
	t_vec3			proj;
	t_vec3			normal;

	if (hit_point->hit_type == 1)
		return (vec3_mul_scalar(cone->orientation, -1.0f));
	co_p = vec3_sub(hit_point->p, cone->pos);
	m = vec3_dot(co_p, cone->orientation);
	proj = vec3_mul_scalar(cone->orientation, m);
	normal = vec3_sub(co_p, vec3_mul_scalar(proj, 2));
	if (vec3_dot(hit_point->ray->direction, normal) > 0)
		normal = vec3_mul_scalar(normal, -1);
	return (vec3_normalize(normal));
}
