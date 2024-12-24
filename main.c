/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:29:26 by adbouras          #+#    #+#             */
/*   Updated: 2024/12/24 17:43:43 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	import_map(t_data **data, char *path)
{
	char	*line;
	int		fd;

	fd = open(path, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		(*data)->map = ft_strjoin((*data)->map, line);
		free(line);
	}
	close(fd);
}

// 'Encodes' four individual bytes into an int.
int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void	draw_tile(mlx_image_t *image, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			mlx_put_pixel(image, j, i, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_data	*data)
{
	char	**map_arr;
	int		i;
	int		j;

	i = 0;
	map_arr = ft_split(data->map, '\n');
	draw_tile(data->space, WHITE);
	draw_tile(data->blank, RED);
	draw_tile(data->wall, BLACK);
	while (map_arr[i])
	{
		j = 0;
		while (map_arr[i][j])
		{
			if (map_arr[i][j] == '1')
				mlx_image_to_window(data->game->window, data->wall, j * TILE_SIZE, i * TILE_SIZE);
			else if (map_arr[i][j] == '0')
				mlx_image_to_window(data->game->window, data->space, j * TILE_SIZE, i * TILE_SIZE);
			else if (map_arr[i][j] == 'N')
			{
				mlx_image_to_window(data->game->window, data->space, j * TILE_SIZE, i * TILE_SIZE);
				data->player_x = j;
				data->player_y = i;
			}
			else
				mlx_image_to_window(data->game->window, data->blank, j * TILE_SIZE, i * TILE_SIZE);
			j++;
		}
		i++;
	}
	mlx_image_to_window(data->game->window, data->player, data->player_x * TILE_SIZE, data->player_y * TILE_SIZE);
}

t_data	*init_data(void)
{
	t_data*			data;
	mlx_texture_t*	texture;

	data = malloc(sizeof(t_data));
	// null check!!
	data->map = NULL;
	data->game = malloc(sizeof(mlx_t));
	// null check!!
	data->game->width = WIDTH;
	data->game->height = HEIGHT;
	data->game->window = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	// return value
	data->wall = mlx_new_image(data->game->window, TILE_SIZE, TILE_SIZE);
	data->space = mlx_new_image(data->game->window, TILE_SIZE, TILE_SIZE);
	data->blank = mlx_new_image(data->game->window, TILE_SIZE, TILE_SIZE);
	// need a handler
	texture = mlx_load_png("assets/player.png");
	data->player = mlx_texture_to_image(data->game->window, texture);
	mlx_delete_texture(texture);
	return (data);
}

void	ft_key_hook(mlx_key_data_t key, void *param)
{
	t_data	*data;

	data = (t_data*)param;
	if (key.key == MLX_KEY_ESCAPE && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		exit(0);
	if (key.key == MLX_KEY_W && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		data->player->instances->y--;
	if (key.key == MLX_KEY_S && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		data->player->instances->y++;
	if (key.key == MLX_KEY_D && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		data->player->instances->x++;
	if (key.key == MLX_KEY_A && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		data->player->instances->x--;
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_data	*data;

	data = init_data();
	import_map(&data, av[1]);
	draw_minimap(data);
	printf("%d, %d\n", data->player_x, data->player_y);
	mlx_key_hook(data->game->window, ft_key_hook, data);
	mlx_loop(data->game->window);
	return (0);
}
