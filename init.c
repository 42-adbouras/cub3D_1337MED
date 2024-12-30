/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:27:00 by adbouras          #+#    #+#             */
/*   Updated: 2024/12/30 19:10:13 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

t_data	*init_data(void)
{
	t_data*			data;

	data = NULL;
	load_data(&data);
	load_game(&data);
	load_player(&data);
	load_images(&data);
	data->map = NULL;
	return (data);
}

void	load_data(t_data **data)
{
	*data = malloc(sizeof(t_data));
	if (!*data)
	{
		perror("Bad malloc on <load_data>");
		exit(1);
	}
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
	(*data)->player->line = mlx_new_image((*data)->game->window, TILE_SIZE, TILE_SIZE);
	(*data)->player->walk_dir = 0;
	(*data)->player->turn_dir = 0;
	(*data)->player->strafe_dir = 0;
	(*data)->player->rot_angle = 3 * M_PI / 2;
	(*data)->player->img = mlx_new_image((*data)->game->window, HITBOX, HITBOX);
	if (!(*data)->player->img)
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
	if (!(*data)->wall || !(*data)->space || !(*data)->blank)
	{
		perror("Failed while loading images");
		free((*data)->game);
		free(*data);
		exit(1);
	}
}
