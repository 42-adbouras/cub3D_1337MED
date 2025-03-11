/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_spawn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:31:03 by adbouras          #+#    #+#             */
/*   Updated: 2025/03/10 12:27:19 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	player_spawn(t_data *data)
{
	mlx_image_to_window(data->game, data->player->imge, \
		data->player->x * TILE_SIZE + (TILE_SIZE / 2 - HITBOX), \
		data->player->y * TILE_SIZE + (TILE_SIZE / 2 - HITBOX));
	if (mlx_image_to_window(data->game, data->frame, 0, 0) == -1)
		ft_exit(data, 2, true);
	data->p_txtre = mlx_load_png("assets/sprites/1.png");
	if (!data->p_txtre)
		ft_exit(data, 2, true);
	data->p_asset = mlx_texture_to_image(data->game, data->p_txtre);
	mlx_resize_image(data->p_asset, WIDTH * 0.7, HEIGHT * 0.7);
	mlx_image_to_window(data->game, data->p_asset, \
						(WIDTH / 2) - data->p_asset->height, \
						HEIGHT - data->p_asset->height);
}

void	get_player_position(t_data *data, int *x, int *y)
{
	int		i;
	int		j;

	i = 0;
	while (data->parsed_map[i])
	{
		j = 0;
		while (data->parsed_map[i][j])
		{
			if (data->parsed_map[i][j] == 'N' \
				|| data->parsed_map[i][j] == 'S' \
				|| data->parsed_map[i][j] == 'E' \
				|| data->parsed_map[i][j] == 'W')
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

void	load_player(t_data *data)
{
	data->player = malloc(sizeof(t_player));
	if (!data->player)
	{
		perror("Bad malloc on <load_player>");
		ft_exit(data, 0, true);
	}
	data->player->walk_dir = 0;
	data->player->turn_dir = 0;
	data->player->strafe_dir = 0;
	data->player->rot_angle = 3 * (M_PI / 2);
	data->player->rays = mlx_new_image(data->game, WIDTH, HEIGHT);
	data->player->imge = mlx_new_image(data->game, HITBOX, HITBOX);
	get_player_position(data, &data->player->x, &data->player->y);
	if (!data->player->imge || !data->player->rays)
	{
		perror("Failed while loading player image");
		ft_exit(data, 1, true);
	}
	init_rot_angle(data);
}
