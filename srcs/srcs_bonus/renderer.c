/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:00:21 by llemmel           #+#    #+#             */
/*   Updated: 2025/05/21 15:36:25 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
#include "../includes/camera.h"
#include "../includes/parsing.h"
#include <unistd.h>

static void	*render_routine(void *arg);

/**
 * @brief	Init all the threads in the scene and set them to WAIT.
 * Get the number of cores available on the system and set the number of threads
 * 
 * @param	scene The scene containing the threads
 */
static void	init_threads(t_scene *scene)
{
	int	i;

	i = -1;
	scene->nb_threads = sysconf(_SC_NPROCESSORS_ONLN);
	if (scene->nb_threads > MAX_THREADS)
		scene->nb_threads = MAX_THREADS;
	while (++i < scene->nb_threads)
		scene->threads[i] = (t_thread){0, i, WAIT, &render_routine, scene};
}

/**
 * @brief	Create a threads all the threads to render. 
 * 	If an error occurs, all the threads are set to ERROR.
 * 	If success, all the threads are set to RENDER.		
 * 
 * @param	scene The scene to render
 */
static void	create_threads(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->nb_threads)
	{
		if (pthread_create(&scene->threads[i].th_id, \
			NULL, scene->threads[i].routine, &scene->threads[i]) != 0)
		{
			while (i >= 0)
			{
				pthread_mutex_lock(&scene->mutex);
				scene->threads[i--].state = ERROR;
				pthread_mutex_unlock(&scene->mutex);
			}
			ft_free_scene(scene);
		}
		i++;
	}
	while (i >= 0)
	{
		pthread_mutex_lock(&scene->mutex);
		scene->threads[i--].state = RENDER;
		pthread_mutex_unlock(&scene->mutex);
	}
}

/**
 * @brief	Get the closest hit point in the scene and calculate the color if 
 *			 the ray hit an object, otherwise return the background color.
 * 
 * @param	scene The scene to render
 * @param	ray	 The ray to test
 * @return	t_vec3 The color of the pixel
 */
static t_vec3	render_scene(t_scene *scene, t_ray *ray)
{
	t_hit_point	hit_point;

	hit_point.t = FLT_MAX;
	get_closest_hit(ray, scene->objects, &hit_point, NULL);
	if (hit_point.t < EPSILON || !hit_point.object)
		return (scene->bg_color);
	else
		return (calc_light(scene, &hit_point));
}

/**
 * @brief	Routine for each thread to render the scene
 * 
 * Each thread will render a part of the scene.
 * 
 * @param	arg	Pointer to the thread structure
 * @return	void* NULL 
 */
static void	*render_routine(void *arg)
{
	t_thread		*thread;
	t_scene			*scene;
	int				p[3];
	t_vec3			color;
	t_ray			ray;

	thread = (t_thread *)arg;
	scene = thread->scene;
	p[1] = (scene->win.image->height / scene->nb_threads * thread->index) - 1;
	p[2] = scene->win.image->height / scene->nb_threads * (thread->index + 1);
	if (!wait_start(thread))
		return (NULL);
	while (++p[1] < p[2])
	{
		p[0] = -1;
		while (++p[0] < (int)scene->win.image->width)
		{
			ray = generate_ray(&scene->camera, p[0], p[1]);
			color = render_scene(scene, &ray);
			ft_put_pixel(scene->win.image, p, color, 0xFF);
		}
	}
	thread->state = DONE;
	return (NULL);
}

/**
 * @brief	Render the scene
 * 
 * This function is the main render function. It will create the threads
 * to render the scene. At the end, it will display the image in the window.
 * 
 * @param	scene scene to render
 */
void	renderer(t_scene *scene)
{
	double	start;
	double	now;
	long	i;

	if (!scene->win.image)
		init_image(scene);
	set_projection_plane(&scene->camera);
	init_threads(scene);
	start = mlx_get_time();
	create_threads(scene);
	i = -1;
	while (++i < scene->nb_threads)
		pthread_join(scene->threads[i].th_id, NULL);
	display_window(scene);
	now = mlx_get_time();
	printf("\033[1;36mRender: %.2fms\033[0m\n", (now - start) * 1000);
	scene->delta_time = now - scene->last_frame_time;
	scene->last_frame_time = now;
}
