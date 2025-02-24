/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:14:40 by adbouras          #+#    #+#             */
/*   Updated: 2025/02/24 10:43:08 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	close_game_bonus(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	ft_exit_bonus(data, 2, true);
}

void	ft_exit_bonus(t_data *data, int i, bool term)
{
	(void)i;

	mlx_close_window(data->game);
	if (i > 0)
	{
		free(data->player);
		free_char_arr_bonus(data->map_arr);
		free((char *)data->map);
	}
	if (term)
		exit(i);
}

void	free_char_arr_bonus(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}
