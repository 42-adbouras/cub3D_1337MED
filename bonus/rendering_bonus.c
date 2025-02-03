/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:29:18 by adbouras          #+#    #+#             */
/*   Updated: 2025/02/03 15:28:24 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_walls_bonus(t_data *data)
{
	int	ray;

	ray = -1;
	while (++ray < RAYS)
		render_strip_bonus(data, ray, data->text[ray].distance);
}


void	draw_bg_bonus(t_data *data)
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
				mlx_put_pixel(data->frame, width, height, rgba(62, 88, 121, 155));
			else
				mlx_put_pixel(data->frame, width, height, rgba(33, 53, 85, 255));
			width++;
		}
		height++;
	}
}

void	render_strip_bonus(t_data *data, int ray, double distance)
{
	double	wall_height;
	double	proj_plane;
	double	top;
	double	bottom;

	distance *= cos(data->text[ray].angle - data->player->rot_angle);
	proj_plane = (WIDTH / 2) / tan(data->fov / 2);
	wall_height = (TILE_SIZE / distance) * proj_plane;
	top = (HEIGHT / 2) - (wall_height / 2);
	if (top < 0)
		top = 0;
	bottom = (HEIGHT / 2) + (wall_height / 2);
	if (bottom > HEIGHT)
		bottom = HEIGHT;
	draw_rect_bonus(data, ray, top, 1, bottom - top);
}

void	draw_rect_bonus(t_data *data, double x, double y, double width, double height)
{
	int	i;
	int	j;

	i = 0;
    while (i < width)
	{
		j = 0;
        while (j < height)
		{
			if (data->text[(int)x].is_hori)
            	mlx_put_pixel(data->frame, x + i, y + j, rgba(216, 196, 182, 255));
			else
            	mlx_put_pixel(data->frame, x + i, y + j, rgba(245, 239, 231, 255));
			j++;
        }
		i++;
    }
}
