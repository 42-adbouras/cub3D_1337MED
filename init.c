/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:46:09 by adbouras          #+#    #+#             */
/*   Updated: 2025/01/23 12:04:19 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

#include "includes/cub3D.h"

void	init_data(t_data *data, char *arg)
{
	import_map(&data, arg);
	load_game(&data);
	load_player(&data);
	load_images(&data);
	load_ray(&data);
}


void	load_game(t_data **data)
{
	(*data)->game = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	(*data)->mini_map = false;
	if (!(*data)->game)
	{
		perror("Failed while loading game window");
		ft_exit(*data, 0, true);
	}
}

void	get_player_position(t_data *data, int *x, int *y)
{
	int		i;
	int		j;

	i = 0;
	while (data->map_arr[i])
	{
		j = 0;
		while (data->map_arr[i][j])
		{
			if (data->map_arr[i][j] == 'N' || data->map_arr[i][j] == 'S' \
				|| data->map_arr[i][j] == 'E' || data->map_arr[i][j] == 'W')
			{
				*x = j;
				*y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	load_player(t_data **data)
{
	(*data)->player = malloc(sizeof(t_player));
	if (!(*data)->player)
	{
		perror("Bad malloc on <load_player>");
		ft_exit(*data, 0, true);
	}
	(*data)->player->walk_dir = 0;
	(*data)->player->turn_dir = 0;
	(*data)->player->strafe_dir = 0;
	(*data)->player->rot_angle = 3 * (M_PI / 2);
	(*data)->player->rays = mlx_new_image((*data)->game, WIDTH, HEIGHT);
	(*data)->player->imge = mlx_new_image((*data)->game, HITBOX, HITBOX);
	get_player_position(*data, &(*data)->player->x, &(*data)->player->y);
	if (!(*data)->player->imge || !(*data)->player->rays)
	{
		perror("Failed while loading player image");
		ft_exit(*data, 1, true);
	}
}

void	load_images(t_data **data)
{
	(*data)->frame = mlx_new_image((*data)->game, WIDTH, HEIGHT);
	if (!(*data)->frame)
	{
		perror("Failed while loading images");
		ft_exit(*data, 1, true);
	}
}

void	load_ray(t_data **data)
{
	(*data)->ray = malloc(sizeof(t_ray));
	if (!(*data)->ray)
	{
		perror("Bad malloc on <load_ray>");
		ft_exit(*data, 1, true);
	}
	(*data)->ray->angle = 0;
	(*data)->ray->distance = 0;
	(*data)->ray->face_down = false;
	(*data)->ray->face_left = false;
	(*data)->ray->face_right = false;
	(*data)->ray->face_up = false;
	(*data)->ray->h_cross = false;
	(*data)->ray->v_cross = false;
}
