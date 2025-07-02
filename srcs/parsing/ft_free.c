/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:43:02 by benpicar          #+#    #+#             */
/*   Updated: 2025/05/22 17:01:14 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief	Free the struct scene and exit with an error message
 * 
 * @param	scene Our big struct
 * @param	err The error message to display
 */
void	ft_exit_error(t_scene *scene, char *err)
{
	ft_putstr_fd(err, STDERR_FILENO);
	ft_free_scene(scene);
	exit(EXIT_FAILURE);
}

/**
 * @brief	Free the mlx
 * 
 * @param	scene Our big struct
 */
void	ft_free_mlx(t_scene *scene)
{
	if (scene->win.mlx)
	{
		if (scene->win.image)
			mlx_delete_image(scene->win.mlx, scene->win.image);
		mlx_terminate(scene->win.mlx);
	}
}

/**
 * @brief	Free the struct scene
 * 
 * @param	scene Our big struct
 */
void	ft_free_scene(t_scene *scene)
{
	size_t		i;

	i = 0;
	ft_free_mlx(scene);
	if (scene->lights)
		ft_free_vector(&scene->lights);
	if (scene->objects)
	{
		while (i < scene->objects->index)
		{
			if (((t_object *)scene->objects->buf)[i].pos_list)
				free(((t_object *)scene->objects->buf)[i].pos_list);
			free(((t_object *)scene->objects->buf)[i].data);
			i++;
		}
		ft_free_vector(&scene->objects);
	}
	get_next_line(scene->fd, 1);
	close(scene->fd);
}
