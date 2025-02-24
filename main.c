/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:43:43 by adbouras          #+#    #+#             */
/*   Updated: 2025/02/24 12:56:44 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	_leaks(void){system("leaks cub3D");}

void	player_spawn(t_data *data)
{
	mlx_image_to_window(data->game, data->player->imge,
						data->player->x * TILE_SIZE + (TILE_SIZE / 2 - HITBOX),
						data->player->y * TILE_SIZE + (TILE_SIZE / 2 - HITBOX));
	if (mlx_image_to_window(data->game, data->frame, 0, 0) == -1)
		ft_exit(data, 2, true);
	if (mlx_image_to_window(data->game, data->minimap, 20, HEIGHT - MINI_MAP_HEIGHT - 20) == -1)
		ft_exit(data, 2, true);
	data->p_txtre = mlx_load_png("assets/sprites/1.png");
	data->p_asset = mlx_texture_to_image(data->game, data->p_txtre);
	mlx_resize_image(data->p_asset, WIDTH * 0.7, HEIGHT * 0.7);
	mlx_image_to_window(data->game, data->p_asset, \
						(WIDTH / 2) - data->p_asset->height, \
						HEIGHT - data->p_asset->height);
}

int	main(int ac, char **av)
{
	t_data	data;

	(void) ac;
	atexit(_leaks);
	init_data(&data, av[1]);
	player_spawn(&data);
	mlx_loop_hook(data.game, game_loop, &data);
	mlx_close_hook(data.game, close_game, &data);
	mlx_loop(data.game);
	mlx_terminate(data.game);
}
