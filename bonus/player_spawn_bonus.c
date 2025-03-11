/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_spawn_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:36:03 by adbouras          #+#    #+#             */
/*   Updated: 2025/03/10 16:46:57 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

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
	data->tx = mlx_load_png("assets/sprites/1.png");
	if (!data->tx)
		ft_exit_bonus(data, 2, true);
	data->im = mlx_texture_to_image(data->game, data->tx);
	mlx_resize_image(data->im, WIDTH * 0.6, HEIGHT * 0.6);
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
