/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:57:17 by llemmel           #+#    #+#             */
/*   Updated: 2025/05/21 16:00:47 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "Mlx_moi.h"
#include "parsing.h"

/**
 * @brief	Exit the program and free the scene
 * 
 * @param	param The scene to free
 */
static void	exit_hook(void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	ft_free_scene(scene);
	exit(EXIT_SUCCESS);
}

/**
 * @brief	Initialize the mlx
 * 
 * @param	scene containing the mlx
 */
static void	ft_init_win(t_scene *scene)
{
	scene->win.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "miniRT", true);
	if (!scene->win.mlx)
		return (ft_exit_error(scene, "Error\nInitialiation mlx fail\n"));
}

int	main(int argc, char **argv)
{
	t_scene	scene;

	ft_memset(&scene, 0, sizeof(t_scene));
	if (argc != 2)
	{
		ft_putstr_fd(ERR_ARG, 2);
		return (EXIT_FAILURE);
	}
	scene.objects = ft_new_vector(sizeof(t_object));
	if (!scene.objects)
		return (ft_putstr_fd(ERR_MALLOC, STDERR_FILENO), EXIT_FAILURE);
	scene.lights = ft_new_vector(sizeof(t_light));
	if (!scene.lights)
		return (ft_exit_error(&scene, ERR_MALLOC), EXIT_FAILURE);
	ft_memcpy(scene.actual_name, "Camera", 7);
	if (!ft_this_is_sparsing(argv[1], &scene))
		return (ft_free_scene(&scene), EXIT_FAILURE);
	ft_init_win(&scene);
	renderer(&scene);
	mlx_key_hook(scene.win.mlx, &my_keyhook, &scene);
	mlx_resize_hook(scene.win.mlx, &resize, &scene);
	mlx_close_hook(scene.win.mlx, exit_hook, &scene);
	mlx_loop(scene.win.mlx);
	return (0);
}
