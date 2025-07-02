/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:27:22 by benpicar          #+#    #+#             */
/*   Updated: 2025/05/19 19:26:32 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//printf("in parse '%s'  \n", buf);

/**
 * @brief	Parse the line and check if the format is correct
 * 
 * @param	scene Our big struct
 * @param	buf The buffer containing the line
 * @param	j The index of the line
 */
static void	ft_parsing_check_id(t_scene *scene, char *buf, int j)
{
	if (!ft_strncmp(&buf[j], "A", 1) && ft_isspace(buf[j + 1]))
		ft_add_ambient(scene, buf, j + 1);
	else if (!ft_strncmp(&buf[j], "C", 1) && ft_isspace(buf[j + 1]))
		ft_add_camera(scene, buf, j + 1);
	else if (!ft_strncmp(&buf[j], "L", 1) && ft_isspace(buf[j + 1]))
		ft_add_light(scene, buf, j + 1);
	else if (!ft_strncmp(&buf[j], "sp", 2) && buf[j + 1]
		&& ft_isspace(buf[j + 2]))
		ft_add_sphere(scene, buf, j + 2);
	else if (!ft_strncmp(&buf[j], "pl", 2) && buf[j + 1]
		&& ft_isspace(buf[j + 2]))
		ft_add_plane(scene, buf, j + 2);
	else if (!ft_strncmp(&buf[j], "cy", 2) && buf[j + 1]
		&& ft_isspace(buf[j + 2]))
		ft_add_cylinder(scene, buf, j + 2);
	else
		return (free(buf), ft_exit_error(scene, ERR_WRO));
}

/**
 * @brief	Set the actual object and light to the first one
 * 
 * @param	scene Our big struct
 */
static void	ft_set_actual(t_scene *scene)
{
	scene->actual_light.ac_l = &((t_light *)scene->lights->buf)[0];
	scene->actual_light.i = 0;
	scene->actual_object.ac_o = &((t_object *)scene->objects->buf)[0];
	scene->actual_object.i = 0;
}

/**
 * @brief	Parse the file and check if the format is correct
 * 
 * @param	file_name The name of the file to parse
 * @param	scene Our big struct
 * @return	true if the parsing is successful
 * @return	false if the parsing failed
 */
bool	ft_this_is_sparsing(char *file_name, t_scene *scene)
{
	char	*buf;
	size_t	j;

	if (ft_strncmp(&file_name[ft_strlen(file_name) - 3], ".rt", 3))
		return (ft_putstr_fd(ERR_NAME, 2), false);
	scene->fd = open(file_name, O_RDONLY);
	if (scene->fd < 0)
		return (ft_putstr_fd(ERR_OPN, 2), false);
	buf = get_next_line(scene->fd, 0);
	if (!buf)
		return (ft_putstr_fd(ERR_READ, 2), close(scene->fd), false);
	while (buf != NULL)
	{
		j = 0;
		while (ft_isspace(buf[j]))
			j++;
		if (buf[j] != '\0')
			ft_parsing_check_id(scene, buf, j);
		free(buf);
		buf = get_next_line(scene->fd, 0);
	}
	close(scene->fd);
	ft_set_actual(scene);
	return (true);
}
