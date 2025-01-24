/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:14:40 by adbouras          #+#    #+#             */
/*   Updated: 2025/01/24 13:41:19 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

void	close_game(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	ft_exit(data, 2, true);
}

void	ft_exit(t_data *data, int i, bool term)
{
	(void)i;

	mlx_close_window(data->game);
	if (i > 0)
	{
		free(data->player);
		free_char_arr(data->map_arr);
		free((char *)data->map);
	}
	if (i > 1)
		free(data->ray);
	if (term)
		exit(i);
}

void	free_char_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}
