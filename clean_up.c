/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:14:40 by adbouras          #+#    #+#             */
/*   Updated: 2025/01/22 18:28:39 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	close_game(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	ft_exit(data, 0);
}

void	ft_exit(t_data *data, int i)
{
	(void)i;

	if (data->game)
		mlx_close_window(data->game);
	free(data->ray);
	free(data->player);
	free_char_arr(data->map_arr);
	free((char *)data->map);

}

void	free_char_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}
