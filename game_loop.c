/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: starscourge <starscourge@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:23:36 by adbouras          #+#    #+#             */
/*   Updated: 2025/01/24 11:25:58 by starscourge      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

void	game_loop(void *param)
{
	t_data	*data;

	data = (t_data*) param;
	mlx_set_mouse_pos(data->game, WIDTH / 2, HEIGHT / 2);
	player_hook(data);
	raycasting(data);

	mlx_delete_image(data->game, data->frame);
	data->frame = mlx_new_image(data->game, WIDTH, HEIGHT);
	if (!data->frame)
		ft_exit(data, 2, true);
	draw_bg(data);
	draw_walls(data);
	if (data->mini_map)
	{
		draw_minimap(data);
		draw_rays(data);
	}
	if (mlx_image_to_window(data->game, data->frame, 0, 0) == -1)
		ft_exit(data, 2, true);
	mlx_image_to_window(data->game, data->m, 0, 0);
	mouse_hook(data);
}
