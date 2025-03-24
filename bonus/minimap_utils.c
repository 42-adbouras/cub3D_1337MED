/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:36:19 by adbouras          #+#    #+#             */
/*   Updated: 2025/03/24 13:15:20 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	draw_minimap_walls(t_data *data, t_mini_map *m)
{
	char	map_char;

	if (m->map_y < 0 || m->map_x < 0 || m->map_y >= data->map_height \
		|| m->map_x >= (int)ft_strlen(data->parsed_map[m->map_y]))
	{
		mlx_put_pixel(data->minimap, m->x, m->y, rgba(230, 230, 230, 180));
		return ;
	}
	map_char = data->parsed_map[m->map_y][m->map_x];
	if (map_char == '1')
		mlx_put_pixel(data->minimap, m->x, m->y, rgba(230, 230, 230, 180));
	else if (map_char == 'C')
		mlx_put_pixel(data->minimap, m->x, m->y, rgba(230, 230, 230, 255));
	else if (map_char == 'O')
		mlx_put_pixel(data->minimap, m->x, m->y, rgba(230, 230, 230, 50));
	else if (map_char == '0')
		mlx_put_pixel(data->minimap, m->x, m->y, rgba(36, 28, 45, 200));
	else
		mlx_put_pixel(data->minimap, m->x, m->y, rgba(230, 230, 230, 180));
}

void	draw_minimap_border(t_data *data, t_mini_map *m)
{
	if ((m->x >= 0 && m->x < 4) || (m->y >= 0 && m->y < 4) \
		|| (m->x >= MINI_WIDTH - 4 && m->x <= MINI_WIDTH) \
		|| (m->y >= MINI_HEIGHT - 4 && m->y <= MINI_HEIGHT))
		mlx_put_pixel(data->minimap, m->x, m->y, rgba(230, 230, 230, 255));
}

void	draw_line_bonus(mlx_image_t *img, t_line line, uint32_t color)
{
	int		i;
	int		steps;
	double	x;
	double	y;

	line.delta_x = line.end_x - line.start_x;
	line.delta_y = line.end_y - line.start_y;
	if (abs(line.delta_x) > abs(line.delta_y))
		steps = abs(line.delta_x);
	else
		steps = abs(line.delta_y);
	line.x_inc = line.delta_x / (double)steps;
	line.y_inc = line.delta_y / (double)steps;
	x = line.start_x;
	y = line.start_y;
	i = -1;
	while (++i <= steps)
	{
		if (x >= 0 && x <= img->width && y >= 0 && y <= img->height)
			mlx_put_pixel(img, (int)round(x), (int)round(y), color);
		x += line.x_inc;
		y += line.y_inc;
	}
}
