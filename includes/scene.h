/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:56:00 by llemmel           #+#    #+#             */
/*   Updated: 2025/05/27 14:19:45 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include <math.h>
# include "vec3.h"
# include "miniRT.h"
# include "../libft/includes/libft.h"

# include <stdint.h>
# include "camera.h"

# define EPSILON 1.0e-4

# define MAX_THREADS 24

# ifndef T_SCENE
#  define T_SCENE

typedef enum e_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE,	//bonus
	UNKNOWN
}	t_type;

typedef struct s_sphere
{
	t_point	origin;
	float	radius;
	float	squarred_radius;
	t_vec3	color;
	bool	bump;
}	t_sphere;

typedef struct s_plane
{
	t_point	origin;
	t_vec3	normal;
	t_vec3	color;
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;
	bool	checkerboard;
}	t_plane;

typedef struct s_cylinder
{
	t_vec3	pos;
	t_vec3	orientation;
	float	radius;
	float	diameter;
	float	height;
	t_vec3	color;
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;
}	t_cylinder;

typedef struct s_cylinder	t_cone;

typedef struct s_light
{
	t_point		origin;
	float		brightness;
	t_vec3		color;
	bool		check;
}	t_light;

typedef struct s_ambiant_ligth
{
	float	ratio;
	t_vec3	color;
}	t_ambiant_ligth;

typedef struct s_check
{
	int	ambient;
	int	cam;
	int	light;
}	t_check;

typedef struct s_object
{
	t_type	type;
	void	*data;
	// * Bonus pour ajouter le mouvement des object dans le temps
	t_vec3	*pos_list;
	size_t	i;
	size_t	max;
	t_vec3	dir;
	float	speed;
}	t_object;

typedef struct s_edit_object
{
	t_object	*ac_o;
	size_t		i;
}	t_edit_object;

typedef struct s_edit_light
{
	t_light	*ac_l;
	size_t	i;
}	t_edit_light;

typedef struct s_window
{
	mlx_t		*mlx;
	mlx_image_t	*image;
}	t_windows;

typedef enum e_state
{
	WAIT,
	RENDER,
	DONE,
	ERROR
}	t_state;

typedef struct s_scene		t_scene;

typedef struct s_thread
{
	pthread_t		th_id;
	int				index;
	t_state			state;
	void			*(*routine)(void *);
	t_scene			*scene;
}	t_thread;

typedef struct s_scene
{
	t_vec3			bg_color;
	t_ambiant_ligth	ambiant_ligth;
	t_camera		camera;
	t_vector		*lights;
	t_vector		*objects;
	t_check			nbr_ele;
	int				fd;
	t_windows		win;
	t_edit_object	actual_object;
	t_edit_light	actual_light;
	bool			on_object;
	bool			light_yagami;
	char			actual_name[10];

	//* --- bonus
	t_thread		threads[MAX_THREADS];
	pthread_mutex_t	mutex;
	long			nb_threads;
	double			last_frame_time;
	double			delta_time;
}	t_scene;

# endif

// shape/object.c
t_vec3			get_normal(const t_hit_point *hit_point);
void			get_closest_hit(const t_ray *ray, const t_vector *objects, \
							t_hit_point *closest_hit, const t_object *ignore);

// shape/sphere.c
void			ray_hit_sphere(const t_ray *ray, const t_sphere *sphere, \
							const void *addr, t_hit_point *hit_point);
t_vec3			normal_sphere(const t_hit_point *hit_point);
bool			light_in_sphere(const t_light *light, const t_sphere *sphere);

// shape/plane.c
void			ray_hit_plane(const t_ray *ray, const t_plane *plane, \
							const void *addr, t_hit_point *hit_point);
t_vec3			normal_plane(const t_hit_point *hit_point);
bool			light_in_plane(const t_light *light, const t_plane *plane);

// shape/cylinder_utils.c
bool			hit_core(float coeff[5], const t_cylinder *cyl, \
	const t_ray *ray, float *t_out);
bool			hit_bottop(const t_cylinder *cyl, const t_ray *ray, \
							bool bottom, float *t_out);
void			init_coeff(const t_ray *ray, const t_cylinder *cyl, \
							float coeff[5]);

// shape/cylinder.c
void			ray_hit_cylinder(const t_ray *ray, const t_cylinder *cylinder, \
							const void *addr, t_hit_point *hit_point);
t_vec3			normal_cylinder(const t_hit_point *hit_point);
bool			light_in_cylinder(const t_light *light, \
								const t_cylinder *cylinder);

void			ray_hit_cone(const t_ray *ray, const t_cone *cone, \
						const void *obj_addr, t_hit_point *hit_point);
t_vec3			normal_cone(const t_hit_point *hit_point);

// perlin_noise.c
float			perlin_noise_at_point(t_vec3 p);

// checker_bump.c
extern float	lerp(float a, float b, float t);
extern float	perlin_noise_interpolation(float t);
t_vec3			checkerboard_plane(const t_hit_point *hit_point);
t_vec3			bump_map_sphere(const t_hit_point *hit_point);

/*cam_move*/

bool			ft_cam_moves(t_scene *scene, mlx_key_data_t keydata);

/*light_move*/

bool			ft_light_moves(t_scene *scene, mlx_key_data_t keydata);

/*object_move*/

bool			ft_object_moves(t_scene *scene, mlx_key_data_t keydata);

#endif