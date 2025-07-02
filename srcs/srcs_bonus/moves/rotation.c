/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:29:40 by benpicar          #+#    #+#             */
/*   Updated: 2025/05/19 15:38:21 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// t_vec3	ft_rotate_y(t_vec3 v, float theta)
// {
// 	float	cos_theta;
// 	float	sin_theta;
// 	t_vec3	result;

// 	cos_theta = cosf(theta);
// 	sin_theta = sinf(theta);
// 	result.x = v.x * cos_theta + v.z * sin_theta;
// 	result.y = v.y;
// 	result.z = -v.x * sin_theta + v.z * cos_theta;
// 	return (result);
// }

/**
 * @brief	Rotate a vector around the x-axis by a given angle
 * 
 * @param	v The vector to rotate
 * @param	theta The angle in radians
 * @return	The rotated vector
 */
t_vec3	ft_rotate_x(t_vec3 v, float theta)
{
	float	cos_theta;
	float	sin_theta;
	t_vec3	result;

	cos_theta = cosf(theta);
	sin_theta = sinf(theta);
	result.x = v.x;
	result.y = v.y * cos_theta - v.z * sin_theta;
	result.z = v.y * sin_theta + v.z * cos_theta;
	return (result);
}

/**
 * @brief	Rotate a vector around the Z axis by a given angle
 * 
 * @param	v The vector to rotate
 * @param	theta The angle in radians
 * @return	The rotated vector
 */
t_vec3	ft_rotate_z(t_vec3 v, float theta)
{
	float	cos_theta;
	float	sin_theta;
	t_vec3	result;

	cos_theta = cosf(theta);
	sin_theta = sinf(theta);
	result.x = v.x * cos_theta - v.y * sin_theta;
	result.y = v.x * sin_theta + v.y * cos_theta;
	result.z = v.z;
	return (result);
}

/**
 * @brief	Rotate a vector around an arbitrary axis by a given angle
 * 
 * @param	v The vector to rotate
 * @param	axis The axis of rotation
 * @param	angle_deg The angle in degrees
 * @return	The rotated vector
 */
t_vec3	ft_rotate_vec3(t_vec3 v, t_vec3 axis, float angle_deg)
{
	float	angle_rad;
	float	cos_theta;
	float	sin_theta;
	t_vec3	term[3];

	angle_rad = angle_deg * (M_PI / 180.0f);
	axis = vec3_normalize(axis);
	cos_theta = cosf(angle_rad);
	sin_theta = sinf(angle_rad);
	term[0] = vec3_mul_scalar(v, cos_theta);
	term[1] = vec3_mul_scalar(vec3_cross(axis, v), sin_theta);
	term[2] = vec3_mul_scalar(axis, vec3_dot(axis, v) * (1.0f - cos_theta));
	return (vec3_add(vec3_add(term[0], term[1]), term[2]));
}

/**
 * @brief	Make a rotation of the plane
 * 
 * @param	pl The plane
 * @param	theta Angle use to make rotation
 * @param	axe Axe use to make rotation
 * @return	true
 */
bool	ft_rotate_plane(t_plane *pl, float theta, t_vec3 axe)
{
	pl->normal = ft_rotate_vec3(
			pl->normal,
			axe,
			theta);
	return (true);
}

/**
 * @brief	Make a rotation of the cylinder
 * 
 * @param	cy The cylinder
 * @param	theta Angle use to make rotation
 * @param	axe Axe use to make rotation
 * @return	true
 */
bool	ft_rotate_cylinder(t_cylinder *cy, float theta, t_vec3 axe)
{
	cy->orientation = ft_rotate_vec3(
			cy->orientation,
			axe,
			theta);
	return (true);
}
