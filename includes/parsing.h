/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:09:55 by benpicar          #+#    #+#             */
/*   Updated: 2025/05/27 14:17:47 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/includes/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "scene.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <strings.h>
# include <math.h>

# define ERR_ARG "Error: Wrong format\nTry: ./miniRT [FILE].rt\n"
# define ERR_NAME "Error\nMap name doesn't end with '.rt'\n"
# define ERR_MALLOC "Error\nAllocation fail\n"
# define ERR_MUTEX "Error\nMutex initialization failed\n"
# define ERR_OPN "Error\nCan't open file\n"
# define ERR_READ "Error\nCan't read file or empty file\n"
# define ERR_UNKN "Error\nUnknow id the in file\n"
# define ERR_DEC "Error\nMore than one '.' in the number\n"
# define ERR_CARNUM "Error\nNot a numeric character in a number\n"
# define ERR_LIG_R "Error\nRatio of the ambient light or the light must be in \
[0.0;1.0]\n"
# define ERR_COL "Error\nColors must be in [0;255]\n"
# define ERR_TOO_L "Error\nToo much information in one line\n"
# define ERR_ORI "Error\nOrientation value must be in [-1;1] \
and cannot be {0, 0, 0}\n"
# define ERR_FOV "Error\nFOV must be in [0;180]\n"
# define ERR_WRO "Error\nWronmg identifier or wrong format\n"
# define ERR_CAM_AN "Error\nAngle of the camera must be in [0;180]\n"
# define ERR_MIS "Error\n(t_hit_point){NULL, -1.0f, (t_point){0, 0, 0}, \
NULL, 0}ing or wrong information\n"
# define ERR_DIAM "Error\nDiameter must be positive\n"
# define ERR_NBA "Error\nDifferent than 1 ambient light\n"
# define ERR_NBC "Error\nDifferent than 1 camera\n"
# define ERR_NBL "Error\nDifferent than 1 light\n"
# define ERR_OVE "Error\nValue overflow or underflow\n"

# define SPEED 1.0f
# define ROTATE_SPEED 9.0f

typedef struct s_atof
{
	float	res;
	float	div;
	float	frac;
	int		j;
	float	sign;
	int		dec;
}	t_atof;

/*ft_atof*/

float	ft_atof(char *nbr, int *i, t_scene *scene);

/*ft_free*/

void	ft_exit_error(t_scene *scene, char *err);
void	ft_free_scene(t_scene *scene);

/*ft_ambient*/

void	ft_add_ambient(t_scene *scene, char *buf, int j);

/*ft_cam*/

void	ft_add_camera(t_scene *scene, char *buf, int j);

/*ft_cylinder*/

void	ft_add_cylinder(t_scene *scene, char *buf, int j);

/*ft_light*/

void	ft_add_light(t_scene *scene, char *buf, int j);

/*ft_plane*/

void	ft_add_plane(t_scene *scene, char *buf, int j);

/*ft_sphere*/

void	ft_add_sphere(t_scene *scene, char *buf, int j);

/*ft_parsing_utils*/

bool	ft_add_check_char(char *buf, int i);
bool	ft_add_check(char *buf, int i);
void	ft_next_info(char *buf, int *i);
bool	ft_have_good_val(t_vec3 vec, float max, float min);
bool	dir_is_valid(t_vec3 dir);

/*ft_parsing*/

bool	ft_this_is_sparsing(char *file_name, t_scene *scene);

/*ft_cam_move*/

bool	ft_cam_moves(t_scene *scene, mlx_key_data_t keydata);

/*ft_objet_move_utils*/

bool	ft_objet_to_light(t_scene *scene);
bool	ft_objet_to_cam(t_scene *scene);

/*rotation*/
bool	ft_rotate_plane(t_plane *pl, float theta, t_vec3 axe);
bool	ft_rotate_cylinder(t_cylinder *cy, float theta, t_vec3 axe);

t_vec3	ft_rotate_y(t_vec3 v, float theta);
t_vec3	ft_rotate_x(t_vec3 v, float theta);
t_vec3	ft_rotate_z(t_vec3 v, float theta);
t_vec3	ft_rotate_vec3(t_vec3 v, t_vec3 axis, float angle_deg);

void	print_scene(t_scene *scene);

void	ft_add_cone(t_scene *scene, char *buf, int j);

void	ft_add_objet_move(t_scene *scene, char *buf, int *i, t_object *new);

bool	ft_check_press_move(mlx_key_data_t keydata);

#endif