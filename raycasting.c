/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 19:45:41 by adbouras          #+#    #+#             */
/*   Updated: 2025/01/12 13:00:56 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int		if_intersection(double angle, double *inter, double *step, char orient)
{
	if (orient == 'h')
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

bool	foo(double angle, char position)
{
	if (position == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (true);
	}
	else if (position == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (true);
	}
	return (false);
}

bool	collider(t_data *data, double h_x, double h_y)
{
	int	x_map;
	int y_map;

	if (h_x < 0 || h_y < 0)
		return (false);
	x_map = (int)floor(h_x / TILE_SIZE);
	y_map = (int)floor(h_y / TILE_SIZE);
	if (data->map_arr[y_map] && x_map <= (int)ft_strlen(data->map_arr[y_map]))
		if (data->map_arr[y_map][x_map] == '1')
			return (false);
	return (true);
}

double	hori_collision(t_data *data, double angle)
{
	double	h_x;
	double	h_y;
	double	x_step;
	double	y_step;
	int		pixels;

	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(angle);
	h_y = floor(data->player->img->instances->y / TILE_SIZE) * TILE_SIZE;
	pixels = if_intersection(angle, &h_y, &y_step, 'h');
	h_x = data->player->img->instances->x + (h_y - data->player->img->instances->y) / tan(angle);
	if ((foo(angle, 'y') && x_step > 0) || (!foo(angle, 'y') && x_step < 0))
		x_step *= (-1);

	// printf("Hori Collision: h_x: %f, h_y: %f, x_step: %f, y_step: %f\n", h_x, h_y, x_step, y_step);

	while (collider(data, h_x, h_y - pixels))
	{
		h_x += x_step;
		h_y += y_step;
	}
	return (sqrt(pow(h_x - data->player->img->instances->x, 2) + pow(h_y - data->player->img->instances->y, 2)));
}

double	vert_collition(t_data *data, double angle)
{
	double	v_x;
	double	v_y;
	double	x_step;
	double	y_step;
	int		pixel;

	x_step = TILE_SIZE;
	y_step = TILE_SIZE * tan(angle);
	v_x = floor(data->player->img->instances->x / TILE_SIZE) * TILE_SIZE;
	pixel = if_intersection(angle, &v_x, &x_step, 0);
	v_y = data->player->img->instances->x + (v_x - data->player->img->instances->x) * tan(angle);
	if ((foo(angle, 'x') && y_step < 0) || (!foo(angle, 'x') && y_step > 0))
		y_step *= -1;
	while (collider(data, v_x, v_y - pixel))
	{
		v_x += x_step;
		v_y += y_step;
	}
	return (sqrt(pow(data->player->img->instances->x / TILE_SIZE, 2) + pow(v_y - data->player->img->instances->x / TILE_SIZE, 2)));
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	if (x < 0)
		return ;
	else if (x >= WIDTH)
		return ;
	if (y < 0)
		return ;
	else if (y >= HEIGHT)
		return ;
	mlx_put_pixel(data->render, x, y, color);
}

double norm_angle(double angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

void	render_strip(t_data *data, int ray)
{
	double	wall_h;
	double	b_pix;
	double	t_pix;

	if (!data || !data->ray || !data->player)
    {
        fprintf(stderr, "Error: Null pointer in render_strip function\n");
        return;
    }

	
	data->ray->distance *= cos(norm_angle(data->ray->angle - data->player->rot_angle));
	wall_h = (TILE_SIZE / data->ray->distance) * ((WIDTH / 2) / tan(FOV / 2));
	b_pix = (HEIGHT / 2) + (wall_h / 2);
	t_pix = (HEIGHT / 2) - (wall_h / 2);
	if (b_pix > HEIGHT)
		b_pix = HEIGHT;
	if (t_pix < 0)
		t_pix = 0;
	while (t_pix < b_pix)
		my_mlx_pixel_put(data, ray, t_pix++, WHITE);
}


void	raycasting(t_data *data)
{
	double	h_intercept;
	double	v_intercept;
	int		ray;

	ray = 0;
	data->ray->angle = data->player->rot_angle - (FOV / 2);
	mlx_delete_image(data->game->window, data->render);
	data->render = mlx_new_image(data->game->window, WIDTH, HEIGHT);
	while (ray < WIDTH)
	{
		data->ray->x = 0;
		h_intercept = hori_collision(data, norm_angle(data->ray->angle));
		v_intercept = vert_collition(data, norm_angle(data->ray->angle));
	
		if (v_intercept <= h_intercept)
			data->ray->distance = v_intercept;
		else
		{
			data->ray->distance = h_intercept;
			data->ray->x = 1;
		}
		render_strip(data, ray);
		ray++;
		data->ray->angle += FOV / WIDTH;
	}
	mlx_image_to_window(data->game->window, data->render, 0, 0);	
}

void	draw_frame(void *param)
{
	t_data	*data;

	data = (t_data*)param;
	mlx_delete_image(data->game->window, data->render);
	data->render = mlx_new_image(data->game->window, WIDTH, HEIGHT);
	raycasting(data);
	mlx_image_to_window(data->game->window, data->render, 0, 0);	
}
