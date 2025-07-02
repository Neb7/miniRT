/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_operator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:52:49 by llemmel           #+#    #+#             */
/*   Updated: 2025/04/29 17:53:17 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

inline t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){
		.x = a.x + b.x,
		.y = a.y + b.y,
		.z = a.z + b.z
	});
}

inline t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){
		.x = a.x - b.x,
		.y = a.y - b.y,
		.z = a.z - b.z
	});
}

inline t_vec3	vec3_mul(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){
		.x = a.x * b.x,
		.y = a.y * b.y,
		.z = a.z * b.z
	});
}

inline t_vec3	vec3_div(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){
		.x = a.x / b.x,
		.y = a.y / b.y,
		.z = a.z / b.z
	});
}
