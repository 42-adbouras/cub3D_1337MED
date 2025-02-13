/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: starscourge <starscourge@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:29:18 by adbouras          #+#    #+#             */
/*   Updated: 2025/02/13 13:32:38 by starscourge      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	which_texture(t_data	*data, int ray)
{
	if (data->text[ray].wall_facing == NORTH)
		data->text[ray].img = data->texture->north_img;
	else if (data->text[ray].wall_facing == SOUTH)
		data->text[ray].img = data->texture->south_img;
	else if (data->text[ray].wall_facing == WEST)
		data->text[ray].img = data->texture->west_img;
	else if (data->text[ray].wall_facing == EAST)
		data->text[ray].img = data->texture->east_img;
}

void	load_textures(t_data *data)
{
	data->texture = malloc(sizeof(t_texture));
	data->texture->north_img = mlx_load_png(data->north_texture);
	data->texture->south_img = mlx_load_png(data->south_texture);
	data->texture->west_img = mlx_load_png(data->west_texture);
	data->texture->east_img = mlx_load_png(data->east_texture);
}

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
	double	texture_x;

	which_texture(data, ray);
	distance *= cos(data->text[ray].angle - data->player->rot_angle);
	proj_plane = (WIDTH / 2) / tan(data->fov / 2);
	wall_height = (TILE_SIZE / distance) * proj_plane;
	top = (HEIGHT / 2) - (wall_height / 2);
	bottom = (HEIGHT / 2) + (wall_height / 2);
	if (bottom > HEIGHT)
		bottom = HEIGHT;
	texture_x = get_texture_x(data, ray);
	draw_rect(data, ray, top, wall_height, ray, texture_x);
}

void	draw_rect(t_data *data, double x, double y, double height, int ray, double texture_x)
{
	int				pixel_index;
	int				color;
	mlx_texture_t	*texture;
	int				r;
	int				g;
	int				b;
	int				a;
	int				j;
	int				tex_x;
	int				tex_y;

	j = 0;
	texture = data->text[ray].img;
	while (j < height)
	{
		tex_x = (int)(texture_x * texture->width);
		tex_y = (int)((j / height) * texture->height);
		pixel_index = (tex_y * texture->width + tex_x) * 4;
		r = texture->pixels[pixel_index + 0];
		g = texture->pixels[pixel_index + 1];
		b = texture->pixels[pixel_index + 2];
		a = texture->pixels[pixel_index + 3];
		color = rgba(r, g, b, a);
		if (x >= 0 && x < WIDTH && y + j >= 0 && y + j < HEIGHT)
			mlx_put_pixel(data->frame, x, y + j, color);
		j++;
	}
}
