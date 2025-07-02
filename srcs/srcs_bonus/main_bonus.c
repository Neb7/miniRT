/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:48:13 by benpicar          #+#    #+#             */
/*   Updated: 2025/05/21 16:01:09 by benpicar         ###   ########.fr       */
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
		ft_exit_error(scene, "Error\nInitialiation mlx fail\n");
}

/**
 * @brief	Initialize the scene
 * 
 * @param	scene the scene to initialize
 * @param	filename the name of the file to parse
 * @return	int EXIT_SUCCESS if success, EXIT_FAILURE if error
 */
static int	init_scene(t_scene *scene, char *filename)
{
	ft_memset(scene, 0, sizeof(t_scene));
	scene->objects = ft_new_vector(sizeof(t_object));
	if (!scene->objects)
		return (ft_putstr_fd(ERR_MALLOC, STDERR_FILENO), EXIT_FAILURE);
	scene->lights = ft_new_vector(sizeof(t_light));
	if (!scene->lights)
		return (ft_exit_error(scene, ERR_MALLOC), EXIT_FAILURE);
	ft_memcpy(scene->actual_name, "Camera", 7);
	if (!ft_this_is_sparsing(filename, scene))
		return (ft_free_scene(scene), EXIT_FAILURE);
	if (pthread_mutex_init(&scene->mutex, NULL) != 0)
		return (ft_putstr_fd(ERR_MUTEX, STDERR_FILENO), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @brief	Main function of the program
 */
int	main(int argc, char **argv)
{
	t_scene	scene;

	if (argc != 2)
	{
		ft_putstr_fd(ERR_ARG, 2);
		return (EXIT_FAILURE);
	}
	if (init_scene(&scene, argv[1]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_init_win(&scene);
	renderer(&scene);
	mlx_key_hook(scene.win.mlx, &my_keyhook, &scene);
	mlx_resize_hook(scene.win.mlx, &resize, &scene);
	mlx_loop_hook(scene.win.mlx, &main_loop, &scene);
	mlx_close_hook(scene.win.mlx, exit_hook, &scene);
	mlx_loop(scene.win.mlx);
	return (0);
}
