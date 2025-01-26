/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:23:36 by adbouras          #+#    #+#             */
/*   Updated: 2025/01/26 18:18:35 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	game_loop(void *param)
{
	t_data	*data;

	data = (t_data*) param;
	mlx_set_mouse_pos(data->game, WIDTH / 2, HEIGHT / 2);

	player_hook(data);
	raycasting(data);

	draw_bg(data);
	draw_walls(data);

	draw_minimap(data);



	mouse_hook(data);
}
