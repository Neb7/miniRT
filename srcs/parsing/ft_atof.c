/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:28:04 by benpicar          #+#    #+#             */
/*   Updated: 2025/05/19 14:46:17 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief	Check the overflow of the float
 * 
 * @param	var Struct of temporary variables
 * @param	nbr The string to convert
 * @return	true if the number will't overflow
 * @return	false if the number will overflow
 */
static bool	ft_atof_overflow(t_atof *var, char *nbr)
{
	if (var->res > FLT_MAX / 10)
		return (false);
	if (var->res > FLT_MAX - (nbr[var->j] - '0'))
		return (false);
	return (true);
}

/**
 * @brief	Make the conversion of the string to a float
 * 
 * @param	var Struct of temporary variables
 * @param	nbr The string to convert
 * @param	scene Our big struct
 * @return	true if the conversion is successful
 * @return	false if the string have a wrong format
 */
static bool	ft_atof_make_nbr(t_atof *var, char *nbr, t_scene *scene)
{
	while (nbr[var->j] != '\0' && !ft_isspace(nbr[var->j]))
	{
		if (nbr[var->j] == '.')
		{
			if (var->dec)
				return (false);
			(var->dec)++;
		}
		else if (nbr[var->j] < '0' || nbr[var->j] > '9')
			return (true);
		else if (!var->dec)
		{
			if (!ft_atof_overflow(var, nbr))
				return (free(nbr), ft_exit_error(scene, ERR_OVE), false);
			var->res = (var->res * 10) + (nbr[var->j] - '0');
		}
		else
		{
			var->frac = (var->frac * 10) + (nbr[var->j] - '0');
			var->div = var->div * 10;
		}
		(var->j)++;
	}
	return (true);
}

/**
 * @brief	Convert a string to a float
 * 
 * @param	nbr The string to convert
 * @param	i The index to start from
 * @param	scene Our big struct
 * @return	The converted float
 */
float	ft_atof(char *nbr, int *i, t_scene *scene)
{
	t_atof	var;
	float	final;

	bzero(&var, sizeof(t_atof));
	var.div = 1;
	var.sign = 1;
	var.j = *i;
	if (nbr[var.j] == '-' || nbr[var.j] == '+')
	{
		if (nbr[var.j] == '-')
			var.sign *= -1;
		(var.j)++;
	}
	if (!ft_atof_make_nbr(&var, nbr, scene))
		return (free(nbr), ft_exit_error(scene, ERR_CARNUM), 0);
	final = (var.res + (var.frac / var.div)) * var.sign;
	*i = var.j;
	return (final);
}
