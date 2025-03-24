/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 10:49:14 by adbouras          #+#    #+#             */
/*   Updated: 2025/03/24 13:15:20 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	clean_assets_bonus(t_data *data)
{
	int	i;

	if (data->texture->east_img)
		mlx_delete_texture(data->texture->east_img);
	if (data->texture->west_img)
		mlx_delete_texture(data->texture->west_img);
	if (data->texture->north_img)
		mlx_delete_texture(data->texture->north_img);
	if (data->texture->south_img)
		mlx_delete_texture(data->texture->south_img);
	if (data->texture->door_img)
		mlx_delete_texture(data->texture->door_img);
	if (data->player->imge)
		mlx_delete_image(data->game, data->player->imge);
	if (data->frame)
		mlx_delete_image(data->game, data->frame);
	if (data->minimap)
		mlx_delete_image(data->game, data->minimap);
	i = -1;
	while (++i < NUM_SPRITES)
	{
		mlx_delete_image(data->game, data->sprites.s_images[i]);
		mlx_delete_texture(data->sprites.s_texture[i]);
	}
}

void	free_strings_bonus(t_data *data)
{
	if (data->north_texture)
		free(data->north_texture);
	if (data->south_texture)
		free(data->south_texture);
	if (data->west_texture)
		free(data->west_texture);
	if (data->east_texture)
		free(data->east_texture);
	if (data->map)
		free((char *)data->map);
	if (data->map_arr)
		free_char_arr_bonus(data->map_arr);
	if (data->parsed_map)
		free_char_arr_bonus(data->parsed_map);
	if (data->sprites.path)
		free_char_arr_bonus(data->sprites.path);
}

void	clean_data_bonus(t_data *data)
{
	if (data->player)
		free(data->player);
	if (data->texture)
		free(data->texture);
}

void	free_char_arr_bonus(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}
