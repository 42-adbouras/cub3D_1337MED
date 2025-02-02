/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:43:43 by adbouras          #+#    #+#             */
/*   Updated: 2025/02/01 15:35:20 by adbouras         ###   ########.fr       */
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
	data->tx = mlx_load_png("assets/sprites/1.png");
	data->im = mlx_texture_to_image(data->game, data->tx);
	mlx_resize_image(data->im, WIDTH * 0.7, HEIGHT * 0.7);
	// if (mlx_image_to_window(data->game, data->im, (WIDTH / 2) - data->im->height / 2, HEIGHT - data->im->height) == -1)
	// 	ft_exit(data, 2, true);
	for (int i = 0; i < NUM_SPRITES; i++)
	{
		mlx_resize_image(data->sprites.s_images[i], WIDTH * 0.7, HEIGHT * 0.7);
		mlx_image_to_window(data->game, data->sprites.s_images[i], (WIDTH / 2) - data->sprites.s_images[i]->height / 2, HEIGHT - data->sprites.s_images[i]->height);
		data->sprites.s_images[i]->enabled = false;
	}
}

void	import_frames(t_data *data)
{
	int		i;

	i = 0;
	while (i < NUM_SPRITES)
	{
		data->sprites.s_texture[i] = mlx_load_png(data->sprites.path[i]);
		if (!data->sprites.s_texture[i])
			ft_exit(data, 2, true);
		data->sprites.s_images[i] = mlx_texture_to_image(data->game, data->sprites.s_texture[i]);
		if (!data->sprites.s_images[i])
			ft_exit(data, 2, true);
		i++;
	}
}

void	load_sprites(t_data *data)
{
	char	*path;
	char	*temp;
	int		fd;

	path = NULL;
	fd = open("assets/sprites/sheet.txt", O_RDONLY);
	while (1)
	{
		temp = get_next_line(fd);
		if (!temp)
			break ;
		path = ft_strjoin(path, temp);
		free(temp);
	}
	data->sprites.path = ft_split_cub(path, '\n');
	free(path);
	close(fd);
	import_frames(data);
}

int	main(int ac, char **av)
{
	t_data	data;

	(void) ac;
	// atexit(_leaks);
	init_data(&data, av[1]);
	load_sprites(&data);
	player_spawn(&data);
	// for (int i = 0; data.parsed_map[i]; i++)
	// 	printf("%s\n", data.parsed_map[i]);
	mlx_loop_hook(data.game, game_loop, &data);
	mlx_close_hook(data.game, close_game, &data);
	mlx_loop(data.game);
	mlx_terminate(data.game);
}
