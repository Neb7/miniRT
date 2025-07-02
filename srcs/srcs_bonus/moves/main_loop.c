/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:16:24 by benpicar          #+#    #+#             */
/*   Updated: 2025/05/22 13:54:42 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief	Move all objects in the scene who have a routine.
 * 
 * @param	scene The scene containing the objects to move
 */
void	move_object(t_scene *scene)
{
	t_object	*object;
	int			i;

	i = -1;
	while (++i < (int)scene->objects->index)
	{
		object = &((t_object *)scene->objects->buf)[i];
		if (!object->pos_list || object->max == 0)
			continue ;
		if (vec3_point_close(object->pos_list[object->i], \
			get_object_origin(object), object, scene->delta_time))
		{
			object->i = (object->i + 1) % object->max;
			object->dir = get_dir(object);
		}
		move(object, scene->delta_time);
	}
}

void	main_loop(void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	move_object(scene);
	renderer(scene);
}
