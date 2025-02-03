/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:23:36 by adbouras          #+#    #+#             */
/*   Updated: 2025/02/03 16:23:22 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	animation_bonus(t_data *data)
{
	int static	current;
	int static	frame;
	int			speed;
	
	speed = 4;
	frame++;
	if (frame % speed == 0)
	{
		data->sprites.s_images[current]->enabled = false;
		current = (current + 1) % NUM_SPRITES;
		data->sprites.s_images[current]->enabled = true;
	}
	if (current == NUM_SPRITES - 1 && frame == (speed * NUM_SPRITES - 1))
	{
		data->sprites.s_images[current]->enabled = false;
		data->sprites.s_images[0]->enabled = true;
		data->animation = false;
		current = 0;
		frame = 0;
	}
}

void	game_loop_bonus(void *param)
{
	t_data	*data;

	data = (t_data*) param;
	mlx_set_mouse_pos(data->game, WIDTH / 2, HEIGHT / 2);
	player_hook_bonus(data);
	raycasting_bonus(data);
	draw_bg_bonus(data);
	draw_walls_bonus(data);
	draw_minimap_bonus(data);
	if (data->animation)
		animation_bonus(data);
	mouse_hook_bonus(data);
}
