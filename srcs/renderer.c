/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:07:13 by llemmel           #+#    #+#             */
/*   Updated: 2025/05/21 15:37:10 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
#include "../includes/camera.h"

t_vec3	render_scene(t_scene *scene, t_ray *ray)
{
	t_hit_point	hit_point;

	hit_point.t = FLT_MAX;
	get_closest_hit(ray, scene->objects, &hit_point, NULL);
	if (hit_point.t < EPSILON || !hit_point.object)
		return (scene->bg_color);
	else
		return (calc_light(scene, &hit_point));
}

void	init_image(t_scene *scene)
{
	scene->win.image = mlx_new_image(scene->win.mlx, \
		scene->win.mlx->width, scene->win.mlx->height);
	if (!scene->win.image)
	{
		printf("Failed to create image\n");
		return ;
	}
}

void	display_window(t_scene *scene)
{
	mlx_image_t		*img;
	size_t			i;

	i = -1;
	img = mlx_put_string(scene->win.mlx, scene->actual_name, 32, 32);
	while (img && ++i < img->height)
	{
		ft_memcpy(scene->win.image->pixels + \
			(((32 + i) * scene->win.image->width * sizeof(int32_t)) \
			+ (32 * sizeof(int32_t))), img->pixels + \
			(i * img->width * sizeof(int32_t)), img->width * sizeof(int32_t));
	}
	mlx_image_to_window(scene->win.mlx, scene->win.image, 0, 0);
	mlx_delete_image(scene->win.mlx, img);
}

void	renderer(t_scene *scene)
{
	int					p[2];
	t_vec3				color;
	t_ray				ray;
	double				start;

	if (!scene->win.image)
		init_image(scene);
	set_projection_plane(&scene->camera);
	start = mlx_get_time();
	p[1] = 0;
	while (p[1] < scene->win.mlx->height)
	{
		p[0] = 0;
		while (p[0] < scene->win.mlx->width)
		{
			ray = generate_ray(&scene->camera, p[0], p[1]);
			color = render_scene(scene, &ray);
			ft_put_pixel(scene->win.image, p, color, 0xFF);
			++p[0];
		}
		++p[1];
	}
	display_window(scene);
	printf("\033[1;36mRender: %fms\033[0m\n", (mlx_get_time() - start) * 1000);
}
