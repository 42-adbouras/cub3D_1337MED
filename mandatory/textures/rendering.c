/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:29:18 by adbouras          #+#    #+#             */
/*   Updated: 2025/03/16 15:36:11 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_walls(t_data *data)
{
	int	ray;

	ray = -1;
	while (++ray < RAYS)
		render_strip(data, ray, data->text[ray].distance);
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
				mlx_put_pixel(data->frame, width, height,
					rgba(data->ceiling_color[0],
						data->ceiling_color[1], data->ceiling_color[2], 155));
			else
				mlx_put_pixel(data->frame, width, height,
					rgba(data->floor_color[0], data->floor_color[1],
						data->floor_color[2], 255));
			width++;
		}
		height++;
	}
}

double	get_texture_x(t_data *data, int ray)
{
	double	texture_x;

	if (data->text[ray].is_hori)
		texture_x = fmod(data->text[ray].wall_hit_x, (double)TILE_SIZE);
	else
		texture_x = fmod(data->text[ray].wall_hit_y, (double)TILE_SIZE);
	texture_x = texture_x / (double)TILE_SIZE;
	if (data->text[ray].wall_facing == WEST
		|| data->text[ray].wall_facing == SOUTH)
		texture_x = 1 - texture_x;
	return (texture_x);
}

void	render_strip(t_data *data, int ray, double distance)
{
	double	wall_height;
	double	proj_plane;
	double	top;
	double	bottom;

	which_texture(data, ray);
	distance *= cos(data->text[ray].angle - data->player->rot_angle);
	proj_plane = (WIDTH / 2) / tan(data->fov / 2);
	wall_height = (TILE_SIZE / distance) * proj_plane;
	top = (HEIGHT / 2) - (wall_height / 2);
	bottom = (HEIGHT / 2) + (wall_height / 2);
	if (bottom > HEIGHT)
		bottom = HEIGHT;
	draw_rect(data, ray, top, wall_height);
}

void	draw_rect(t_data *data, double x, double y, double height)
{
	int				pixel_index;
	int				color;
	int				rgba_col[4];
	int				j;
	int				tex_xy[2];

	j = 0;
	tex_xy[0] = (int)(get_texture_x(data,
				(int)x) * data->text[(int)x].img->width);
	while (j < height)
	{
		tex_xy[1] = (int)((j / height) * data->text[(int)x].img->height);
		pixel_index = (tex_xy[1]
				* data->text[(int)x].img->width + tex_xy[0]) * 4;
		rgba_col[0] = data->text[(int)x].img->pixels[pixel_index + 0];
		rgba_col[1] = data->text[(int)x].img->pixels[pixel_index + 1];
		rgba_col[2] = data->text[(int)x].img->pixels[pixel_index + 2];
		rgba_col[3] = data->text[(int)x].img->pixels[pixel_index + 3];
		color = rgba(rgba_col[0], rgba_col[1], rgba_col[2], rgba_col[3]);
		if (x >= 0 && x < WIDTH && y + j >= 0 && y + j < HEIGHT)
			mlx_put_pixel(data->frame, x, y + j, color);
		j++;
	}
}
