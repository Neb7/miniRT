/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:53:59 by benpicar          #+#    #+#             */
/*   Updated: 2025/05/22 17:01:47 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief	Add the position to the sphere
 * 
 * @param	scene Our big struct
 * @param	buf The buffer containing the line
 * @param	i The index of the line
 * @param	sh The sphere
 */
static void	ft_add_sphere_pos(t_scene *scene, char *buf, int *i, t_sphere *sh)
{
	if (!ft_add_check_char(buf, *i))
		return (free(sh), free(buf), ft_exit_error(scene, ERR_MIS));
	sh->origin.x = ft_atof(buf, i, scene);
	if (!ft_add_check(buf, *i))
		return (free(sh), free(buf), ft_exit_error(scene, ERR_MIS));
	(*i)++;
	sh->origin.y = ft_atof(buf, i, scene);
	if (!ft_add_check(buf, *i))
		return (free(sh), free(buf), ft_exit_error(scene, ERR_MIS));
	(*i)++;
	sh->origin.z = ft_atof(buf, i, scene);
}

/**
 * @brief	Add the diameter to the sphere
 * 
 * @param	scene Our big struct
 * @param	buf The buffer containing the line
 * @param	i The index of the line
 * @param	sh The sphere
 */
static void	ft_add_sphere_diam(t_scene *scene, char *buf, int *i, t_sphere *sh)
{
	if (!ft_add_check_char(buf, *i))
		return (free(sh), free(buf), ft_exit_error(scene, ERR_MIS));
	sh->radius = ft_atof(buf, i, scene);
	if (sh->radius <= 0)
		return (free(sh), free(buf), ft_exit_error(scene, ERR_DIAM));
	sh->radius = sh->radius / 2;
	sh->squarred_radius = sh->radius * sh->radius;
}

/**
 * @brief	Add the color to the sphere
 * 
 * @param	scene Our big struct
 * @param	buf The buffer containing the line
 * @param	i The index of the line
 * @param	sh The sphere
 */
static void	ft_add_sphere_color(t_scene *scene, char *buf, int *i, t_sphere *sh)
{
	if (!ft_add_check_char(buf, *i))
		return (free(sh), free(buf), ft_exit_error(scene, ERR_MIS));
	sh->color.x = ft_atof(buf, i, scene);
	if (!ft_add_check(buf, *i))
		return (free(sh), free(buf), ft_exit_error(scene, ERR_MIS));
	(*i)++;
	sh->color.y = ft_atof(buf, i, scene);
	if (!ft_add_check(buf, *i))
		return (free(sh), free(buf), ft_exit_error(scene, ERR_MIS));
	(*i)++;
	sh->color.z = ft_atof(buf, i, scene);
	if (!ft_have_good_val(sh->color, 255, 0))
		return (free(sh), free(buf), ft_exit_error(scene, ERR_COL));
	sh->color = vec3_div_scalar(sh->color, 255.0f);
	ft_next_info(buf, i);
	if (buf[*i] == 't' || buf[*i] == 'f')
	{
		if (buf[*i] == 't')
			sh->bump = true;
		else
			sh->bump = false;
		(*i)++;
	}
}

/**
 * @brief	Add the sphere to the scene
 * 
 * @param	scene Our big struct
 * @param	buf The buffer containing the line
 * @param	j The index of the line
 */
void	ft_add_sphere(t_scene *scene, char *buf, int j)
{
	int			i;
	t_object	new;
	t_sphere	*sh;

	i = j;
	ft_bzero(&new, sizeof(t_object));
	new.type = SPHERE;
	sh = (t_sphere *)ft_calloc(1, sizeof(t_sphere));
	if (!sh)
		return (free(buf), ft_exit_error(scene, ERR_MALLOC));
	ft_next_info(buf, &i);
	ft_add_sphere_pos(scene, buf, &i, sh);
	ft_next_info(buf, &i);
	ft_add_sphere_diam(scene, buf, &i, sh);
	ft_next_info(buf, &i);
	ft_add_sphere_color(scene, buf, &i, sh);
	new.data = sh;
	ft_next_info(buf, &i);
	if (buf[i] != '\0')
		ft_add_objet_move(scene, buf, &i, &new);
	if (!ft_add_char_vector(&new, scene->objects, 1, sizeof(t_object)))
		return (free(sh), free(buf), ft_exit_error(scene, ERR_MALLOC));
}
