/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:29:26 by adbouras          #+#    #+#             */
/*   Updated: 2024/12/26 18:38:00 by adbouras         ###   ########.fr       */
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
	(*data)->map_arr = ft_split((*data)->map, '\n');
	close(fd);
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

void	draw_player(mlx_image_t *image)
{
	int	i;
	int	j;

	i = TILE_SIZE / 3;
	while (i < ((TILE_SIZE / 3) * 2))
	{
		j = TILE_SIZE / 3;
		while (j < ((TILE_SIZE / 3) * 2))
		{
			mlx_put_pixel(image, j, i, GREEN);
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
	draw_player(data->player->img);
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
				data->player->x = j;
				data->player->y = i;
			}
			else
				mlx_image_to_window(data->game->window, data->blank, j * TILE_SIZE, i * TILE_SIZE);
			j++;
		}
		i++;
	}
	mlx_image_to_window(data->game->window, data->player->img, data->player->x * TILE_SIZE, data->player->y * TILE_SIZE);
}

t_data	*init_data(void)
{
	t_data*			data;
	// mlx_texture_t*	texture;

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
	// texture = mlx_load_png("assets/player.png");
	data->player = malloc(sizeof(t_player));
	data->player->line = mlx_new_image(data->game->window, TILE_SIZE, TILE_SIZE);
	data->player->walk_dir = 0;
	data->player->turn_dir = 0;
	data->player->strafe_dir = 0;
	data->player->rot_speed = 2 * (M_PI / 180);
	data->player->rot_angle = M_PI / 2;
	data->player->move_speed = 2;
	data->player->img = mlx_new_image(data->game->window, TILE_SIZE, TILE_SIZE);
	// data->player->img = mlx_texture_to_image(data->game->window, texture);
	// mlx_delete_texture(texture);
	return (data);
}

bool	if_collision(char **map, int x, int y)
{
	int i;
	int j;

	i = roundf(x / 32);
	j = roundf(y / 32);
	if (map[j][i] == '1')
		return(true);
	return(false);
}

void	update_player_pos(t_data* data)
{
	data->player->rot_angle += data->player->turn_dir * data->player->rot_speed;

	double step = data->player->walk_dir * data->player->move_speed;
	double x = data->player->img->instances->x + cos(data->player->rot_angle) * step;
	double y = data->player->img->instances->y + sin(data->player->rot_angle) * step;
	(void)x;
	(void)y;
	// printf("=> %f, %d, %d.\n", data->player->rot_angle,(int)(y)/32,(int)(x)/32);
	if (data->map_arr[((int)(y)/32)][(int)(x)/32] != '1')
	{
		data->player->img->instances->x = x;
		data->player->img->instances->y = y;
	}
}

void	ft_key_hook(void *param)
{
	t_data	*data;

	data = (t_data*)param;
	if (mlx_is_key_down(data->game->window, MLX_KEY_ESCAPE))
		exit(0);
	if (mlx_is_key_down(data->game->window, MLX_KEY_W))
		data->player->walk_dir = 1;
	if (mlx_is_key_down(data->game->window, MLX_KEY_S))
		data->player->walk_dir = -1;
	if (mlx_is_key_down(data->game->window, MLX_KEY_D))
		data->player->img->instances->x += data->player->move_speed;
	if (mlx_is_key_down(data->game->window, MLX_KEY_A))
		data->player->img->instances->x -= data->player->move_speed;
	if (mlx_is_key_down(data->game->window, MLX_KEY_RIGHT))
		data->player->turn_dir = 1;
	if (mlx_is_key_down(data->game->window, MLX_KEY_LEFT))
		data->player->turn_dir = -1;
	
	update_player_pos(data);
	data->player->turn_dir = 0;
	data->player->walk_dir = 0;
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_data	*data;

	data = init_data();
	import_map(&data, av[1]);
	draw_minimap(data);
	// printf("%d, %d\n", data->player->x, data->player->y);
	mlx_loop_hook(data->game->window, ft_key_hook, data);
	mlx_loop(data->game->window);
	return (0);
}
