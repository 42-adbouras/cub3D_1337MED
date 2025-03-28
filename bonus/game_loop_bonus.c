/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:23:36 by adbouras          #+#    #+#             */
/*   Updated: 2025/03/24 13:15:20 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	game_loop_bonus(void *param)
{
	t_data	*data;

	data = (t_data *) param;
	mlx_set_mouse_pos(data->game, WIDTH / 2, HEIGHT / 2);
	player_hook_bonus(data);
	raycasting_bonus(data);
	draw_bg_bonus(data);
	draw_walls_bonus(data);
	if (data->animation)
		animation_bonus(data);
	mouse_hook_bonus(data);
}
