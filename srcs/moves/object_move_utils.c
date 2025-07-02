/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_move_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:51:57 by benpicar          #+#    #+#             */
/*   Updated: 2025/05/19 14:34:59 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Change the current object selection to the light.
 *
 * @param scene Our big struct
 * @return true
 */
bool	ft_objet_to_light(t_scene *scene)
{
	scene->on_object = false;
	scene->light_yagami = true;
	ft_bzero(scene->actual_name, 10);
	ft_memcpy(scene->actual_name, "Light", 6);
	return (true);
}

/**
 * @brief Change the current object selection to the camera.
 *
 * @param scene Our big struct
 * @return true
 */
bool	ft_objet_to_cam(t_scene *scene)
{
	scene->on_object = false;
	ft_bzero(scene->actual_name, 10);
	ft_memcpy(scene->actual_name, "Camera", 7);
	return (true);
}
