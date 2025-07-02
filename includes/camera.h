/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:29:06 by llemmel           #+#    #+#             */
/*   Updated: 2025/05/27 14:16:29 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include <math.h>
# include "vec3.h"

# include <stdio.h>

# ifndef T_CAMERA
#  define T_CAMERA

typedef struct s_camera
{
	t_point		origin;
	t_vec3		direction;
	t_vec3		forward;
	t_vec3		right;
	t_vec3		up;
	float		win_size[2];
	float		matice[3][3];
	t_point		center;
	t_vec3		u;
	t_vec3		v;
	t_vec3		lower_left_corner;

	float		width;
	float		height;
	float		aspect_ratio;
	float		fov;
	char		axe;
}	t_camera;

# endif

typedef struct s_ray
{
	t_point	origin;
	t_vec3	direction;
}	t_ray;

typedef struct s_object	t_object;

typedef struct s_hit_point
{
	t_ray		*ray;
	float		t;
	t_point		p;
	t_object	*object;
	int			hit_type;
}	t_hit_point;

void		set_projection_plane(t_camera *camera);

t_ray		generate_ray(const t_camera *camera, \
							const float px, const float py);
t_point		ray_at(const t_ray *ray, const float t);

#endif