/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:43:43 by adbouras          #+#    #+#             */
/*   Updated: 2025/03/11 15:08:55 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	_leaks(void)
{
	system("leaks cub3D");
}

int	main(int ac, char **av)
{
	t_data	data;

	(void) ac;
	init_data_bonus(&data, av[1]);
	load_sprites_bonus(&data);
	player_spawn_bonus(&data);
	mlx_loop_hook(data.game, game_loop_bonus, &data);
	mlx_close_hook(data.game, close_game_bonus, &data);
	mlx_loop(data.game);
	mlx_terminate(data.game);
}
