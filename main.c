/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:43:43 by adbouras          #+#    #+#             */
/*   Updated: 2025/01/29 13:47:25 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	_leaks(void){system("leaks cub3D");}

void	player_spawn(t_data *data)
{
	mlx_image_to_window(data->game, data->player->imge,
						data->player->x * TILE_SIZE + (TILE_SIZE / 2 - HITBOX),
						data->player->y * TILE_SIZE + (TILE_SIZE / 2 - HITBOX));
	mlx_set_cursor_mode(data->game, MLX_MOUSE_HIDDEN);
	if (mlx_image_to_window(data->game, data->frame, 0, 0) == -1)
		ft_exit(data, 2, true);
	if (mlx_image_to_window(data->game, data->minimap, 20, HEIGHT - MINI_MAP_HEIGHT - 20) == -1)
		ft_exit(data, 2, true);
	data->tx = mlx_load_png("assets/petition.png");
	data->im = mlx_texture_to_image(data->game, data->tx);
	// mlx_resize_image(data->im, 300, 450);
	if (mlx_image_to_window(data->game, data->im, WIDTH / 2, HEIGHT - data->im->height) == -1)
		ft_exit(data, 2, true);
}

// void	sprite(void *param)
// {
// 	t_data	*data;
// 	static int count;
	
// 	data = (t_data *)param;
	
// }

int	main(int ac, char **av)
{
	t_data	data;

	(void) ac;
	// atexit(_leaks);
	init_data(&data, av[1]);
	player_spawn(&data);
	for (int i = 0; data.parsed_map[i]; i++)
		printf("%s\n", data.parsed_map[i]);
	mlx_loop_hook(data.game, game_loop, &data);
	// mlx_loop_hook(data.game, sprite, &data);
	mlx_close_hook(data.game, close_game, &data);
	mlx_loop(data.game);
	mlx_terminate(data.game);
}
