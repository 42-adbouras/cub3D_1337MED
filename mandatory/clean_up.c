/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:14:40 by adbouras          #+#    #+#             */
/*   Updated: 2025/03/16 12:50:25 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	close_game(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	ft_exit(data, 0, GAME_EXIT, false);
}

void	ft_exit(t_data *data, int code, const char *s, bool term)
{
	if (s)
	{
		ft_putstr_fd(BRED, STDERR);
		if (!code)
			ft_putstr_fd(BBLU, STDERR);
		ft_putstr_fd((char *)s, STDERR);
		ft_putstr_fd(RSET, STDERR);
	}
	if (code > 6)
		exit(code);
	if (data->game)
		mlx_close_window(data->game);
	free_strings(data);
	clean_assets(data);
	clean_data(data);
	if (term)
	{
		mlx_terminate(data->game);
		exit(code);
	}
}
