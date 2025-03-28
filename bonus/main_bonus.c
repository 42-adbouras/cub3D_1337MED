/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:43:43 by adbouras          #+#    #+#             */
/*   Updated: 2025/03/24 14:43:41 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 2)
		return (ft_putstr_fd(USAGE_BONUS, STDERR), 1);
	init_data_bonus(&data, av[1]);
	load_sprites_bonus(&data);
	player_spawn_bonus(&data);
	mlx_loop_hook(data.game, game_loop_bonus, &data);
	mlx_loop_hook(data.game, minimap_bonus, &data);
	mlx_close_hook(data.game, close_game_bonus, &data);
	mlx_loop(data.game);
	mlx_terminate(data.game);
}
