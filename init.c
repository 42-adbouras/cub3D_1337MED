/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:27:00 by adbouras          #+#    #+#             */
/*   Updated: 2025/01/10 20:10:44 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	init_data(t_data *data, char *arg)
{
	import_map(&data, arg);
	load_game(&data);
	load_player(&data);
	load_images(&data);
	data->ray = malloc(sizeof(t_ray));
}

void	load_game(t_data **data)
{
	(*data)->game = malloc(sizeof(mlx_t));
	if (!(*data)->game)
	{
		perror("Bad malloc on <load_game>");
		free(*data);
		exit(1);
	}
	(*data)->game->width = WIDTH;
	(*data)->game->height = HEIGHT;
	(*data)->game->window = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!(*data)->game->window)
	{
		perror("Failed while loading game window");
		free(*data);
		exit(1);
	}
}

void	get_player_position(t_data *data, int *x, int *y)
{
	int		i;
	int		j;

	i = 0;
	printf("here\n");
	while (data->map_arr[i])
	{
		j = 0;
		while (data->map_arr[i][j])
		{
			if (data->map_arr[i][j] == 'N' || data->map_arr[i][j] == 'S' || data->map_arr[i][j] == 'E' || data->map_arr[i][j] == 'W')
			{
				*x = j;
				*y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	load_player(t_data **data)
{
	(*data)->player = malloc(sizeof(t_player));
	if (!(*data)->player)
	{
		perror("Bad malloc on <load_player>");
		free((*data)->game);
		free(*data);
		exit(1);
	}
	(*data)->player->walk_dir = 0;
	(*data)->player->turn_dir = 0;
	(*data)->player->strafe_dir = 0;
	(*data)->player->rot_angle = 3 * M_PI / 2;
	(*data)->player->line = mlx_new_image((*data)->game->window, TILE_SIZE, TILE_SIZE);
	(*data)->player->img = mlx_new_image((*data)->game->window, HITBOX, HITBOX);
	get_player_position(*data, &(*data)->player->x, &(*data)->player->y);
	if (!(*data)->player->img || !(*data)->player->line)
	{
		perror("Failed while loading player image");
		free((*data)->game);
		free(*data);
		exit(1);
	}
}

void	load_images(t_data **data)
{
	(*data)->wall = mlx_new_image((*data)->game->window, TILE_SIZE, TILE_SIZE);
	(*data)->space = mlx_new_image((*data)->game->window, TILE_SIZE, TILE_SIZE);
	(*data)->blank = mlx_new_image((*data)->game->window, TILE_SIZE, TILE_SIZE);
	(*data)->render = mlx_new_image((*data)->game->window, WIDTH, HEIGHT);
	if (!(*data)->wall || !(*data)->space || !(*data)->blank || !(*data)->render)
	{
		perror("Failed while loading images");
		free((*data)->game);
		free(*data);
		exit(1);
	}
}
