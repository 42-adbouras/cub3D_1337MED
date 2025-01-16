/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:43:43 by adbouras          #+#    #+#             */
/*   Updated: 2025/01/16 20:18:33 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	var_check(t_data *data)
{
	int i = 0;

	printf(" ----------- MAP -----------\n%s\n\n", data->map);
	while (data->map_arr[i]) {
		printf("%s\n", data->map_arr[i++]);
	}
	printf("map height: %d.\n", data->map_height);
	data->game ? printf("\nData.game is good\n") : printf("\nData.game is NOT good\n");
	data->wall ? printf("\nData.wall is good\n") : printf("\nData.wall is NOT good\n");
	data->space ? printf("\nData.space is good\n") : printf("\nData.space is NOT good\n");
	data->blank ? printf("\nData.blank is good\n") : printf("\nData.blank is NOT good\n");
	data->render ? printf("\nData.render is good\n") : printf("\nData.render is NOT good\n");
	data->player ? printf("\nData.player is good\n") : printf("\nData.player is NOT good\n");
	data->ray ? printf("\nData.ray is good\n") : printf("\nData.ray is NOT good\n");
	printf("\tray angle: %f\n", data->ray->angle);
	printf("\tray distance: %f\n", data->ray->distance);
	printf("\tray distance: %d\n", data->ray->face_down);
		
}

int	main(int ac, char **av)
{
	t_data	data;

	(void) ac;
	init_data(&data, av[1]);
	var_check(&data);
}
