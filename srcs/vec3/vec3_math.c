/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_math.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:48:12 by llemmel           #+#    #+#             */
/*   Updated: 2025/05/16 18:44:03 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

inline float	vec3_length(t_vec3 a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

inline float	vec3_squarred_length(t_vec3 a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z);
}

inline t_vec3	vec3_normalize(t_vec3 a)
{
	return (vec3_div_scalar(a, sqrt(a.x * a.x + a.y * a.y + a.z * a.z)));
}

inline float	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

inline t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){
		.x = a.y * b.z - a.z * b.y,
		.y = a.z * b.x - a.x * b.z,
		.z = a.x * b.y - a.y * b.x
	});
}
