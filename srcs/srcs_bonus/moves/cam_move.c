/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:23:14 by benpicar          #+#    #+#             */
/*   Updated: 2025/05/21 15:35:34 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	ft_check_press_move(mlx_key_data_t keydata)
{
	return (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT);
}

/**
 * @brief	Make a rotation around axe
 * 
 * @param	scene Our big struct
 * @param	theta Angle use to make rotation
 * @param	axe Axe use to make rotation
 * @param	axep A charactere for precise
 * @return	true
 */
static bool	ft_rotat(t_scene *scene, float theta, t_vec3 axe, char axep)
{
	scene->camera.axe = axep;
	scene->camera.direction = ft_rotate_vec3(
			scene->camera.direction,
			axe,
			theta);
	return (true);
}

/**
 * @brief	Make a move of camera
 * 
 * @param	scene Our big struct
 * @param	keydata information of the key pressed
 * @return	true
 * @return	false
 */
static bool	ft_cam_moves_dir(t_scene *scene, mlx_key_data_t keydata)
{
	const float	speed = SPEED * scene->delta_time;

	if (keydata.key == MLX_KEY_W && ft_check_press_move(keydata))
		scene->camera.origin = vec3_add(scene->camera.origin,
				vec3_mul_scalar(scene->camera.up, -speed));
	else if (keydata.key == MLX_KEY_S && ft_check_press_move(keydata))
		scene->camera.origin = vec3_add(scene->camera.origin,
				vec3_mul_scalar(scene->camera.up, speed));
	else if (keydata.key == MLX_KEY_A && ft_check_press_move(keydata))
		scene->camera.origin = vec3_add(scene->camera.origin,
				vec3_mul_scalar(scene->camera.right, -speed));
	else if (keydata.key == MLX_KEY_D && ft_check_press_move(keydata))
		scene->camera.origin = vec3_add(scene->camera.origin,
				vec3_mul_scalar(scene->camera.right, speed));
	else if (keydata.key == MLX_KEY_Q && ft_check_press_move(keydata))
		scene->camera.origin = vec3_add(scene->camera.origin,
				vec3_mul_scalar(scene->camera.forward, speed));
	else if (keydata.key == MLX_KEY_Z && ft_check_press_move(keydata))
		scene->camera.origin = vec3_add(scene->camera.origin,
				vec3_mul_scalar(scene->camera.forward, -speed));
	else
		return (false);
	return (true);
}

/**
 * @brief	Change the selectioned object
 * 
 * @param	scene Our big struct
 * @param	keydata information of the key pressed
 * @return	true 
 * @return	false 
 */
static bool	ft_change(t_scene *scene, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_O && keydata.action == MLX_PRESS)
	{
		scene->on_object = true;
		ft_bzero(scene->actual_name, 10);
		if (scene->actual_object.ac_o->type == CYLINDER)
			ft_memcpy(scene->actual_name, "Cylinder", 9);
		else if (scene->actual_object.ac_o->type == PLANE)
			ft_memcpy(scene->actual_name, "Plane", 6);
		else if (scene->actual_object.ac_o->type == SPHERE)
			ft_memcpy(scene->actual_name, "Sphere", 7);
		else if (scene->actual_object.ac_o->type == CONE)
			ft_memcpy(scene->actual_name, "Cone", 5);
	}
	else if (keydata.key == MLX_KEY_L && keydata.action == MLX_PRESS)
	{
		scene->light_yagami = true;
		ft_bzero(scene->actual_name, 10);
		ft_memcpy(scene->actual_name, "Light", 6);
	}
	return (true);
}

/**
 * @brief	Make a move of camera
 * 
 * @param	scene Our big struct
 * @param	keydata information of the key pressed
 * @return	true 
 * @return	false 
 */
bool	ft_cam_moves(t_scene *scene, mlx_key_data_t keydata)
{
	const float	rotate_speed = ROTATE_SPEED * scene->delta_time;

	if ((keydata.key == MLX_KEY_O || keydata.key == MLX_KEY_L)
		&& keydata.action == MLX_PRESS)
		return (ft_change(scene, keydata));
	else if (keydata.key == MLX_KEY_UP && ft_check_press_move(keydata))
		return (ft_rotat(scene, -rotate_speed, scene->camera.right, 'x'));
	else if (keydata.key == MLX_KEY_DOWN && ft_check_press_move(keydata))
		return (ft_rotat(scene, rotate_speed, scene->camera.right, 'x'));
	else if (keydata.key == MLX_KEY_RIGHT && ft_check_press_move(keydata))
		return (ft_rotat(scene, -rotate_speed, scene->camera.up, 'y'));
	else if (keydata.key == MLX_KEY_LEFT && ft_check_press_move(keydata))
		return (ft_rotat(scene, rotate_speed, scene->camera.up, 'y'));
	else
		return (ft_cam_moves_dir(scene, keydata));
	return (false);
}
