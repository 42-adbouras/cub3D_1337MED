/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:23:36 by adbouras          #+#    #+#             */
/*   Updated: 2025/01/25 10:29:25 by adbouras         ###   ########.fr       */
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
		// draw_rays(data);
	}
	if (mlx_image_to_window(data->game, data->frame, 0, 0) == -1)
		ft_exit(data, 2, true);

	mouse_hook(data);
}
