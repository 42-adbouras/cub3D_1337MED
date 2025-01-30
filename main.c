/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:43:43 by adbouras          #+#    #+#             */
/*   Updated: 2025/01/30 23:00:34 by adbouras         ###   ########.fr       */
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
	// data->tx = mlx_load_png("assets/petition.png");
	// data->im = mlx_texture_to_image(data->game, data->tx);
	// mlx_resize_image(data->im, 300, 450);
	// if (mlx_image_to_window(data->game, data->im, WIDTH / 2, HEIGHT - data->im->height) == -1)
	// 	ft_exit(data, 2, true);
	for (int i = 0; i < NUM_SPRITES; i++)
	{
		mlx_resize_image(data->sprites.s_images[i], WIDTH * 0.7, HEIGHT * 0.7);
		mlx_image_to_window(data->game, data->sprites.s_images[i], (WIDTH / 2) - data->sprites.s_images[i]->height / 2, HEIGHT - data->sprites.s_images[i]->height);
		data->sprites.s_images[i]->enabled = false;
	}
}

void	load_sprites(t_data *data)
{
	char	*path[NUM_SPRITES] = {
		"assets/sptites/1.png", "assets/sptites/2.png", "assets/sptites/3.png",
        "assets/sptites/4.png", "assets/sptites/5.png", "assets/sptites/6.png",
        "assets/sptites/7.png", "assets/sptites/8.png", "assets/sptites/9.png",
        "assets/sptites/10.png", "assets/sptites/11.png", "assets/sptites/12.png",
        "assets/sptites/13.png", "assets/sptites/14.png", "assets/sptites/15.png",
        "assets/sptites/16.png", "assets/sptites/17.png", "assets/sptites/18.png"
    };
	// data->sprites.s_texture[0] = mlx_load_png("assets/sptites/1.png");
	// data->sprites.s_texture[1] = mlx_load_png("assets/sptites/2.png");
	// data->sprites.s_texture[2] = mlx_load_png("assets/sptites/3.png");
	// data->sprites.s_texture[3] = mlx_load_png("assets/sptites/4.png");
	// data->sprites.s_texture[4] = mlx_load_png("assets/sptites/5.png");
	// data->sprites.s_texture[5] = mlx_load_png("assets/sptites/6.png");
	// data->sprites.s_texture[6] = mlx_load_png("assets/sptites/7.png");
	// data->sprites.s_texture[7] = mlx_load_png("assets/sptites/8.png");
	// data->sprites.s_texture[8] = mlx_load_png("assets/sptites/9.png");
	// data->sprites.s_texture[9] = mlx_load_png("assets/sptites/10.png");
	// data->sprites.s_texture[10] = mlx_load_png("assets/sptites/11.png");
	// data->sprites.s_texture[11] = mlx_load_png("assets/sptites/12.png");
	// data->sprites.s_texture[12] = mlx_load_png("assets/sptites/13.png");
	// data->sprites.s_texture[13] = mlx_load_png("assets/sptites/14.png");
	// data->sprites.s_texture[14] = mlx_load_png("assets/sptites/15.png");
	// data->sprites.s_texture[15] = mlx_load_png("assets/sptites/16.png");
	// data->sprites.s_texture[16] = mlx_load_png("assets/sptites/17.png");
	// data->sprites.s_texture[17] = mlx_load_png("assets/sptites/18.png");
	int	i = 0;
	while (i < NUM_SPRITES)
	{
		data->sprites.s_texture[i] = mlx_load_png(path[i]);
		data->sprites.s_images[i] = mlx_texture_to_image(data->game, data->sprites.s_texture[i]);
		
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	(void) ac;
	// atexit(_leaks);
	init_data(&data, av[1]);
	load_sprites(&data);
	player_spawn(&data);
	for (int i = 0; data.parsed_map[i]; i++)
		printf("%s\n", data.parsed_map[i]);
	mlx_loop_hook(data.game, game_loop, &data);
	mlx_close_hook(data.game, close_game, &data);
	mlx_loop(data.game);
	mlx_terminate(data.game);
}
