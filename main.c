/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:43:43 by adbouras          #+#    #+#             */
/*   Updated: 2025/03/13 21:01:43 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	_leaks(void)
{
	system("leaks -q cub3D");
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 2)
		return (ft_putstr_fd(USAGE, STDERR), false);
	atexit(_leaks);
	init_data(&data, av[1]);
	player_spawn(&data);
	mlx_loop_hook(data.game, game_loop, &data);
	mlx_close_hook(data.game, close_game, &data);
	mlx_loop(data.game);
	// mlx_terminate(data.game);
	return (0);
}
