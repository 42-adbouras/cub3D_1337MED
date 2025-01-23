/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:29:18 by adbouras          #+#    #+#             */
/*   Updated: 2025/01/23 12:04:19 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

void	draw_walls(t_data *data)
{
	int	ray;

	ray = -1;
	while (++ray < RAYS)
		render_strip(data, ray, data->text[ray].distance);
}

void	draw_rays(t_data *data)
{
	int	ray;
	
	ray = -1;
	while (++ray < RAYS)
		draw_line(data->frame,
				(data->player->x + (HITBOX / 2)) * MAP_FACT,
				(data->player->y + (HITBOX / 2)) * MAP_FACT,
				data->text[ray].wall_hit_x * MAP_FACT,
				data->text[ray].wall_hit_y * MAP_FACT,
				rgba(192, 242, 255, 255));
}

void	draw_bg(t_data *data)
{
	int	height;
	int	width;

	height = 0;
	while (height < HEIGHT)
	{
		width = 0;
		while (width < WIDTH)
		{
			if (height < HEIGHT / 2)
				mlx_put_pixel(data->frame, width, height, rgba(175, 246, 255, 255));
			else
				mlx_put_pixel(data->frame, width, height, rgba(20, 36, 40, 255));
			width++;
		}
		height++;
	}
}

void	render_strip(t_data *data, int ray, double distance)
{
	double wall_height;
	double proj_plane;
	double top;
	double bottom;

	distance *= cos(data->text[ray].angle - data->player->rot_angle);
	proj_plane = (WIDTH / 2) / tan(FOV / 2);
	wall_height = (TILE_SIZE / distance) * proj_plane;

	top = (HEIGHT / 2) - (wall_height / 2);
	top = top < 0 ? 0 : top;

	bottom = (HEIGHT / 2) + (wall_height / 2);
	bottom = bottom > HEIGHT ? HEIGHT : bottom;

	draw_rect(data, ray, top, 1, bottom - top);
}

void	draw_rect(t_data *data, double x, double y, double width, double height)
{
	int i, j;

	i = 0;
    while (i < width)
	{
		j = 0;
        while (j < height)
		{
			if (data->text[(int)x].is_hori)
            	mlx_put_pixel(data->frame, x + i, y + j, rgba(255, 255, 255, 255));
			else
            	mlx_put_pixel(data->frame, x + i, y + j, rgba(214, 214, 214, 255));
			j++;
        }
		i++;
    }
}
