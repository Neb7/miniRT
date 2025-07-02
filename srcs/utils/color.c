/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:03:56 by llemmel           #+#    #+#             */
/*   Updated: 2025/05/27 14:09:21 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_put_pixel(mlx_image_t *img, \
	int coord[2], t_vec3 color, uint8_t alpha)
{
	uint8_t	*dst;

	if (!img || !img->pixels || coord[0] < 0 || coord[0] >= (int)img->width \
		|| coord[1] < 0 || coord[1] >= (int)img->height)
		return ;
	if (color.x > 1.0f)
		color.x = 1.0f;
	if (color.y > 1.0f)
		color.y = 1.0f;
	if (color.z > 1.0f)
		color.z = 1.0f;
	dst = img->pixels + (coord[1] * img->width + coord[0]) * sizeof(uint32_t);
	dst[0] = (uint8_t)(color.x * 255);
	dst[1] = (uint8_t)(color.y * 255);
	dst[2] = (uint8_t)(color.z * 255);
	dst[3] = alpha;
}

t_vec3	get_object_color(const t_object *object)
{
	if (object->type == SPHERE)
		return (((t_sphere *)object->data)->color);
	else if (object->type == PLANE)
		return ((((t_plane *)object->data)->color));
	else if (object->type == CYLINDER)
		return ((((t_cylinder *)object->data)->color));
	else if (object->type == CONE)
		return ((((t_cone *)object->data)->color));
	else
		return ((t_vec3){0, 0, 0});
}
