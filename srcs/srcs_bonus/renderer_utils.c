/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:25:04 by llemmel           #+#    #+#             */
/*   Updated: 2025/05/21 15:36:18 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "parsing.h"

/**
 * @brief	Initialize the image in the scene.
 * This function will create a new image with the size of the window.
 * 
 * @param	scene The scene to initialize the image in
 */
void	init_image(t_scene *scene)
{
	scene->win.image = mlx_new_image(scene->win.mlx, \
		scene->win.mlx->width, scene->win.mlx->height);
	if (!scene->win.image)
	{
		printf("Failed to create image\n");
		ft_free_scene(scene);
	}
}

/**
 * @brief	Display the window with the image.
 * It also display the mode name in the top left corner.
 * 
 * @param	scene The scene containing the window and the image to display
 */
void	display_window(t_scene *scene)
{
	mlx_image_t	*img;
	size_t		i;

	i = -1;
	img = mlx_put_string(scene->win.mlx, scene->actual_name, 32, 32);
	while (img && ++i < img->height)
	{
		ft_memcpy(scene->win.image->pixels + \
			(((32 + i) * scene->win.image->width * sizeof(int32_t)) \
			+ (32 * sizeof(int32_t))), img->pixels + \
			(i * img->width * sizeof(int32_t)), img->width * sizeof(int32_t));
	}
	mlx_image_to_window(scene->win.mlx, scene->win.image, 0, 0);
	mlx_delete_image(scene->win.mlx, img);
}

/**
 * @brief	Wait all the threads to be in RENDER state 
 * before starting the render.
 * 
 * @param	thread	The thread to wait
 * @return	true if the thread is in RENDER state, 
 * 				false if the thread is in ERROR state
 */
bool	wait_start(t_thread	*thread)
{
	pthread_mutex_lock(&thread->scene->mutex);
	while (thread->state != RENDER)
	{
		pthread_mutex_unlock(&thread->scene->mutex);
		usleep(100);
		pthread_mutex_lock(&thread->scene->mutex);
	}
	pthread_mutex_unlock(&thread->scene->mutex);
	pthread_mutex_lock(&thread->scene->mutex);
	if (thread->state == ERROR)
	{
		pthread_mutex_unlock(&thread->scene->mutex);
		return (false);
	}
	pthread_mutex_unlock(&thread->scene->mutex);
	return (true);
}
