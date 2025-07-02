/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:23:52 by benpicar          #+#    #+#             */
/*   Updated: 2025/05/19 19:26:36 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief	Check if the key is pressed or repeat
 * 
 * @param	scene Our big struct
 */
static void	ft_change_light(t_scene *scene)
{
	int	i_tmp;

	if (scene->actual_light.i + 1 < scene->lights->index)
		(scene->actual_light.i)++;
	else
		scene->actual_light.i = 0;
	i_tmp = scene->actual_light.i;
	scene->actual_light.ac_l = &((t_light *)scene->lights->buf)[i_tmp];
	scene->actual_light.ac_l->check = false;
}

/**
 * @brief	Function for handle the interaction when we press a key
 * 
 * @param	scene Our big struct
 * @param	keydata information of the key pressed
 */
static void	ft_change_to_other(t_scene *scene, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_O && keydata.action == MLX_PRESS)
	{
		scene->on_object = true;
		scene->light_yagami = false;
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
		scene->light_yagami = false;
		ft_bzero(scene->actual_name, 10);
		ft_memcpy(scene->actual_name, "Camera", 7);
	}
}

/**
 * @brief	Function for handle the interaction when we press a key
 * 
 * @param	scene Our big struct
 * @param	keydata information of the key pressed
 * @return	true
 * @return	false
 */
bool	ft_light_moves(t_scene *scene, mlx_key_data_t keydata)
{
	if ((keydata.key == MLX_KEY_O || keydata.key == MLX_KEY_L)
		&& keydata.action == MLX_PRESS)
		ft_change_to_other(scene, keydata);
	else if (keydata.key == MLX_KEY_TAB && ft_check_press_move(keydata))
		ft_change_light(scene);
	else if (keydata.key == MLX_KEY_W && ft_check_press_move(keydata))
		scene->actual_light.ac_l->origin.y += 1;
	else if (keydata.key == MLX_KEY_S && ft_check_press_move(keydata))
		scene->actual_light.ac_l->origin.y -= 1;
	else if (keydata.key == MLX_KEY_A && ft_check_press_move(keydata))
		scene->actual_light.ac_l->origin.x += 1;
	else if (keydata.key == MLX_KEY_D && ft_check_press_move(keydata))
		scene->actual_light.ac_l->origin.x -= 1;
	else if (keydata.key == MLX_KEY_Q && ft_check_press_move(keydata))
		scene->actual_light.ac_l->origin.z -= 1;
	else if (keydata.key == MLX_KEY_Z && ft_check_press_move(keydata))
		scene->actual_light.ac_l->origin.z += 1;
	else
		return (false);
	return (true);
}
