/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:46:09 by adbouras          #+#    #+#             */
/*   Updated: 2025/02/03 15:36:30 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_data_bonus(t_data *data, char *arg)
{
	import_map_bonus(data, arg);
	parse_map(data);
	load_game_bonus(data);
	load_player_bonus(data);
	load_images_bonus(data);
	load_ray_bonus(data);
	get_map_size_bonus(data);
}


void	load_game_bonus(t_data *data)
{
	data->game = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	data->rot_speed = ROT_SPEED * (M_PI / 180);
	data->fov = FOV * (M_PI / 180);
	data->animation = false;
	if (!data->game)
	{
		perror("Failed while loading game window");
		ft_exit_bonus(data, 0, true);
	}
}

void	get_player_position_bonus(t_data *data, int *x, int *y)
{
	int		i;
	int		j;

	i = 0;
	while (data->parsed_map[i])
	{
		j = 0;
		while (data->parsed_map[i][j])
		{
			if (data->parsed_map[i][j] == 'N' || data->parsed_map[i][j] == 'S' \
				|| data->parsed_map[i][j] == 'E' || data->parsed_map[i][j] == 'W')
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

void	load_player_bonus(t_data *data)
{
	data->player = malloc(sizeof(t_player));
	if (!data->player)
	{
		perror("Bad malloc on <load_player>");
		ft_exit_bonus(data, 0, true);
	}
	data->player->walk_dir = 0;
	data->player->turn_dir = 0;
	data->player->strafe_dir = 0;
	data->player->rot_angle = 3 * (M_PI / 2);
	data->player->rays = mlx_new_image(data->game, WIDTH, HEIGHT);
	data->player->imge = mlx_new_image(data->game, HITBOX, HITBOX);
	get_player_position_bonus(data, &data->player->x, &data->player->y);
	if (!data->player->imge || !data->player->rays)
	{
		perror("Failed while loading player image");
		ft_exit_bonus(data, 1, true);
	}
}

void	load_images_bonus(t_data *data)
{
	data->frame = mlx_new_image(data->game, WIDTH, HEIGHT);
	data->minimap = mlx_new_image(data->game, WIDTH, HEIGHT);
	if (!data->frame || !data->minimap)
	{
		perror("Failed while loading images");
		ft_exit_bonus(data, 1, true);
	}
}

void	load_ray_bonus(t_data *data)
{
	int	ray;

	ray = -1;
	while (++ray < RAYS)
	{
		data->text[ray].angle = 0;
		data->text[ray].distance = 0;
		data->text[ray].h_cross = false;
		data->text[ray].v_cross = false;
		data->text[ray].wall_hit_x = 0;
		data->text[ray].wall_hit_y = 0;
		data->text[ray].face_up = false;
		data->text[ray].face_down = false;
		data->text[ray].face_left = false;
		data->text[ray].face_right = false;
		data->text[ray].is_hori = false;
	}
}
