/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 10:43:11 by adbouras          #+#    #+#             */
/*   Updated: 2025/03/24 13:14:03 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	clean_assets(t_data *data)
{
	if (data->texture->east_img)
		mlx_delete_texture(data->texture->east_img);
	if (data->texture->west_img)
		mlx_delete_texture(data->texture->west_img);
	if (data->texture->north_img)
		mlx_delete_texture(data->texture->north_img);
	if (data->texture->south_img)
		mlx_delete_texture(data->texture->south_img);
	if (data->p_txtre)
		mlx_delete_texture(data->p_txtre);
	if (data->player->imge)
		mlx_delete_image(data->game, data->player->imge);
	if (data->p_asset)
		mlx_delete_image(data->game, data->p_asset);
	if (data->frame)
		mlx_delete_image(data->game, data->frame);
}

void	free_strings(t_data *data)
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
		free_char_arr(data->map_arr);
	if (data->parsed_map)
		free_char_arr(data->parsed_map);
}

void	clean_data(t_data *data)
{
	if (data->player)
		free(data->player);
	if (data->texture)
		free(data->texture);
}

void	free_char_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}
