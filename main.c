/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:43:43 by adbouras          #+#    #+#             */
/*   Updated: 2025/03/10 12:26:00 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	_leaks(void)
{
	system("leaks cub3D");
}

int	main(int ac, char **av)
{
	t_data	data;

	(void) ac;
	init_data(&data, av[1]);
	player_spawn(&data);
	mlx_loop_hook(data.game, game_loop, &data);
	mlx_close_hook(data.game, close_game, &data);
	mlx_loop(data.game);
	mlx_terminate(data.game);
}
