/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:58:41 by adbouras          #+#    #+#             */
/*   Updated: 2025/01/17 20:06:57 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

bool wall_at(t_data *data, int x, int y) {
    int X_index;
    int Y_index;

    if (x < 0 || x >= data->map_width || y < 0 || y >= data->map_height)
        return (true);
    Y_index = floor(y / TILE_SIZE);
    X_index = floor(x / TILE_SIZE);
    if (Y_index >= data->map_height / TILE_SIZE || X_index >= data->map_width / TILE_SIZE)
        return (true);
    if (X_index >= (int)ft_strlen(data->map_arr[Y_index]))
        return (true);
    if (data->map_arr[Y_index][X_index] == '1')
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
	return (sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1))));
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

	if (data->ray->face_up)
		next_y--;

	while (next_x >= 0 && next_x <= WIDTH && next_y >= 0 && next_y <= HEIGHT)
	{
		if (wall_at(data, next_x, next_y))
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

	if (data->ray->face_left)
		next_x--;

	while (next_x >= 0 && next_x <= WIDTH && next_y >= 0 && next_y <= HEIGHT)
	{
		if (wall_at(data, next_x, next_y))
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

void draw_rect(t_data *data, double ray, double t_pix, double b_pix)
{
	while (t_pix < b_pix)
		mlx_put_pixel(data->render, ray, t_pix++, WHITE);
}

void	render_strip(t_data *data, int ray)
{
	double	wall_height;
	double	projec_plane;
	double	t_pix;
	double	b_pix;

	projec_plane = (WIDTH / 2) / tan(data->player->fov / 2);
	wall_height = (TILE_SIZE / data->ray->distance) * projec_plane;
	b_pix = (HEIGHT / 2) + (wall_height / 2);
	t_pix = (HEIGHT / 2) - (wall_height / 2);
	if (b_pix > HEIGHT)
		b_pix = HEIGHT;
	if (t_pix < 0)
		t_pix = 0;
	draw_rect(data, ray, t_pix, b_pix);
}

void	raycasting(t_data *data)
{
	double	*hori_coord;
	// double	*vert_coord;
	double	hori_dist;
	// double	vert_dist;
	int		ray;

	ray = 0;
	hori_dist = DBL_MAX;
	// vert_dist = DBL_MAX;
	data->ray->angle = data->player->rot_angle - (data->player->fov / 2);
	mlx_delete_image(data->game->window, data->player->line);
	data->player->line = mlx_new_image(data->game->window, WIDTH, HEIGHT);
	while (ray < 1)
	{
		data->ray->angle = norm_angle(data->ray->angle);
		set_orientation(data, data->ray->angle);
		
		hori_coord = hori_intersection(data, data->ray->angle);
		// vert_coord = vert_intersection(data, data->ray->angle);

		// if (data->ray->h_cross)
			hori_dist = get_distance(data->player->x, data->player->y, hori_coord[0], hori_coord[1]);
		// if (data->ray->v_cross)
		// 	vert_dist = get_distance(data->player->x, data->player->y, vert_coord[0], vert_coord[1]);
		// if (hori_dist < vert_dist)
			// data->ray->distance = hori_dist;
		// else
		// 	data->ray->distance = vert_dist;
		update_line(data->player->line, data, data->ray->angle, hori_dist);
		data->ray->angle += data->player->fov / RAYS;
		ray++;
	}
	mlx_image_to_window(data->game->window, data->player->line, 0, 0);
	
}
