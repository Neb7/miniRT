/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:23:59 by benpicar          #+#    #+#             */
/*   Updated: 2025/05/19 14:38:10 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief	Change the selectioned object
 * 
 * @param	scene Our big struct
 * @param	keydata information of the key pressed
 * @return	true
 * @return	false
 */
static void	ft_change_object(t_scene *scene)
{
	int	i_tmp;

	if (scene->actual_object.i + 1 < scene->objects->index)
		(scene->actual_object.i)++;
	else
		scene->actual_object.i = 0;
	i_tmp = scene->actual_object.i;
	scene->actual_object.ac_o = &((t_object *)scene->objects->buf)[i_tmp];
	ft_bzero(scene->actual_name, 10);
	if (scene->actual_object.ac_o->type == CYLINDER)
		ft_memcpy(scene->actual_name, "Cylinder", 9);
	else if (scene->actual_object.ac_o->type == PLANE)
		ft_memcpy(scene->actual_name, "Plane", 6);
	else if (scene->actual_object.ac_o->type == SPHERE)
		ft_memcpy(scene->actual_name, "Sphere", 7);
}

/**
 * @brief	Make a move of the plane
 * 
 * @param	scene Our big struct
 * @param	keydata information of the key pressed
 * @param	pl The plane
 * @return	true
 * @return	false
 */
static bool	ft_move_plane(t_scene *scene, mlx_key_data_t keydata, t_plane *pl)
{
	pl = scene->actual_object.ac_o->data;
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		ft_rotate_plane(pl, -9.0f, pl->right);
	else if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		ft_rotate_plane(pl, 9.0f, pl->right);
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		ft_rotate_plane(pl, -9.0f, pl->up);
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		ft_rotate_plane(pl, 9.0f, pl->up);
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		pl->origin.y += 1;
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		pl->origin.y -= 1;
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		pl->origin.x += 1;
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		pl->origin.x -= 1;
	else if (keydata.key == MLX_KEY_Q && keydata.action == MLX_PRESS)
		pl->origin.z -= 1;
	else if (keydata.key == MLX_KEY_Z && keydata.action == MLX_PRESS)
		pl->origin.z += 1;
	else
		return (false);
	return (true);
}

/**
 * @brief	Make a move of the sphere
 * 
 * @param	scene Our big struct
 * @param	keydata information of the key pressed
 * @param	sp The sphere
 * @return	true
 * @return	false
 */
static bool	ft_move_sphere(t_scene *scene, mlx_key_data_t keydata)
{
	t_sphere	*sp;

	sp = scene->actual_object.ac_o->data;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		sp->origin.y += 1;
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		sp->origin.y -= 1;
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		sp->origin.x += 1;
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		sp->origin.x -= 1;
	else if (keydata.key == MLX_KEY_Q && keydata.action == MLX_PRESS)
		sp->origin.z -= 1;
	else if (keydata.key == MLX_KEY_Z && keydata.action == MLX_PRESS)
		sp->origin.z += 1;
	else
		return (false);
	return (true);
}

/**
 * @brief	Make a move of the cylinder
 * 
 * @param	scene Our big struct
 * @param	keydata information of the key pressed
 * @param	cy The cylinder
 * @return	true
 * @return	false
 */
static bool	ft_move_cylinder(t_scene *scene, mlx_key_data_t keydata,
	t_cylinder *cy)
{
	cy = scene->actual_object.ac_o->data;
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		cy->orientation = ft_rotate_x(cy->orientation, 9.0 * M_PI / 180);
	else if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		cy->orientation = ft_rotate_x(cy->orientation, -9.0 * M_PI / 180);
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		cy->orientation = ft_rotate_z(cy->orientation, 9.0 * M_PI / 180);
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		cy->orientation = ft_rotate_z(cy->orientation, -9.0 * M_PI / 180);
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		cy->pos.y += 1;
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		cy->pos.y -= 1;
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		cy->pos.x += 1;
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		cy->pos.x -= 1;
	else if (keydata.key == MLX_KEY_Q && keydata.action == MLX_PRESS)
		cy->pos.z -= 1;
	else if (keydata.key == MLX_KEY_Z && keydata.action == MLX_PRESS)
		cy->pos.z += 1;
	else
		return (false);
	return (true);
}

/**
 * @brief	Function for handle the interaction when we press a key
 * 
 * @param	scene Our big struct
 * @param	keydata information of the key pressed
 * @return	true
 * @return	false
 */
bool	ft_object_moves(t_scene *scene, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_L && keydata.action == MLX_PRESS)
		return (ft_objet_to_light(scene));
	else if (keydata.key == MLX_KEY_O && keydata.action == MLX_PRESS)
		return (ft_objet_to_cam(scene));
	else
	{
		if (keydata.key == MLX_KEY_TAB && keydata.action == MLX_PRESS)
			ft_change_object(scene);
		else if (scene->actual_object.ac_o->type == PLANE)
			return (ft_move_plane(scene, keydata, NULL));
		else if (scene->actual_object.ac_o->type == SPHERE)
			return (ft_move_sphere(scene, keydata));
		else if (scene->actual_object.ac_o->type == CYLINDER)
			return (ft_move_cylinder(scene, keydata, NULL));
		else
			return (false);
	}
	return (true);
}
