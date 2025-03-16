/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:46:09 by adbouras          #+#    #+#             */
/*   Updated: 2025/03/16 12:57:36 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_data_bonus(t_data *data, char *arg)
{
	import_map_bonus(data, arg);
	parse_map_bonus(data);
	load_game_bonus(data);
	load_player_bonus(data);
	load_images_bonus(data);
	load_ray_bonus(data);
	load_textures_bonus(data);
	get_map_size_bonus(data);
}

void	load_game_bonus(t_data *data)
{
	data->game = mlx_init(WIDTH, HEIGHT, "cub3D_bonus", true);
	data->rot_speed = ROT_SPEED * (M_PI / 180);
	data->fov = FOV * (M_PI / 180);
	data->animation = false;
	if (!data->game)
		ft_exit_bonus(data, 3, GAME_WIN, true);
}

void	load_images_bonus(t_data *data)
{
	data->frame = mlx_new_image(data->game, WIDTH, HEIGHT);
	data->minimap = mlx_new_image(data->game, WIDTH, HEIGHT);
	if (!data->frame || !data->minimap)
		ft_exit_bonus(data, 5, ERR_IMG, true);
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
		data->text[ray].contant = '\0';
	}
}

void	init_rot_angle_bonus(t_data	*data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map_arr[i])
	{
		j = 0;
		while (data->map_arr[i][j])
		{
			if (data->map_arr[i][j] == 'N')
				data->player->rot_angle = 270 * (M_PI / 180);
			if (data->map_arr[i][j] == 'S')
				data->player->rot_angle = 90 * (M_PI / 180);
			if (data->map_arr[i][j] == 'W')
				data->player->rot_angle = 180 * (M_PI / 180);
			if (data->map_arr[i][j] == 'E')
				data->player->rot_angle = 0;
			j++;
		}
		i++;
	}
}
