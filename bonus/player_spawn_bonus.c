/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_spawn_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:36:03 by adbouras          #+#    #+#             */
/*   Updated: 2025/03/16 12:57:36 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	load_player_bonus(t_data *data)
{
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		ft_exit_bonus(data, 2, ERR_MALLOC, true);
	data->player->walk_dir = 0;
	data->player->turn_dir = 0;
	data->player->strafe_dir = 0;
	data->player->imge = mlx_new_image(data->game, HITBOX, HITBOX);
	get_player_position_bonus(data, &data->player->x, &data->player->y);
	if (!data->player->imge)
		ft_exit_bonus(data, 5, ERR_IMG, true);
	init_rot_angle_bonus(data);
}

void	player_spawn_bonus(t_data *data)
{
	int	i;

	mlx_image_to_window(data->game, data->player->imge,
		data->player->x * TILE_SIZE + (TILE_SIZE / 2 - HITBOX),
		data->player->y * TILE_SIZE + (TILE_SIZE / 2 - HITBOX));
	mlx_set_cursor_mode(data->game, MLX_MOUSE_HIDDEN);
	mlx_image_to_window(data->game, data->frame, 0, 0);
	mlx_image_to_window(data->game, data->minimap, 20, \
		HEIGHT - MINI_HEIGHT - 20);
	i = -1;
	while (++i < NUM_SPRITES)
	{
		mlx_resize_image(data->sprites.s_images[i], WIDTH * 0.6, HEIGHT * 0.6);
		mlx_image_to_window(data->game, data->sprites.s_images[i], \
		(WIDTH / 2) - data->sprites.s_images[i]->height, \
		HEIGHT - data->sprites.s_images[i]->height);
		data->sprites.s_images[i]->enabled = false;
	}
	data->sprites.s_images[0]->enabled = true;
}

void	get_player_position_bonus(t_data *data, int *x, int *y)
{
	int		i;
	int		j;

	i = 0;
	if (!data->parsed_map || !(*data->parsed_map))
		ft_exit_bonus(data, 15, ERR_MAP, true);
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
				data->parsed_map[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}
