/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: starscourge <starscourge@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:06:12 by adbouras          #+#    #+#             */
/*   Updated: 2025/01/24 10:04:43 by starscourge      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

int	check_extension(char	*name)
{
	int	i;

	i = 0;
	if (ft_strlen(name) < 4)
		return (1);
	while (name[i] != '.')
		i++;
	if (ft_strncmp(&name[i], ".cub", 4) != 0)
		return (1);
	return (0);
}

void	import_map(t_data **data, char *path)
{
	char	*line;
	int		fd;

	(*data)->map = NULL;
	if (check_extension(path) == 1)
	{
		printf("Error,\n invalid map extension.");
		exit(1);
	}
	fd = open(path, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		(*data)->map = ft_strjoin((*data)->map, line);
		free(line);
	}
	(*data)->map_arr = ft_split((*data)->map, '\n');
	get_map_size(*data);
	close(fd);
}

void	get_map_size(t_data *data)
{
	int	width;
	int	height;

	height = 0;
	width = (int)ft_strlen(data->map_arr[0]);
	while (data->map_arr[height])
	{
		if (height > 0 && width < (int)ft_strlen(data->map_arr[height - 1]))
			width = (int)ft_strlen(data->map_arr[height]);
		height++;
	}
	data->map_height = height;
	data->map_width = width;
}

void	draw_minimap(t_data	*data)
{
	int		i;
	int		j;

	i = 0;
	while (data->map_arr[i])
	{
		j = 0;
		while (data->map_arr[i][j])
		{
			if (data->map_arr[i][j] == '1')
				draw_tile(data->frame, j, i, rgba(33, 103, 120, 125));
			else if (data->map_arr[i][j] == '0')
				draw_tile(data->frame, j, i, rgba(255, 255, 255, 255));
			else if (data->map_arr[i][j] == 'N')
				draw_tile(data->frame, j, i, rgba(255, 255, 255, 255));
			j++;
		}
		i++;
	}
}

void	draw_tile(mlx_image_t *image, int x, int y ,int color)
{
	int	i;
	int	j;
	int	x_pixel;
	int	y_pixel;

	i = 0;
	while (i < TILE_SIZE * MAP_FACT)
	{
		j = 0;
		y_pixel = y * TILE_SIZE * MAP_FACT + i;
		while (j < TILE_SIZE * MAP_FACT)
		{
			x_pixel = x * TILE_SIZE * MAP_FACT + j;
			if (x_pixel >= 0 && x_pixel < WIDTH && y_pixel >= 0 && y_pixel < HEIGHT)
				mlx_put_pixel(image, x * TILE_SIZE * MAP_FACT + j, y * TILE_SIZE * MAP_FACT + i, color);
			j++;
		}
		i++;
	}
}

void	draw_player(mlx_image_t *image)
{
	int	i;
	int	j;

	i = 0;
	while (i < HITBOX)
	{
		j = 0;
		while (j < HITBOX)
		{
			mlx_put_pixel(image, j, i, 0x00000000);
			j++;
		}
		i++;
	}
}
