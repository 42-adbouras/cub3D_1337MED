/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:58:41 by adbouras          #+#    #+#             */
/*   Updated: 2025/01/18 18:57:58 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

bool	wall_at(t_data *data, int x, int y)
{
    int map_x;
    int map_y;

    if (x < 0 || x >= data->map_width * TILE_SIZE || y < 0 || y >= data->map_height * TILE_SIZE)
        return (true);
    map_y = floor(y / TILE_SIZE);
    map_x = floor(x / TILE_SIZE);
    if (map_y >= data->map_height || map_x >= data->map_width)
        return (true);
    if (map_x >= (int)ft_strlen(data->map_arr[map_y]))
        return (true);
    if (data->map_arr[map_y][map_x] == '1')
        return (true);
    return (false);
}

void	set_orientation(t_data *data, double angle)
{
	data->ray->face_down = (angle > 0 && angle < M_PI);
	data->ray->face_up = !data->ray->face_down;
	data->ray->face_right = (angle < 0.5 * M_PI || angle > 1.5 * M_PI);
	data->ray->face_left = !data->ray->face_right;
}

double	get_distance(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

double*	hori_intersection(t_data *data, double angle)
{
	double	x_step;
	double	y_step;
	double	x_inter;
	double 	y_inter;
	double	*hori_coord;

	hori_coord = malloc(sizeof(double) * 2);
	//////////////
	y_inter = floor(data->player->y / TILE_SIZE) * TILE_SIZE;
	y_inter += data->ray->face_down ? TILE_SIZE : 0;
	x_inter = data->player->x + (y_inter - data->player->y) / tan(angle);
	y_step = TILE_SIZE;
	y_step *= data->ray->face_up ? -1 : 1;
	x_step = TILE_SIZE / tan(angle);
	x_step *= data->ray->face_left && x_step > 0 ? -1 : 1;
	x_step *= data->ray->face_right && x_step < 0 ? -1 : 1;
	double	next_x = x_inter;
	double	next_y = y_inter;
	while (next_x >= 0 && next_x <= data->map_width * TILE_SIZE && next_y >= 0 && next_y <= data->map_height * TILE_SIZE)
	{
		if (wall_at(data, next_x, next_y - (data->ray->face_up ? 1 : 0)))
		{
			data->ray->h_cross = true;
			break;
		}
		next_x += x_step;
		next_y += y_step;
	}
	hori_coord[0] = next_x;
	hori_coord[1] = next_y;
	return (hori_coord);
}

double*	vert_intersection(t_data *data, double angle)
{
	double	x_step;
	double	y_step;
	double	x_inter;
	double 	y_inter;
	double	*vert_coord;

	vert_coord = malloc(sizeof(double) * 2);
	//////////////
	x_inter = floor(data->player->x / TILE_SIZE) * TILE_SIZE;
	x_inter += data->ray->face_right ? TILE_SIZE : 0;
	y_inter = data->player->y + (x_inter - data->player->x) * tan(angle);
	x_step = TILE_SIZE;
	x_step *= data->ray->face_left ? -1 : 1;
	y_step = TILE_SIZE * tan(angle);
	y_step *= (data->ray->face_up && y_step > 0) ? -1 : 1;
	y_step *= (data->ray->face_down && y_step < 0) ? -1 : 1;
	double	next_x = x_inter;
	double	next_y = y_inter;
	while (next_x >= 0 && next_x <= data->map_width * TILE_SIZE && next_y >= 0 && next_y <= data->map_height * TILE_SIZE)
	{
		if (wall_at(data, next_x - (data->ray->face_left ? 1 : 0), next_y))
		{
			data->ray->v_cross = true;
			break;
		}
		next_x += x_step;
		next_y += y_step;
	}
	vert_coord[0] = next_x;
	vert_coord[1] = next_y;
	return (vert_coord);
}

void draw_rect(t_data *data, double x, double y, double width, double height)
{
	int i, j;

	i = 0;
    while (i < width)
	{
		j = 0;
        while (j < height)
		{
			if (data->ray->is_hori)
            	mlx_put_pixel(data->frame, x + i, y + j, WHITE);
			else
            	mlx_put_pixel(data->frame, x + i, y + j, 0xB5B5B5FF);
			j++;
        }
		i++;
    }
}

void render_strip(t_data *data, int ray, double distance)
{
	double wall_height;
	double proj_plane;
	double top;
	double bottom;

	distance = distance * cos(data->ray->angle - data->player->rot_angle);
	proj_plane = (WIDTH / 2) / tan(FOV / 2);
	wall_height = (TILE_SIZE / distance) * proj_plane;

	top = (HEIGHT / 2) - (wall_height / 2);
	top = top < 0 ? 0 : top;

	bottom = (HEIGHT / 2) + (wall_height / 2);
	bottom = bottom > HEIGHT ? HEIGHT : bottom;

	draw_rect(data, ray, top, 1, bottom - top);
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
				mlx_put_pixel(data->frame, width, height, 0x89CFF3FF);
			else
				mlx_put_pixel(data->frame, width, height, 0xB99470FF);
			width++;
		}
		height++;
	}
}

void	raycasting(t_data *data)
{
	double	*hori_coord;
	double	*vert_coord;
	double	hori_dist;
	double	vert_dist;
	int		ray;

	ray = 0;
	hori_dist = DBL_MAX;
	vert_dist = DBL_MAX;
	data->ray->angle = data->player->rot_angle - (FOV / 2);
	draw_bg(data);
	while (ray < RAYS)
	{
		data->ray->angle = norm_angle(data->ray->angle);
		set_orientation(data, data->ray->angle);
		
		hori_coord = hori_intersection(data, data->ray->angle);
		vert_coord = vert_intersection(data, data->ray->angle);	
		if (data->ray->h_cross)
			hori_dist = get_distance(data->player->x, data->player->y, hori_coord[0], hori_coord[1]);
		if (data->ray->v_cross)
			vert_dist = get_distance(data->player->x, data->player->y, vert_coord[0], vert_coord[1]);
		if (hori_dist < vert_dist)
		{
			data->ray->distance = hori_dist;
			data->ray->is_hori = true;
			data->ray->wall_hit_x = hori_coord[0];
			data->ray->wall_hit_y = hori_coord[1];
		}
		else
		{
			data->ray->distance = vert_dist;
			data->ray->is_hori = false;
			data->ray->wall_hit_x = vert_coord[0];
			data->ray->wall_hit_y = vert_coord[1];
		}
		draw_line(data->player->rays, data->player->x, data->player->y, data->ray->wall_hit_x, data->ray->wall_hit_y, GREEN);
		render_strip(data, ray, data->ray->distance);
		data->ray->angle += FOV / RAYS;
		ray++;
	}
}
