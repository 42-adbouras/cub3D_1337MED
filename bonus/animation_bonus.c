/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:49:12 by adbouras          #+#    #+#             */
/*   Updated: 2025/03/24 13:15:20 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	animation_bonus(t_data *data)
{
	int static	current;
	int static	frame;
	int			speed;

	speed = 6;
	frame++;
	if (frame % speed == 0)
	{
		data->sprites.s_images[current]->enabled = false;
		current = (current + 1) % NUM_SPRITES;
		data->sprites.s_images[current]->enabled = true;
	}
	if (frame == (speed * NUM_SPRITES - 1))
	{
		data->sprites.s_images[current]->enabled = false;
		data->sprites.s_images[0]->enabled = true;
		data->animation = false;
		current = 0;
		frame = 0;
	}
}
