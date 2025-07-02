/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:53:46 by benpicar          #+#    #+#             */
/*   Updated: 2025/05/21 15:51:26 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief	Add the position to the plane
 * 
 * @param	scene Our big struct
 * @param	buf The buffer containing the line
 * @param	i The index of the line
 * @param	pl The plane
 */
static void	ft_add_plane_pos(t_scene *scene, char *buf, int *i, t_plane *pl)
{
	if (!ft_add_check_char(buf, *i))
		return (free(pl), free(buf), ft_exit_error(scene, ERR_MIS));
	pl->origin.x = ft_atof(buf, i, scene);
	if (!ft_add_check(buf, *i))
		return (free(pl), free(buf), ft_exit_error(scene, ERR_MIS));
	(*i)++;
	pl->origin.y = ft_atof(buf, i, scene);
	if (!ft_add_check(buf, *i))
		return (free(pl), free(buf), ft_exit_error(scene, ERR_MIS));
	(*i)++;
	pl->origin.z = ft_atof(buf, i, scene);
}

/**
 * @brief	Add the orientation to the plane
 * 
 * @param	scene Our big struct
 * @param	buf The buffer containing the line
 * @param	i The index of the line
 * @param	pl The plane
 */
static void	ft_add_plane_ori(t_scene *scene, char *buf, int *i, t_plane *pl)
{
	if (!ft_add_check_char(buf, *i))
		return (free(pl), free(buf), ft_exit_error(scene, ERR_MIS));
	pl->normal.x = ft_atof(buf, i, scene);
	if (!ft_add_check(buf, *i))
		return (free(pl), free(buf), ft_exit_error(scene, ERR_MIS));
	(*i)++;
	pl->normal.y = ft_atof(buf, i, scene);
	if (!ft_add_check(buf, *i))
		return (free(pl), free(buf), ft_exit_error(scene, ERR_MIS));
	(*i)++;
	pl->normal.z = ft_atof(buf, i, scene);
	if (!ft_have_good_val(pl->normal, 1, -1) || !dir_is_valid(pl->normal))
		return (free(pl), free(buf), ft_exit_error(scene, ERR_ORI));
	pl->normal = vec3_normalize(pl->normal);
	pl->forward = (t_vec3){0.0, 0.0, 1.0};
	pl->right = (t_vec3){1.0, 0.0, 0.0};
	pl->up = (t_vec3){0.0, 1.0, 0.0};
}

/**
 * @brief	Add the color to the plane
 * 
 * @param	scene Our big struct
 * @param	buf The buffer containing the line
 * @param	i The index of the line
 */
static void	ft_add_plane_color(t_scene *scene, char *buf, int *i, t_plane *pl)
{
	if (!ft_add_check_char(buf, *i))
		return (free(pl), free(buf), ft_exit_error(scene, ERR_MIS));
	pl->color.x = ft_atof(buf, i, scene);
	if (!ft_add_check(buf, *i))
		return (free(pl), free(buf), ft_exit_error(scene, ERR_MIS));
	(*i)++;
	pl->color.y = ft_atof(buf, i, scene);
	if (!ft_add_check(buf, *i))
		return (free(pl), free(buf), ft_exit_error(scene, ERR_MIS));
	(*i)++;
	pl->color.z = ft_atof(buf, i, scene);
	if (!ft_have_good_val(pl->color, 255, 0))
		return (free(pl), free(buf), ft_exit_error(scene, ERR_COL));
	pl->color = vec3_div_scalar(pl->color, 255.0f);
	ft_next_info(buf, i);
	if (buf[*i] == 't' || buf[*i] == 'f')
	{
		if (buf[*i] == 't')
			pl->checkerboard = true;
		else
			pl->checkerboard = false;
		(*i)++;
	}
}

/**
 * @brief	Add the plane to the scene
 * 
 * @param	scene Our big struct
 * @param	buf The buffer containing the line
 * @param	j The index of the line
 */
void	ft_add_plane(t_scene *scene, char *buf, int j)
{
	int			i;
	t_object	new;
	t_plane		*pl;

	i = j;
	ft_bzero(&new, sizeof(t_object));
	new.type = PLANE;
	pl = (t_plane *)ft_calloc(1, sizeof(t_plane));
	if (!pl)
		return (free(buf), ft_exit_error(scene, ERR_MALLOC));
	ft_next_info(buf, &i);
	ft_add_plane_pos(scene, buf, &i, pl);
	ft_next_info(buf, &i);
	ft_add_plane_ori(scene, buf, &i, pl);
	ft_next_info(buf, &i);
	ft_add_plane_color(scene, buf, &i, pl);
	new.data = pl;
	ft_next_info(buf, &i);
	if (buf[i] != '\0')
		ft_add_objet_move(scene, buf, &i, &new);
	if (!ft_add_char_vector(&new, scene->objects, 1, sizeof(t_object)))
		return (free(pl), free(buf), ft_exit_error(scene, ERR_MALLOC));
	ft_next_info(buf, &i);
	if (buf[i] != '\0')
		return (free(buf), ft_exit_error(scene, ERR_TOO_L));
}
