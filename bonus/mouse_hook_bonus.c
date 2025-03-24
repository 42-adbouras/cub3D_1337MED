/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:56:04 by adbouras          #+#    #+#             */
/*   Updated: 2025/03/24 13:15:20 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	mouse_hook_bonus(t_data *data)
{
	static int32_t	prev_x;
	int32_t			new_x;
	int32_t			new_y;
	double			delta;

	mlx_get_mouse_pos(data->game, &new_x, &new_y);
	delta = (new_x - prev_x) / MOUSE_SENS;
	if (prev_x != 0)
	{
		data->player->rot_angle += delta;
		data->player->rot_angle = norm_angle_bonus(data->player->rot_angle);
	}
	prev_x = WIDTH / 2;
}
