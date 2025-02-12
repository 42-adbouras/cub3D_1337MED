/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:23:36 by adbouras          #+#    #+#             */
/*   Updated: 2025/02/12 13:47:25 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	game_loop(void *param)
{
	t_data	*data;

	data = (t_data*) param;
	player_hook(data);
	raycasting(data);
	draw_bg(data);
	draw_walls(data);
}
