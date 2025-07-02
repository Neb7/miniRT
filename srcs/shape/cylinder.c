/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 09:34:01 by llemmel           #+#    #+#             */
/*   Updated: 2025/05/22 14:26:26 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "camera.h"

void	ray_hit_cylinder(const t_ray *ray, const t_cylinder *cyl, \
	const void *addr, t_hit_point *hit_point)
{
	float		coeff[5];
	t_hit_point	tmp;
	float		t[3];
	float		discriminant;

	tmp = (t_hit_point){NULL, -1.0f, (t_point){0, 0, 0}, NULL, 0};
	init_coeff(ray, cyl, coeff);
	discriminant = coeff[1] * coeff[1] - 4 * coeff[0] * coeff[2];
	if (discriminant >= 0.0f)
	{
		coeff[4] = sqrt(discriminant);
		if (hit_core(coeff, cyl, ray, &t[0]))
			tmp = (t_hit_point){(t_ray *)ray, t[0], \
				ray_at(ray, t[0]), (void *)addr, 0};
	}
	if (hit_bottop(cyl, ray, false, &t[1])
		&& (tmp.t < 0 || t[1] < tmp.t))
		tmp = (t_hit_point){(t_ray *)ray, t[1], \
			ray_at(ray, t[1]), (void *)addr, 2};
	if (hit_bottop(cyl, ray, true, &t[2])
		&& (tmp.t < 0 || t[2] < tmp.t))
		tmp = (t_hit_point){(t_ray *)ray, t[2], \
			ray_at(ray, t[2]), (void *)addr, 1};
	*hit_point = tmp;
}

t_vec3	normal_cylinder(const t_hit_point *hit_point)
{
	const t_cylinder	*cyl = hit_point->object->data;
	t_vec3				pa;
	float				h;
	t_point				c;

	if (hit_point->hit_type == 1)
		return (vec3_mul_scalar(cyl->orientation, -1.0f));
	else if (hit_point->hit_type == 2)
		return (cyl->orientation);
	else
	{
		pa = vec3_sub(hit_point->p, cyl->pos);
		h = vec3_dot(pa, cyl->orientation);
		c = vec3_add(cyl->pos, vec3_mul_scalar(cyl->orientation, h));
		return (vec3_normalize(vec3_sub(hit_point->p, c)));
	}
}

bool	light_in_cylinder(const t_light *light, const t_cylinder *cylinder)
{
	const float		scalar = vec3_dot(vec3_sub(light->origin, cylinder->pos), \
									cylinder->orientation);
	const t_point	projection = vec3_add(cylinder->pos, \
			vec3_mul_scalar(cylinder->orientation, scalar));
	float			h;

	if (vec3_length(vec3_sub(light->origin, projection)) > cylinder->radius)
		return (false);
	h = vec3_dot(vec3_sub(projection, cylinder->pos), cylinder->orientation);
	return (h >= 0.0f && h <= cylinder->height);
}
