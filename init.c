/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:46:09 by adbouras          #+#    #+#             */
/*   Updated: 2025/03/10 12:22:26 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	init_data(t_data *data, char *arg)
{
	import_map(data, arg);
	parse_map(data);
	load_game(data);
	load_player(data);
	load_images(data);
	load_ray(data);
	load_textures(data);
	get_map_size(data);
}

void	load_game(t_data *data)
{
	data->game = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	data->rot_speed = ROT_SPEED * (M_PI / 180);
	data->fov = FOV * (M_PI / 180);
	if (!data->game)
	{
		perror("Failed while loading game window");
		ft_exit(data, 0, true);
	}
}

void	init_rot_angle(t_data	*data)
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

void	load_images(t_data *data)
{
	data->frame = mlx_new_image(data->game, WIDTH, HEIGHT);
	data->minimap = mlx_new_image(data->game, WIDTH, HEIGHT);
	if (!data->frame || !data->minimap)
	{
		perror("Failed while loading images");
		ft_exit(data, 1, true);
	}
}

void	load_ray(t_data *data)
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
