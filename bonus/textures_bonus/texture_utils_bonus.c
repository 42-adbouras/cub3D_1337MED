/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 00:27:27 by starscourge       #+#    #+#             */
/*   Updated: 2025/02/23 19:17:37 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	which_texture_bonus(t_data	*data, int ray)
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

void	load_textures_bonus(t_data *data)
{
	data->texture = malloc(sizeof(t_texture));
	data->texture->north_img = mlx_load_png(data->north_texture);
	data->texture->south_img = mlx_load_png(data->south_texture);
	data->texture->west_img = mlx_load_png(data->west_texture);
	data->texture->east_img = mlx_load_png(data->east_texture);
}
