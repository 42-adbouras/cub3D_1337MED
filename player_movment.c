/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:26:58 by adbouras          #+#    #+#             */
/*   Updated: 2025/01/17 15:43:08 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	key_press(t_data *data)
{
	data->player->turn_dir = 0;
	data->player->walk_dir = 0;
	data->player->strafe_dir = 0;
	if (mlx_is_key_down(data->game->window, MLX_KEY_ESCAPE))
		exit(0);
	if (mlx_is_key_down(data->game->window, MLX_KEY_RIGHT))
		data->player->turn_dir = 1;
	if (mlx_is_key_down(data->game->window, MLX_KEY_LEFT))
		data->player->turn_dir = -1;
	if (mlx_is_key_down(data->game->window, MLX_KEY_W))
		data->player->walk_dir = 1;
	if (mlx_is_key_down(data->game->window, MLX_KEY_S))
		data->player->walk_dir = -1;
	if (mlx_is_key_down(data->game->window, MLX_KEY_D))
		data->player->strafe_dir = 1;
	if (mlx_is_key_down(data->game->window, MLX_KEY_A))
		data->player->strafe_dir = -1;
}
void    draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, uint32_t color) {
    int dx;
    int dy;
    int    i;

    dx = x1- x0;
    dy = y1 - y0;
    i = -1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    double x_inc = dx / (double)steps;
    double y_inc = dy / (double)steps;

    double x = x0;
    double y = y0;
    while (++i <= steps)
    {
        if (x >= 0 && x < img->width && y >= 0 && y < img->height)
            mlx_put_pixel(img, (int)round(x), (int)round(y), color);
        x += x_inc;
        y += y_inc;
    }
}

bool	if_collition(t_data *data, int32_t x, int32_t y)
{
	int		p_x;
	int		p_y;
	int		h_x;
	int		h_y;

	p_x = x + data->player->imge->instances->x;
	p_y = y + data->player->imge->instances->y;
	h_x = (p_x + HITBOX - 1) / TILE_SIZE;
	h_y = (p_y + HITBOX - 1) / TILE_SIZE;
	if (data->map_arr[p_y / TILE_SIZE][p_x / TILE_SIZE] != '1' && data->map_arr[h_y][h_x] != '1'
		&& data->map_arr[p_y / TILE_SIZE][h_x] != '1' && data->map_arr[h_y][p_x / TILE_SIZE] != '1')
		return (true);
	return (false);
}

void	update_line(mlx_image_t *line, t_data *data, double angle, int dist)
{
	double	start = (data->player->imge->instances->x + cos(angle) * dist);
	double	end = (data->player->imge->instances->y + sin(angle) * dist);
	draw_line(line, data->player->imge->instances->x, data->player->imge->instances->y, start, end, GREEN);
}


void	update_player_pose(t_data *data)
{
	double	move_step;
	double	straf_step;
	int32_t	new_x;
	int32_t	new_y;

	data->player->rot_angle += data->player->turn_dir * data->player->rot_speed;
	data->player->rot_angle = norm_angle(data->player->rot_angle);
	move_step = data->player->walk_dir * SPEED;
	straf_step = data->player->strafe_dir * SPEED;

	new_x = round(cos(data->player->rot_angle) * move_step - sin(data->player->rot_angle) * straf_step);
	new_y = round(sin(data->player->rot_angle) * move_step + cos(data->player->rot_angle) * straf_step);
	
	if (if_collition(data, new_x, new_y))
	{
		data->player->imge->instances->x += new_x;
		data->player->imge->instances->y += new_y;
	}
	data->player->x = data->player->imge->instances->x;
	data->player->y = data->player->imge->instances->y;
	mlx_delete_image(data->game->window, data->player->line);
	data->player->line = mlx_new_image(data->game->window, 3000, data->map_height * TILE_SIZE);
	update_line(data->player->line, data, data->player->rot_angle, 20);
	mlx_image_to_window(data->game->window, data->player->line, 0, 0);
}

void	player_hook(t_data *data)
{
	key_press(data);
	update_player_pose(data);
}