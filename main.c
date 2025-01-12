/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:29:26 by adbouras          #+#    #+#             */
/*   Updated: 2025/01/12 13:02:18 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"


int	main(int ac, char **av)
{	(void)ac;
	t_data	data;

	init_data(&data, av[1]);
	draw_minimap(&data);
	mlx_loop_hook(data.game->window, &ft_key_hook, &data);
	mlx_loop(data.game->window);
	return (0);
}
