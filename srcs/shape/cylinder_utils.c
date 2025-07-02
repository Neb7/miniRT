/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:55:59 by llemmel           #+#    #+#             */
/*   Updated: 2025/05/21 17:57:44 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	hit_core(float coeff[5], const t_cylinder *cyl, \
	const t_ray *ray, float *t_out)
{
	const float	t = fmin((-coeff[1] - coeff[4]) / (2.0f * coeff[0]), \
					(-coeff[1] + coeff[4]) / (2.0f * coeff[0]));
	float		proj_len;

	if (t < EPSILON)
		return (false);
	proj_len = vec3_dot(vec3_sub(ray_at(ray, t), cyl->pos), cyl->orientation);
	if (proj_len >= 0.0f && proj_len <= cyl->height)
	{
		*t_out = t;
		return (true);
	}
	return (false);
}

bool	hit_bottop(const t_cylinder *cyl, const t_ray *ray, \
	bool bottom, float *t_out)
{
	t_point	cap_center;
	float	denom;
	float	t;
	t_vec3	diff;

	if (bottom)
		cap_center = cyl->pos;
	else
		cap_center = vec3_add(cyl->pos, \
			vec3_mul_scalar(cyl->orientation, cyl->height));
	denom = vec3_dot(ray->direction, cyl->orientation);
	if (fabs(denom) < EPSILON)
		return (false);
	t = vec3_dot(vec3_sub(cap_center, ray->origin), cyl->orientation) / denom;
	if (t < EPSILON)
		return (false);
	diff = vec3_sub(ray_at(ray, t), cap_center);
	if (vec3_dot(diff, diff) <= cyl->radius * cyl->radius)
	{
		*t_out = t;
		return (true);
	}
	return (false);
}

void	init_coeff(const t_ray *ray, const t_cylinder *cyl, float coeff[5])
{
	const t_vec3	oc = vec3_sub(ray->origin, cyl->pos);
	const t_vec3	d = vec3_sub(ray->direction, \
		vec3_mul_scalar(cyl->orientation, \
						vec3_dot(ray->direction, cyl->orientation)));
	const t_vec3	delta_p = vec3_sub(oc, \
		vec3_mul_scalar(cyl->orientation, vec3_dot(oc, cyl->orientation)));

	coeff[0] = vec3_dot(d, d);
	coeff[1] = 2.0f * vec3_dot(d, delta_p);
	coeff[2] = vec3_dot(delta_p, delta_p) - cyl->radius * cyl->radius;
}
