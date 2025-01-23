/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:43:43 by adbouras          #+#    #+#             */
/*   Updated: 2025/01/23 10:28:59 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	_leaks(void){system("leaks cub3D");}

void	player_spawn(t_data *data)
{
	mlx_image_to_window(data->game, data->player->imge,
						data->player->x * TILE_SIZE + (TILE_SIZE / 2 - HITBOX),
						data->player->y * TILE_SIZE + (TILE_SIZE / 2 - HITBOX));
}

int	main(int ac, char **av)
{
	t_data	data;

	(void) ac;
	// atexit(_leaks);
	init_data(&data, av[1]);
	player_spawn(&data);
	mlx_loop_hook(data.game, game_loop, &data);
	mlx_close_hook(data.game, close_game, &data);
	mlx_loop(data.game);
	mlx_terminate(data.game);
}
