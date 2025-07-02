/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cam.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:53:18 by benpicar          #+#    #+#             */
/*   Updated: 2025/05/21 15:36:35 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief	Add the position of the camera
 * 
 * @param	scene Our big struct
 * @param	buf The buffer containing the line
 * @param	i The index of the line
 */
static void	ft_add_camera_pos(t_scene *scene, char *buf, int *i)
{
	if (!ft_add_check_char(buf, *i))
		return (free(buf), ft_exit_error(scene, ERR_MIS));
	scene->camera.origin.x = ft_atof(buf, i, scene);
	if (!ft_add_check(buf, *i))
		return (free(buf), ft_exit_error(scene, ERR_MIS));
	(*i)++;
	scene->camera.origin.y = ft_atof(buf, i, scene);
	if (!ft_add_check(buf, *i))
		return (free(buf), ft_exit_error(scene, ERR_MIS));
	(*i)++;
	scene->camera.origin.z = ft_atof(buf, i, scene);
}

/**
 * @brief	Add the orientation of the camera
 * 
 * @param	scene Our big struct
 * @param	buf The buffer containing the line
 * @param	i The index of the line
 */
static void	ft_add_camera_ori(t_scene *scene, char *buf, int *i)
{
	if (!ft_add_check_char(buf, *i))
		return (free(buf), ft_exit_error(scene, ERR_MIS));
	scene->camera.direction.x = ft_atof(buf, i, scene);
	if (!ft_add_check(buf, *i))
		return (free(buf), ft_exit_error(scene, ERR_MIS));
	(*i)++;
	scene->camera.direction.y = ft_atof(buf, i, scene);
	if (!ft_add_check(buf, *i))
		return (free(buf), ft_exit_error(scene, ERR_MIS));
	(*i)++;
	scene->camera.direction.z = ft_atof(buf, i, scene);
	if (!ft_have_good_val(scene->camera.direction, 1, -1) \
			|| !dir_is_valid(scene->camera.direction))
		return (free(buf), ft_exit_error(scene, ERR_ORI));
	scene->camera.direction = vec3_normalize(scene->camera.direction);
}

/**
 * @brief	Add the orizontal field of view in degrees in the range [0, 180]
 * 
 * @param	scene Our big struct
 * @param	buf The buffer containing the line
 * @param	i The index of the line
 */
static void	ft_add_camera_fov(t_scene *scene, char *buf, int *i)
{
	if (!ft_add_check_char(buf, *i))
		return (free(buf), ft_exit_error(scene, ERR_MIS));
	scene->camera.fov = ft_atof(buf, i, scene);
	if (scene->camera.fov > 180 || scene->camera.fov < 0)
		return (free(buf), ft_exit_error(scene, ERR_CAM_AN));
}

/**
 * @brief	Add the camera to the scene
 * 
 * @param	scene Our big struct
 * @param	buf The buffer containing the line
 * @param	j The index of the line
 */
void	ft_add_camera(t_scene *scene, char *buf, int j)
{
	int	i;

	scene->nbr_ele.cam++;
	if (scene->nbr_ele.cam > 1)
		return (free(buf), ft_exit_error(scene, ERR_NBC));
	i = j;
	ft_next_info(buf, &i);
	ft_add_camera_pos(scene, buf, &i);
	ft_next_info(buf, &i);
	ft_add_camera_ori(scene, buf, &i);
	ft_next_info(buf, &i);
	ft_add_camera_fov(scene, buf, &i);
	ft_next_info(buf, &i);
	scene->camera.win_size[0] = WIN_WIDTH;
	scene->camera.win_size[1] = WIN_HEIGHT;
	if (buf[i] != '\0')
		return (free(buf), ft_exit_error(scene, ERR_TOO_L));
}
