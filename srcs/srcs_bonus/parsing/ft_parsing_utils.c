/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:47:17 by benpicar          #+#    #+#             */
/*   Updated: 2025/05/21 15:36:08 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief	Check if the next character is valid
 * 
 * @param	buf The buffer containing the line
 * @param	i The index of the line
 * @return	true if the next character is valid
 * @return	false if the next character is not valid
 */
bool	ft_add_check_char(char *buf, int i)
{
	if (buf[i] < '0' || buf[i] > '9')
	{
		if (buf[i] != '.' && buf[i] != '+' && buf[i] != '-')
			return (false);
	}
	return (true);
}

/**
 * @brief	Check if the next character is valid
 * 
 * @param	buf The buffer containing the line
 * @param	i The index of the line
 * @return	true if the next character is valid
 * @return	false if the next character is not valid
 */
bool	ft_add_check(char *buf, int i)
{
	if (!buf[i] || !buf[i + 1])
		return (false);
	if (buf[i + 1] < '0' || buf[i + 1] > '9')
	{
		if (buf[i + 1] != '+' && buf[i + 1] != '-' && buf[i + 1] != '.')
			return (false);
	}
	return (true);
}

/**
 * @brief	Move the index to the next information
 * 
 * @param	buf The buffer containing the line
 * @param	i The index of the line
 */
void	ft_next_info(char *buf, int *i)
{
	while (ft_isspace(buf[*i]))
		(*i)++;
}

/**
 * @brief	Check if the vector is in the range
 * 
 * @param	vec The vector to check
 * @param	max The maximum value
 * @param	min The minimum value
 * @return	true if the vector is in the range
 * @return	false if the vector is out of the range
 */
bool	ft_have_good_val(t_vec3 vec, float max, float min)
{
	if (vec.x > max || vec.x < min)
		return (false);
	if (vec.y > max || vec.y < min)
		return (false);
	if (vec.z > max || vec.z < min)
		return (false);
	return (true);
}

bool	dir_is_valid(t_vec3 dir)
{
	return (vec3_squarred_length(dir) != 0);
}
