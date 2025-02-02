/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:58:41 by adbouras          #+#    #+#             */
/*   Updated: 2025/02/02 16:16:29 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

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
    if (map_x >= (int)ft_strlen(data->parsed_map[map_y]))
        return (true);
    if (data->parsed_map[map_y][map_x] == '1')
        return (true);
    return (false);
}

void	set_orientation(t_data *data, double angle, int ray)
{
	data->text[ray].face_down = (angle > 0 && angle < M_PI);
	data->text[ray].face_up = !data->text[ray].face_down;
	data->text[ray].face_right = (angle < 0.5 * M_PI || angle > 1.5 * M_PI);
	data->text[ray].face_left = !data->text[ray].face_right;
}

double	get_distance(double start_x, double start_y, double end_x, double end_y)
{
	// start_x += (HITBOX / 2);
	// start_y += (HITBOX / 2);
	return (sqrt(pow(end_x - start_x, 2) + pow(end_y - start_y, 2)));
}

double	hori_intersection(t_data *data, double angle, int ray)
{
	t_ray_utils	h;

	h.player_x = (data->player->x + (HITBOX / 2));
	h.player_y = (data->player->y + (HITBOX / 2));
	h.y_inter = floor((h.player_y) / TILE_SIZE) * TILE_SIZE;
	if (data->text[ray].face_down)
		h.y_inter += TILE_SIZE;
	h.x_inter = (h.player_x) + (h.y_inter - (h.player_y)) / tan(angle);
	h.y_step = TILE_SIZE;
	if (data->text[ray].face_up)
		h.y_step *= -1;
	h.x_step = TILE_SIZE / tan(angle);
	if (data->text[ray].face_left && h.x_step > 0)
		h.x_step *= -1;
	if (data->text[ray].face_right && h.x_step < 0)
		h.x_step *= -1;
	h.next_x = h.x_inter;
	h.next_y = h.y_inter;
	while (h.next_x >= 0 && h.next_x <= data->map_width * TILE_SIZE \
		&& h.next_y >= 0 && h.next_y <= data->map_height * TILE_SIZE)
	{
		if (wall_at(data, h.next_x, h.next_y - (data->text[ray].face_up ? 1 : 0)))
		{
			data->text[ray].h_cross = true;
			break;
		}
		h.next_x += h.x_step;
		h.next_y += h.y_step;
	}
	data->text[ray].wall_hit_x = h.next_x;
	data->text[ray].wall_hit_y = h.next_y;
	return (get_distance(h.player_x, h.player_y, h.next_x, h.next_y));
}

double	vert_intersection(t_data *data, double angle, int ray)
{
	t_ray_utils	v;

	v.player_x = (data->player->x + (HITBOX / 2));
	v.player_y = (data->player->y + (HITBOX / 2));
	v.x_inter = floor((v.player_x) / TILE_SIZE) * TILE_SIZE;
	if (data->text[ray].face_right)
		v.x_inter += TILE_SIZE;
	v.y_inter = (v.player_y) + (v.x_inter - (v.player_x)) * tan(angle);
	v.x_step = TILE_SIZE;
	if (data->text[ray].face_left)
		v.x_step *= -1;
	v.y_step = TILE_SIZE * tan(angle);
	if (data->text[ray].face_up && v.y_step > 0)
		v.y_step *= -1;
	if (data->text[ray].face_down && v.y_step < 0)
		v.y_step *= -1;
	v.next_x = v.x_inter;
	v.next_y = v.y_inter;
	while (v.next_x >= 0 && v.next_x <= data->map_width * TILE_SIZE \
		&& v.next_y >= 0 && v.next_y <= data->map_height * TILE_SIZE)
	{
		if (wall_at(data, v.next_x - (data->text[ray].face_left ? 1 : 0), v.next_y))
		{
			data->text[ray].v_cross = true;
			break;
		}
		v.next_x += v.x_step;
		v.next_y += v.y_step;
	}
	if (data->text[ray].wall_hit_x < v.next_x)
		data->text[ray].wall_hit_x = v.next_x;
	if (data->text[ray].wall_hit_y < v.next_y)
		data->text[ray].wall_hit_y = v.next_y;
	return (get_distance(v.player_x, v.player_y, v.next_x, v.next_y));
}

void	raycasting(t_data *data)
{
    double  hori_dist;
    double  vert_dist;
	double	ray_angle;
    int     ray;

    ray = -1;
    ray_angle = norm_angle(data->player->rot_angle - (data->fov / 2));
    while (++ray < RAYS)
    {
        data->text[ray].angle = ray_angle;
        set_orientation(data, ray_angle, ray);
        hori_dist = hori_intersection(data, ray_angle, ray);
        vert_dist = vert_intersection(data, ray_angle, ray);    
        if (hori_dist < vert_dist)
        {
            data->text[ray].is_hori = true;
            data->text[ray].distance = hori_dist;
        }
        else
        {
            data->text[ray].is_hori = false;
            data->text[ray].distance = vert_dist;
        }
        ray_angle = norm_angle(ray_angle + (data->fov / RAYS));
    }
}
