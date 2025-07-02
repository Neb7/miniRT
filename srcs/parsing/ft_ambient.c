/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ambient.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:52:57 by benpicar          #+#    #+#             */
/*   Updated: 2025/05/19 14:41:52 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief	Add the ratio to the ambient light
 * 
 * @param	scene Our big struct
 * @param	buf The buffer containing the line
 * @param	i The index of the line
 */
static void	ft_add_ambient_ratio(t_scene *scene, char *buf, int *i)
{
	if (!ft_add_check_char(buf, *i))
		return (free(buf), ft_exit_error(scene, ERR_MIS));
	scene->ambiant_ligth.ratio = ft_atof(buf, i, scene);
	if (scene->ambiant_ligth.ratio > 1 || scene->ambiant_ligth.ratio < 0)
		return (free(buf), ft_exit_error(scene, ERR_LIG_R));
}

/**
 * @brief	Add the color to the ambient light
 * 
 * @param	scene Our big struct
 * @param	buf The buffer containing the line
 * @param	i The index of the line
 */
static void	ft_add_ambient_color(t_scene *scene, char *buf, int *i)
{
	if (!ft_add_check_char(buf, *i))
		return (free(buf), ft_exit_error(scene, ERR_MIS));
	scene->ambiant_ligth.color.x = ft_atof(buf, i, scene);
	if (!ft_add_check(buf, *i))
		return (free(buf), ft_exit_error(scene, ERR_MIS));
	(*i)++;
	scene->ambiant_ligth.color.y = ft_atof(buf, i, scene);
	if (!ft_add_check(buf, *i))
		return (free(buf), ft_exit_error(scene, ERR_MIS));
	(*i)++;
	scene->ambiant_ligth.color.z = ft_atof(buf, i, scene);
	if (!ft_have_good_val(scene->ambiant_ligth.color, 255, 0))
		return (free(buf), ft_exit_error(scene, ERR_COL));
	scene->ambiant_ligth.color = vec3_div_scalar(
			scene->ambiant_ligth.color, 255.0f);
}

/**
 * @brief	Add the ambient light to the scene
 * 
 * @param	scene Our big struct
 * @param	buf The buffer containing the line
 * @param	j The index of the line
 */
void	ft_add_ambient(t_scene *scene, char *buf, int j)
{
	int	i;

	scene->nbr_ele.ambient++;
	if (scene->nbr_ele.ambient > 1)
		return (free(buf), ft_exit_error(scene, ERR_NBA));
	i = j;
	ft_next_info(buf, &i);
	ft_add_ambient_ratio(scene, buf, &i);
	ft_next_info(buf, &i);
	ft_add_ambient_color(scene, buf, &i);
	ft_next_info(buf, &i);
	if (buf[i] != '\0')
		return (free(buf), ft_exit_error(scene, ERR_TOO_L));
}
