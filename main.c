/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: starscourge <starscourge@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:43:43 by adbouras          #+#    #+#             */
/*   Updated: 2025/01/19 12:38:11 by starscourge      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

// void	var_check(t_data *data)
// {
// 	int i = 0;

// 	printf(" ----------- MAP -----------\n%s\n\n", data->map);
// 	while (data->map_arr[i]) {
// 		printf("%s\n", data->map_arr[i++]);
// 	}
// 	printf("map height: %d.\n", data->map_height);
// 	data->game ? printf("\nData.game is good\n") : printf("\nData.game is NOT good\n");
// 	printf("\twindow width: %d\n\twindow height: %d.\n", data->game->width, data->game->height);
// 	data->wall ? printf("\nData.wall is good\n") : printf("\nData.wall is NOT good\n");
// 	data->space ? printf("\nData.space is good\n") : printf("\nData.space is NOT good\n");
// 	data->blank ? printf("\nData.blank is good\n") : printf("\nData.blank is NOT good\n");
// 	data->frame ? printf("\nData.frame is good\n") : printf("\nData.frame is NOT good\n");
// 	data->player ? printf("\nData.player is good\n") : printf("\nData.player is NOT good\n");
// 	printf("\tplayer x: %d, player y: %d.\n", data->player->x, data->player->y);
// 	printf("\tplayer view angle: %f.\n", data->player->rot_angle);
// 	data->ray ? printf("\nData.ray is good\n") : printf("\nData.ray is NOT good\n");
// 	printf("\tray angle: %f\n", data->ray->angle);
// 	printf("\tray distance: %f\n", data->ray->distance);
// }

void	game_loop(void *param)
{
	t_data	*data;

	data = (t_data*) param;
	// handle frame image
	mlx_delete_image(data->game->window, data->frame);
	data->frame = mlx_new_image(data->game->window, WIDTH, HEIGHT);
	player_hook(data);
	raycasting(data);
	mlx_image_to_window(data->game->window, data->frame, 0, 0);
}

int	main(int ac, char **av)
{
	t_data	data;

	(void) ac;
	init_data(&data, av[1]);
	parse_map(data);
	draw_minimap(&data);
	mlx_loop_hook(data.game->window, game_loop, &data);
	mlx_loop(data.game->window);
	// var_check(&data);
}
