/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:14:40 by adbouras          #+#    #+#             */
/*   Updated: 2025/03/13 11:03:29 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	close_game(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	ft_exit(data, 0, GAME_EXIT, false);
}

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

void	ft_exit(t_data *data, int code, const char *s, bool term)
{
	if (s)
		ft_putstr_fd((char *)s, STDERR);
	if (code > 6)
		exit(code);
	if (data->game)
		mlx_close_window(data->game);
	free_strings(data);
	clean_assets(data);
	clean_data(data);
	if (term)
		exit(code);
}

void	free_char_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}
