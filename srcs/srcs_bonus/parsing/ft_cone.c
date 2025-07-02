/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cone.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:19:25 by benpicar          #+#    #+#             */
/*   Updated: 2025/05/21 15:35:44 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief	Add the orientation to the cone
 * 
 * @param	scene Our big struct
 * @param	buf The buffer containing the line
 * @param	i The index of the line
 */
static void	ft_add_cone_ori(t_scene *scene, char *buf, int *i, \
	t_cone *co)
{
	if (!ft_add_check_char(buf, *i))
		return (free(co), free(buf), ft_exit_error(scene, ERR_MIS));
	co->orientation.x = ft_atof(buf, i, scene);
	if (!ft_add_check(buf, *i))
		return (free(co), free(buf), ft_exit_error(scene, ERR_MIS));
	(*i)++;
	co->orientation.y = ft_atof(buf, i, scene);
	if (!ft_add_check(buf, *i))
		return (free(co), free(buf), ft_exit_error(scene, ERR_MIS));
	(*i)++;
	co->orientation.z = ft_atof(buf, i, scene);
	if (!ft_have_good_val(co->orientation, 1, -1) \
			|| !dir_is_valid(co->orientation))
		return (free(co), free(buf), ft_exit_error(scene, ERR_ORI));
	co->orientation = vec3_normalize(co->orientation);
}

/**
 * @brief	Add the position to the cone
 * 
 * @param	scene Our big struct
 * @param	buf The buffer containing the line
 * @param	i The index of the line
 */
static void	ft_add_cone_pos(t_scene *scene, char *buf, int *i, \
	t_cone *co)
{
	if (!ft_add_check_char(buf, *i))
		return (free(co), free(buf), ft_exit_error(scene, ERR_MIS));
	co->pos.x = ft_atof(buf, i, scene);
	if (!ft_add_check(buf, *i))
		return (free(co), free(buf), ft_exit_error(scene, ERR_MIS));
	(*i)++;
	co->pos.y = ft_atof(buf, i, scene);
	if (!ft_add_check(buf, *i))
		return (free(co), free(buf), ft_exit_error(scene, ERR_MIS));
	(*i)++;
	co->pos.z = ft_atof(buf, i, scene);
	ft_next_info(buf, i);
	ft_add_cone_ori(scene, buf, i, co);
}

/**
 * @brief	Add the diameter and height to the cone
 * 
 * @param	scene Our big struct
 * @param	buf The buffer containing the line
 * @param	i The index of the line
 */
static void	ft_add_cone_diam(t_scene *scene, char *buf, int *i, \
	t_cone *co)
{
	if (!ft_add_check_char(buf, *i))
		return (free(co), free(buf), ft_exit_error(scene, ERR_MIS));
	co->diameter = ft_atof(buf, i, scene);
	if (co->diameter <= 0)
		return (free(co), free(buf), ft_exit_error(scene, ERR_DIAM));
	co->radius = co->diameter / 2;
	ft_next_info(buf, i);
	if (!ft_add_check_char(buf, *i))
		return (free(co), free(buf), ft_exit_error(scene, ERR_MIS));
	co->height = ft_atof(buf, i, scene);
	if (co->height <= 0)
		return (free(co), free(buf), ft_exit_error(scene, ERR_DIAM));
	co->radius = co->height * tanf(M_PI / 4.0f);
}

/**
 * @brief	Add the color to the cone
 * 
 * @param	scene Our big struct
 * @param	buf The buffer containing the line
 * @param	i The index of the line
 */
static void	ft_add_cone_color(t_scene *scene, char *buf, int *i, \
	t_cone *co)
{
	if (!ft_add_check_char(buf, *i))
		return (free(co), free(buf), ft_exit_error(scene, ERR_MIS));
	co->color.x = ft_atof(buf, i, scene);
	if (!ft_add_check(buf, *i))
		return (free(co), free(buf), ft_exit_error(scene, ERR_MIS));
	(*i)++;
	co->color.y = ft_atof(buf, i, scene);
	if (!ft_add_check(buf, *i))
		return (free(co), free(buf), ft_exit_error(scene, ERR_MIS));
	(*i)++;
	co->color.z = ft_atof(buf, i, scene);
	if (!ft_have_good_val(co->color, 255, 0))
		return (free(co), free(buf), ft_exit_error(scene, ERR_COL));
	co->color = vec3_div_scalar(co->color, 255.0f);
	co->forward = (t_vec3){0.0, 0.0, 1.0};
	co->right = (t_vec3){1.0, 0.0, 0.0};
	co->up = (t_vec3){0.0, 1.0, 0.0};
}

/**
 * @brief	Add the cone to the scene
 * 
 * @param	scene Our big struct
 * @param	buf The buffer containing the line
 * @param	j The index of the line
 */
void	ft_add_cone(t_scene *scene, char *buf, int j)
{
	int			i;
	t_object	new;
	t_cone		*co;

	i = j;
	ft_bzero(&new, sizeof(t_object));
	new.type = CONE;
	co = (t_cone *)ft_calloc(1, sizeof(t_cone));
	if (!co)
		return (free(buf), ft_exit_error(scene, ERR_MALLOC));
	ft_next_info(buf, &i);
	ft_add_cone_pos(scene, buf, &i, co);
	ft_next_info(buf, &i);
	ft_add_cone_diam(scene, buf, &i, co);
	ft_next_info(buf, &i);
	ft_add_cone_color(scene, buf, &i, co);
	new.data = co;
	ft_next_info(buf, &i);
	if (buf[i] != '\0')
		ft_add_objet_move(scene, buf, &i, &new);
	if (!ft_add_char_vector(&new, scene->objects, 1, sizeof(t_object)))
		return (free(co), free(buf), ft_exit_error(scene, ERR_MALLOC));
	ft_next_info(buf, &i);
	if (buf[i] != '\0')
		return (free(buf), ft_exit_error(scene, ERR_TOO_L));
}
