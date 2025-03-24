/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:14:40 by adbouras          #+#    #+#             */
/*   Updated: 2025/03/24 13:15:20 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	close_game_bonus(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	ft_exit_bonus(data, 2, GAME_EXIT, false);
}

void	ft_exit_bonus(t_data *data, int code, const char *s, bool term)
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
	mlx_close_window(data->game);
	free_strings_bonus(data);
	clean_assets_bonus(data);
	clean_data_bonus(data);
	if (term)
	{
		mlx_terminate(data->game);
		exit(code);
	}
}
