/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:31:47 by adbouras          #+#    #+#             */
/*   Updated: 2025/03/10 12:32:44 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	assigne_hori_walls(t_data *data, double ray_angle, int ray)
{
	if (sin(ray_angle) > 0)
		data->text[ray].wall_facing = SOUTH;
	else
		data->text[ray].wall_facing = NORTH;
}

void	assigne_vert_walls(t_data *data, double ray_angle, int ray)
{
	if (cos(ray_angle) > 0)
		data->text[ray].wall_facing = EAST;
	else
		data->text[ray].wall_facing = WEST;
}
