/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: starscourge <starscourge@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 00:27:27 by starscourge       #+#    #+#             */
/*   Updated: 2025/02/15 00:28:15 by starscourge      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	which_texture(t_data	*data, int ray)
{
	if (data->text[ray].wall_facing == NORTH)
		data->text[ray].img = data->texture->north_img;
	else if (data->text[ray].wall_facing == SOUTH)
		data->text[ray].img = data->texture->south_img;
	else if (data->text[ray].wall_facing == WEST)
		data->text[ray].img = data->texture->west_img;
	else if (data->text[ray].wall_facing == EAST)
		data->text[ray].img = data->texture->east_img;
}
