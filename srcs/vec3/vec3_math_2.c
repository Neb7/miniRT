/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_math_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:48:12 by llemmel           #+#    #+#             */
/*   Updated: 2025/05/16 18:43:56 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

inline t_vec3	vec3_reflect(t_vec3 a, t_vec3 normal)
{
	return (vec3_sub(a, \
		vec3_mul_scalar(vec3_mul_scalar(normal, vec3_dot(a, normal)), 2.0f)));
}
