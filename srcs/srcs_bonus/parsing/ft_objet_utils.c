/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_objet_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:08:09 by benpicar          #+#    #+#             */
/*   Updated: 2025/05/22 13:52:11 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief	Free the object, the buffer and the scene
 * 
 * @param	scene Our big struct
 */
static void	ft_free_move_objet(t_scene *scene, char *buf, t_object *new)
{
	free(new->data);
	free(new->pos_list);
	free(buf);
	ft_exit_error(scene, ERR_MIS);
}

/**
 * @brief	Move the index to the next information
 * 
 * @param	buf The buffer containing the line
 * @param	i The index of the line
 * @param	new The object
 * @param	scene Our big struct
 */
static t_vec3	ft_next_coor(char *buf, int *i, t_scene *scene, t_object *new)
{
	t_vec3	ret;

	ft_bzero(&ret, sizeof(t_vec3));
	if (!ft_add_check_char(buf, *i))
		return (ft_free_move_objet(scene, buf, new), ret);
	ret.x = ft_atof(buf, i, scene);
	if (!ft_add_check(buf, *i))
		return (ft_free_move_objet(scene, buf, new), ret);
	(*i)++;
	ret.y = ft_atof(buf, i, scene);
	if (!ft_add_check(buf, *i))
		return (ft_free_move_objet(scene, buf, new), ret);
	(*i)++;
	ret.z = ft_atof(buf, i, scene);
	return (ret);
}

/**
 * @brief	Add positions to the object for an auto move
 * 
 * @param	scene Our big struct
 * @param	buf The buffer containing the line
 * @param	i The index of the line
 * @param	new The object
 */
void	ft_add_objet_move(t_scene *scene, char *buf, int *i, t_object *new)
{
	size_t	j;

	j = 0;
	if (!ft_isdigit(buf[*i]))
		return (free(new->data), free(buf), ft_exit_error(scene, ERR_MIS));
	new->max = (size_t)ft_atoi_i(&buf[*i], i);
	new->pos_list = ft_calloc(new->max + 1, sizeof(t_vec3));
	if (!new->pos_list)
		return (free(new->data), free(buf), ft_exit_error(scene, ERR_MALLOC));
	new->pos_list[0] = ((t_cone *)new->data)->pos;
	while (++j <= new->max)
	{
		ft_next_info(buf, i);
		if (!ft_add_check_char(buf, *i))
			return (ft_free_move_objet(scene, buf, new));
		new->pos_list[j] = ft_next_coor(buf, i, scene, new);
	}
	if (new->max > 0)
	{
		ft_next_info(buf, i);
		if (!ft_add_check_char(buf, *i))
			return (ft_free_move_objet(scene, buf, new));
		new->speed = fabs(ft_atof(buf, i, scene));
		(new->max)++;
	}
}
