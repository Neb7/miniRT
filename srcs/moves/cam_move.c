/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:23:14 by benpicar          #+#    #+#             */
/*   Updated: 2025/05/21 15:37:21 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief	Make a rotation around axe
 * 
 * @param	scene Our big struct
 * @param	theta Angle use to make rotation
 * @param	axe Axe use to make rotation
 * @param	axep A charactere for precise
 * @return	true 
 * @return	false 
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
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		scene->camera.origin = vec3_add(scene->camera.origin,
				vec3_mul_scalar(scene->camera.up, -SPEED));
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		scene->camera.origin = vec3_add(scene->camera.origin,
				vec3_mul_scalar(scene->camera.up, SPEED));
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		scene->camera.origin = vec3_add(scene->camera.origin,
				vec3_mul_scalar(scene->camera.right, -SPEED));
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		scene->camera.origin = vec3_add(scene->camera.origin,
				vec3_mul_scalar(scene->camera.right, SPEED));
	else if (keydata.key == MLX_KEY_Q && keydata.action == MLX_PRESS)
		scene->camera.origin = vec3_add(scene->camera.origin,
				vec3_mul_scalar(scene->camera.forward, SPEED));
	else if (keydata.key == MLX_KEY_Z && keydata.action == MLX_PRESS)
		scene->camera.origin = vec3_add(scene->camera.origin,
				vec3_mul_scalar(scene->camera.forward, -SPEED));
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
 * @brief	Make a rotation of the camera or change the selectioned object
 * 
 * @param	scene Our big struct
 * @param	keydata information of the key pressed
 * @return	true 
 * @return	false 
 */
bool	ft_cam_moves(t_scene *scene, mlx_key_data_t keydata)
{
	if ((keydata.key == MLX_KEY_O || keydata.key == MLX_KEY_L)
		&& keydata.action == MLX_PRESS)
		return (ft_change(scene, keydata));
	else if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		return (ft_rotat(scene, -ROTATE_SPEED, scene->camera.right, 'x'));
	else if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		return (ft_rotat(scene, ROTATE_SPEED, scene->camera.right, 'x'));
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		return (ft_rotat(scene, -ROTATE_SPEED, scene->camera.up, 'y'));
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		return (ft_rotat(scene, ROTATE_SPEED, scene->camera.up, 'y'));
	else
		return (ft_cam_moves_dir(scene, keydata));
	return (false);
}
