/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:43:43 by adbouras          #+#    #+#             */
/*   Updated: 2025/01/18 18:06:57 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	var_check(t_data *data)
{
	int i = 0;

	printf(" ----------- MAP -----------\n%s\n\n", data->map);
	while (data->map_arr[i]) {
		printf("%s\n", data->map_arr[i++]);
	}
	printf("map height: %d.\n", data->map_height);
	data->game ? printf("\nData.game is good\n") : printf("\nData.game is NOT good\n");
	printf("\twindow width: %d\n\twindow height: %d.\n", data->game->width, data->game->height);
	data->wall ? printf("\nData.wall is good\n") : printf("\nData.wall is NOT good\n");
	data->space ? printf("\nData.space is good\n") : printf("\nData.space is NOT good\n");
	data->blank ? printf("\nData.blank is good\n") : printf("\nData.blank is NOT good\n");
	data->render ? printf("\nData.render is good\n") : printf("\nData.render is NOT good\n");
	data->player ? printf("\nData.player is good\n") : printf("\nData.player is NOT good\n");
	printf("\tplayer x: %d, player y: %d.\n", data->player->x, data->player->y);
	printf("\tplayer view angle: %f.\n", data->player->rot_angle);
	printf("\tplayer rotation speed: %f.\n", data->player->rot_speed);
	data->ray ? printf("\nData.ray is good\n") : printf("\nData.ray is NOT good\n");
	printf("\tray angle: %f\n", data->ray->angle);
	printf("\tray distance: %f\n", data->ray->distance);
}

void	game_loop(void *param)
{
	t_data	*data;

	data = (t_data*) param;
	// handle render image
	mlx_delete_image(data->game->window, data->render);
	data->render = mlx_new_image(data->game->window, WIDTH, HEIGHT);
	player_hook(data);
	raycasting(data);
	mlx_image_to_window(data->game->window, data->render, 0, 0);
}

int	main(int ac, char **av)
{
	t_data	data;

	(void) ac;
	init_data(&data, av[1]);
	draw_minimap(&data);
	mlx_loop_hook(data.game->window, game_loop, &data);
	mlx_loop(data.game->window);
	// var_check(&data);
}
