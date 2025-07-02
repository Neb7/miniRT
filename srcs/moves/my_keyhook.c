/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_keyhook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:26:26 by benpicar          #+#    #+#             */
/*   Updated: 2025/05/27 14:12:58 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "Mlx_moi.h"
#include "parsing.h"

/**
 * @brief	Fonction for handle the interaction when we resize the window
 * 
 * @param	width The new width of the window
 * @param	height The new height of the window
 * @param	param Adress of our big struct
 */
void	resize(int32_t width, int32_t height, void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	scene->camera.win_size[0] = width;
	scene->camera.win_size[1] = height;
	scene->win.mlx->width = width;
	scene->win.mlx->height = height;
	mlx_delete_image(scene->win.mlx, scene->win.image);
	scene->win.image = NULL;
	renderer(scene);
}

/**
 * @brief	Fonction for handle the keyboad interaction
 * 
 * @param	keydata information of the key pressed
 * @param	param Adress of our big struct
 */
void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	bool	update;
	t_scene	*scene;

	scene = (t_scene *)param;
	update = false;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		return (ft_free_scene(scene), exit(0));
	if (!scene->on_object && !scene->light_yagami)
		update = ft_cam_moves(scene, keydata);
	else if (scene->light_yagami)
		update = ft_light_moves(scene, keydata);
	else if (scene->on_object)
		update = ft_object_moves(scene, keydata);
	if (update)
		renderer(scene);
}
