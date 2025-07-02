/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_operator_scalar.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:57:56 by llemmel           #+#    #+#             */
/*   Updated: 2025/05/15 16:54:46 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

inline t_vec3	vec3_add_scalar(t_vec3 a, float scalar)
{
	return ((t_vec3){
		.x = a.x + scalar,
		.y = a.y + scalar,
		.z = a.z + scalar
	});
}

inline t_vec3	vec3_sub_scalar(t_vec3 a, float scalar)
{
	return ((t_vec3){
		.x = a.x - scalar,
		.y = a.y - scalar,
		.z = a.z - scalar
	});
}

inline t_vec3	vec3_mul_scalar(t_vec3 a, float scalar)
{
	return ((t_vec3){
		.x = a.x * scalar,
		.y = a.y * scalar,
		.z = a.z * scalar
	});
}

inline t_vec3	vec3_div_scalar(t_vec3 a, float scalar)
{
	return ((t_vec3){
		.x = a.x / scalar,
		.y = a.y / scalar,
		.z = a.z / scalar
	});
}
