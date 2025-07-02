/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:58:49 by benpicar          #+#    #+#             */
/*   Updated: 2025/05/21 15:35:51 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief	Add the orientation to the cylinder
 * 
 * @param	scene Our big struct
 * @param	buf The buffer containing the line
 * @param	i The index of the line
 */
static void	ft_add_cylinder_ori(t_scene *scene, char *buf, int *i, \
	t_cylinder *cy)
{
	if (!ft_add_check_char(buf, *i))
		return (free(cy), free(buf), ft_exit_error(scene, ERR_MIS));
	cy->orientation.x = ft_atof(buf, i, scene);
	if (!ft_add_check(buf, *i))
		return (free(cy), free(buf), ft_exit_error(scene, ERR_MIS));
	(*i)++;
	cy->orientation.y = ft_atof(buf, i, scene);
	if (!ft_add_check(buf, *i))
		return (free(cy), free(buf), ft_exit_error(scene, ERR_MIS));
	(*i)++;
	cy->orientation.z = ft_atof(buf, i, scene);
	if (!ft_have_good_val(cy->orientation, 1, -1) \
		|| !dir_is_valid(cy->orientation))
		return (free(cy), free(buf), ft_exit_error(scene, ERR_ORI));
	cy->orientation = vec3_normalize(cy->orientation);
}

/**
 * @brief	Add the position to the cylinder
 * 
 * @param	scene Our big struct
 * @param	buf The buffer containing the line
 * @param	i The index of the line
 * @param	cy The cylinder
 */
static void	ft_add_cylinder_pos(t_scene *scene, char *buf, int *i, \
	t_cylinder *cy)
{
	if (!ft_add_check_char(buf, *i))
		return (free(cy), free(buf), ft_exit_error(scene, ERR_MIS));
	cy->pos.x = ft_atof(buf, i, scene);
	if (!ft_add_check(buf, *i))
		return (free(cy), free(buf), ft_exit_error(scene, ERR_MIS));
	(*i)++;
	cy->pos.y = ft_atof(buf, i, scene);
	if (!ft_add_check(buf, *i))
		return (free(cy), free(buf), ft_exit_error(scene, ERR_MIS));
	(*i)++;
	cy->pos.z = ft_atof(buf, i, scene);
	ft_next_info(buf, i);
	ft_add_cylinder_ori(scene, buf, i, cy);
}

/**
 * @brief	Add the diameter and height to the cylinder
 * 
 * @param	scene Our big struct
 * @param	buf The buffer containing the line
 * @param	i The index of the line
 */
static void	ft_add_cylinder_diam(t_scene *scene, char *buf, int *i, \
	t_cylinder *cy)
{
	if (!ft_add_check_char(buf, *i))
		return (free(cy), free(buf), ft_exit_error(scene, ERR_MIS));
	cy->diameter = ft_atof(buf, i, scene);
	if (cy->diameter <= 0)
		return (free(cy), free(buf), ft_exit_error(scene, ERR_DIAM));
	cy->radius = cy->diameter / 2;
	ft_next_info(buf, i);
	if (!ft_add_check_char(buf, *i))
		return (free(cy), free(buf), ft_exit_error(scene, ERR_MIS));
	cy->height = ft_atof(buf, i, scene);
	if (cy->height <= 0)
		return (free(cy), free(buf), ft_exit_error(scene, ERR_DIAM));
}

/**
 * @brief	Add the color to the cylinder
 * 
 * @param	scene Our big struct
 * @param	buf The buffer containing the line
 * @param	i The index of the line
 */
static void	ft_add_cylinder_color(t_scene *scene, char *buf, int *i, \
	t_cylinder *cy)
{
	if (!ft_add_check_char(buf, *i))
		return (free(cy), free(buf), ft_exit_error(scene, ERR_MIS));
	cy->color.x = ft_atof(buf, i, scene);
	if (!ft_add_check(buf, *i))
		return (free(cy), free(buf), ft_exit_error(scene, ERR_MIS));
	(*i)++;
	cy->color.y = ft_atof(buf, i, scene);
	if (!ft_add_check(buf, *i))
		return (free(cy), free(buf), ft_exit_error(scene, ERR_MIS));
	(*i)++;
	cy->color.z = ft_atof(buf, i, scene);
	if (!ft_have_good_val(cy->color, 255, 0))
		return (free(cy), free(buf), ft_exit_error(scene, ERR_COL));
	cy->color = vec3_div_scalar(cy->color, 255.0f);
	cy->forward = (t_vec3){0.0, 0.0, 1.0};
	cy->right = (t_vec3){1.0, 0.0, 0.0};
	cy->up = (t_vec3){0.0, 1.0, 0.0};
}

/**
 * @brief	Add the cylinder to the scene
 * 
 * @param	scene Our big struct
 * @param	buf The buffer containing the line
 * @param	j The index of the line
 */
void	ft_add_cylinder(t_scene *scene, char *buf, int j)
{
	int			i;
	t_object	new;
	t_cylinder	*cy;

	i = j;
	ft_bzero(&new, sizeof(t_object));
	new.type = CYLINDER;
	cy = (t_cylinder *)ft_calloc(1, sizeof(t_cylinder));
	if (!cy)
		return (free(buf), ft_exit_error(scene, ERR_MALLOC));
	ft_next_info(buf, &i);
	ft_add_cylinder_pos(scene, buf, &i, cy);
	ft_next_info(buf, &i);
	ft_add_cylinder_diam(scene, buf, &i, cy);
	ft_next_info(buf, &i);
	ft_add_cylinder_color(scene, buf, &i, cy);
	new.data = cy;
	ft_next_info(buf, &i);
	if (buf[i] != '\0')
		ft_add_objet_move(scene, buf, &i, &new);
	if (!ft_add_char_vector(&new, scene->objects, 1, sizeof(t_object)))
		return (free(cy), free(buf), ft_exit_error(scene, ERR_MALLOC));
	ft_next_info(buf, &i);
	if (buf[i] != '\0')
		return (free(buf), ft_exit_error(scene, ERR_TOO_L));
}
