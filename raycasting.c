/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:58:41 by adbouras          #+#    #+#             */
/*   Updated: 2025/02/02 17:16:40 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

t_ray_utils	step_incremant(t_data *data, t_ray_utils u, int ray, bool orient)
{
	data->orient = orient;
	while (u.next_x >= 0 && u.next_x <= data->map_width * TILE_SIZE \
		&& u.next_y >= 0 && u.next_y <= data->map_height * TILE_SIZE)
	{
		if (wall_at(data, u.next_x, u.next_y, ray))
		{
			if (!orient)
				data->text[ray].v_cross = true;
			else
				data->text[ray].h_cross = true;
			break ;
		}
		u.next_x += u.x_step;
		u.next_y += u.y_step;
	}
	return (u); 
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
	h = step_incremant(data, h, ray, true);
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
	v = step_incremant(data, v, ray, false);
	if (data->text[ray].wall_hit_x < v.next_x)
		data->text[ray].wall_hit_x = v.next_x;
	if (data->text[ray].wall_hit_y < v.next_y)
		data->text[ray].wall_hit_y = v.next_y;
	return (get_distance(v.player_x, v.player_y, v.next_x, v.next_y));
}

void	raycasting(t_data *data)
{
	double	hori_dist;
	double	vert_dist;
	double	ray_angle;
	int		ray;

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
