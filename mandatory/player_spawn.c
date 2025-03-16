/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_spawn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:31:03 by adbouras          #+#    #+#             */
/*   Updated: 2025/03/16 12:49:02 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_spawn(t_data *data)
{
	int	x;
	int	y;

	x = data->player->x * TILE_SIZE + (TILE_SIZE / 2 - HITBOX);
	y = data->player->y * TILE_SIZE + (TILE_SIZE / 2 - HITBOX);
	if (mlx_image_to_window(data->game, data->player->imge, x, y) == -1)
		ft_exit(data, 6, IMG_2_WIN, true);
	if (mlx_image_to_window(data->game, data->frame, 0, 0) == -1)
		ft_exit(data, 6, IMG_2_WIN, true);
	data->p_txtre = mlx_load_png("assets/sprites/1.png");
	if (!data->p_txtre)
		ft_exit(data, 4, ERR_TEXTURE, true);
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
	if (!data->parsed_map || !(*data->parsed_map))
		ft_exit(data, 15, ERR_MAP, true);
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
		ft_exit(data, 2, ERR_MALLOC, true);
	data->player->walk_dir = 0;
	data->player->turn_dir = 0;
	data->player->strafe_dir = 0;
	data->player->rot_angle = 3 * (M_PI / 2);
	data->player->imge = mlx_new_image(data->game, HITBOX, HITBOX);
	get_player_position(data, &data->player->x, &data->player->y);
	if (!data->player->imge)
		ft_exit(data, 5, ERR_IMG, true);
	init_rot_angle(data);
}
