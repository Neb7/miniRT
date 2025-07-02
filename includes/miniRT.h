/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:57:09 by llemmel           #+#    #+#             */
/*   Updated: 2025/05/27 14:17:08 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>
# include <math.h>
# include <pthread.h>
# include "../libft/includes/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

# include "vec3.h"
# include "scene.h"

# ifndef WIN_WIDTH
#  define WIN_WIDTH 1920
# endif

# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 1080
# endif

# define FLT_MAX 3.402823466e+38F

# define SHININESS 10.0f
# define SPEC_STRENGHT 0.3f

typedef struct s_object		t_object;
typedef struct s_scene		t_scene;
typedef struct s_hit_point	t_hit_point;
typedef struct s_thread		t_thread;

// utils
void	ft_put_pixel(mlx_image_t *img, int coord[2], \
					t_vec3 color, uint8_t alpha);

t_vec3	get_object_color(const t_object *object);
t_vec3	get_object_color_hit(const t_hit_point *hit);
t_vec3	get_dir(t_object *object);
bool	vec3_point_close(t_point a, t_point b, \
	t_object *object, float delta_time);
t_vec3	get_object_origin(const t_object *object);
void	move(t_object *object, float delta_time);

t_vec3	calc_light(const t_scene *scene, const t_hit_point *hit_point);
void	init_image(t_scene *scene);
void	display_window(t_scene *scene);
bool	wait_start(t_thread	*thread);
void	renderer(t_scene *scene);

// debug.c
void	print_vec3_2(t_vec3 vec, const char *name);

#endif