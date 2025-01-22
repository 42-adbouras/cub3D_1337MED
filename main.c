/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:43:43 by adbouras          #+#    #+#             */
/*   Updated: 2025/01/22 18:52:05 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	draw_walls(t_data *data)
{
	int	ray;

	ray = -1;
	while (++ray < RAYS)
		render_strip(data, ray, data->text[ray].distance);
}

void	draw_rays(t_data *data)
{
	int	ray;
	
	ray = -1;
	while (++ray < RAYS)
		draw_line(data->frame,
				(data->player->x + (HITBOX / 2)) * MAP_FACT,
				(data->player->y + (HITBOX / 2)) * MAP_FACT,
				data->text[ray].wall_hit_x * MAP_FACT,
				data->text[ray].wall_hit_y * MAP_FACT,
				rgba(192, 242, 255, 255));
}

void	game_loop(void *param)
{
	t_data	*data;

	data = (t_data*) param;
	player_hook(data);
	raycasting(data);

	mlx_delete_image(data->game, data->frame);
	data->frame = mlx_new_image(data->game, WIDTH, HEIGHT);

	draw_bg(data);
	draw_walls(data);
	if (data->mini_map)
	{
		draw_minimap(data);
		draw_rays(data);
	}

	mlx_image_to_window(data->game, data->frame, 0, 0);
}

void	_leaks(void){system("leaks cub3D");}

int	main(int ac, char **av)
{
	t_data	data;

	(void) ac;
	atexit(_leaks);
	init_data(&data, av[1]);
	mlx_image_to_window(data.game, data.player->imge,
						data.player->x * TILE_SIZE + (TILE_SIZE / 2 - HITBOX),
						data.player->y * TILE_SIZE + (TILE_SIZE / 2 - HITBOX));
	mlx_loop_hook(data.game, game_loop, &data);
	mlx_close_hook(data.game, close_game, &data);
	mlx_loop(data.game);
	mlx_terminate(data.game);
}
