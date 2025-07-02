/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:53:31 by benpicar          #+#    #+#             */
/*   Updated: 2025/05/19 19:27:07 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief	Add the color to the light
 * 
 * @param	scene Our big struct
 * @param	buf The buffer containing the line
 * @param	i The index of the line
 * @param	tmp The light
 */
static void	ft_add_light_pos(t_scene *scene, char *buf, int *i, t_light *tmp)
{
	if (!ft_add_check_char(buf, *i))
		return (free(buf), ft_exit_error(scene, ERR_MIS));
	tmp->origin.x = ft_atof(buf, i, scene);
	if (!ft_add_check(buf, *i))
		return (free(buf), ft_exit_error(scene, ERR_MIS));
	(*i)++;
	tmp->origin.y = ft_atof(buf, i, scene);
	if (!ft_add_check(buf, *i))
		return (free(buf), ft_exit_error(scene, ERR_MIS));
	(*i)++;
	tmp->origin.z = ft_atof(buf, i, scene);
}

/**
 * @brief	Add the ratio to the light
 * 
 * @param	scene Our big struct
 * @param	buf The buffer containing the line
 * @param	i The index of the line
 * @param	tmp The light
 */
static void	ft_add_light_ratio(t_scene *scene, char *buf, int *i, t_light *tmp)
{
	if (!ft_add_check_char(buf, *i))
		return (free(buf), ft_exit_error(scene, ERR_MIS));
	tmp->brightness = ft_atof(buf, i, scene);
	if (tmp->brightness > 1 || tmp->brightness < 0)
		return (free(buf), ft_exit_error(scene, ERR_LIG_R));
}

/**
 * @brief	Add the color to the light
 * 
 * @param	scene Our big struct
 * @param	buf The buffer containing the line
 * @param	i The index of the line
 * @param	tmp The light
 */
static void	ft_add_light_color(t_scene *scene, char *buf, int *i, t_light *tmp)
{
	if (buf[*i] == '\0')
	{
		tmp->color.x = 255;
		tmp->color.y = 255;
		tmp->color.z = 255;
		return ;
	}
	if (!ft_add_check_char(buf, *i))
		return (free(buf), ft_exit_error(scene, ERR_MIS));
	tmp->color.x = ft_atof(buf, i, scene);
	if (!ft_add_check(buf, *i))
		return (free(buf), ft_exit_error(scene, ERR_MIS));
	(*i)++;
	tmp->color.y = ft_atof(buf, i, scene);
	if (!ft_add_check(buf, *i))
		return (free(buf), ft_exit_error(scene, ERR_MIS));
	(*i)++;
	tmp->color.z = ft_atof(buf, i, scene);
	if (!ft_have_good_val(tmp->color, 255, 0))
		return (free(buf), ft_exit_error(scene, ERR_COL));
	tmp->color = vec3_div_scalar(tmp->color, 255.0f);
}

/**
 * @brief	Add the light to the scene
 * 
 * @param	scene Our big struct
 * @param	buf The buffer containing the line
 * @param	j The index of the line
 */
void	ft_add_light(t_scene *scene, char *buf, int j)
{
	int		i;
	t_light	tmp;

	scene->nbr_ele.light++;
	i = j;
	ft_bzero(&tmp, sizeof(t_light));
	ft_next_info(buf, &i);
	ft_add_light_pos(scene, buf, &i, &tmp);
	ft_next_info(buf, &i);
	ft_add_light_ratio(scene, buf, &i, &tmp);
	ft_next_info(buf, &i);
	ft_add_light_color(scene, buf, &i, &tmp);
	if (!ft_add_char_vector(&tmp, scene->lights, 1, sizeof(t_light)))
		return (free(buf), ft_exit_error(scene, ERR_MALLOC));
	ft_next_info(buf, &i);
	if (buf[i] != '\0')
		return (free(buf), ft_exit_error(scene, ERR_TOO_L));
}
