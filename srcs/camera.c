/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:27:58 by llemmel           #+#    #+#             */
/*   Updated: 2025/07/02 18:54:40 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "../includes/camera.h"
#include "../libft/includes/libft.h"

void	init_cam(t_camera *camera, bool *set)
{
	camera->fov = camera->fov * (M_PI / 180.0f);
	camera->forward = vec3_normalize(camera->direction);
	if (camera->direction.y < 0.9 && camera->direction.y > -0.9)
	{
		camera->right = vec3_normalize(vec3_cross((t_vec3){0.0, 1.0, 0.0}, \
						camera->forward));
		camera->up = vec3_normalize(vec3_cross(camera->right, camera->forward));
	}
	else
	{
		camera->up = vec3_normalize(vec3_cross((t_vec3){1.0, 0.0, 0.0}, \
						camera->forward));
		camera->right = vec3_normalize(vec3_cross(camera->up, camera->forward));
	}
	*set = true;
}

void	set_projection_plane(t_camera *camera)
{
	static bool		set = false;
	t_vec3			tmp;

	camera->direction = vec3_normalize(camera->direction);
	camera->aspect_ratio = camera->win_size[0] / camera->win_size[1];
	if (!set)
		init_cam(camera, &set);
	camera->width = (2.0 * tan(camera->fov * 0.5));
	camera->height = (camera->width / camera->aspect_ratio);
	if (camera->axe == 'x')
	{
		camera->forward = camera->direction;
		camera->up = vec3_normalize(vec3_cross(camera->right, camera->forward));
	}
	else if (camera->axe == 'y')
	{
		camera->forward = camera->direction;
		camera->right = vec3_normalize(vec3_cross(camera->forward, camera->up));
	}
	camera->axe = 0;
	camera->center = vec3_add(camera->origin, camera->forward);
	camera->u = vec3_mul_scalar(camera->right, camera->width * 0.5);
	camera->v = vec3_mul_scalar(camera->up, camera->height * 0.5);
	tmp = vec3_sub(camera->center, camera->u);
	camera->lower_left_corner = vec3_sub(tmp, camera->v);
}
