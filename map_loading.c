/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: starscourge <starscourge@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:06:12 by adbouras          #+#    #+#             */
/*   Updated: 2025/01/19 12:42:59 by starscourge      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

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
	if(check_extension(path) == 1)
	{
		printf("Error, invalid file extension.\n");
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
	printf("%d, %d\n", (*data)->map_width, (*data)->map_height);
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
	char	**map_arr;
	int		i;
	int		j;

	i = 0;
	map_arr = ft_split(data->map, '\n');
	draw_tile(data->space, WHITE);
	draw_tile(data->blank, RED);
	draw_tile(data->wall, BLACK);
	draw_player(data->player->imge);
	while (map_arr[i])
	{
		j = 0;
		while (map_arr[i][j])
		{
			if (map_arr[i][j] == '1')
				mlx_image_to_window(data->game->window, data->wall, j * TILE_SIZE * MAP_FACT, i * TILE_SIZE * MAP_FACT);
			else if (map_arr[i][j] == '0')
				mlx_image_to_window(data->game->window, data->space, j * TILE_SIZE * MAP_FACT, i * TILE_SIZE * MAP_FACT);
			else if (map_arr[i][j] == 'N')
				mlx_image_to_window(data->game->window, data->space, j * TILE_SIZE * MAP_FACT, i * TILE_SIZE * MAP_FACT);
			else
				mlx_image_to_window(data->game->window, data->blank, j * TILE_SIZE * MAP_FACT, i * TILE_SIZE * MAP_FACT);
			j++;
		}
		i++;
	}
	mlx_image_to_window(data->game->window, data->player->imge, data->player->x * TILE_SIZE * MAP_FACT, data->player->y * TILE_SIZE * MAP_FACT);
}

void	draw_tile(mlx_image_t *image, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE * MAP_FACT)
	{
		j = 0;
		while (j < TILE_SIZE * MAP_FACT)
		{
			mlx_put_pixel(image, j, i, color);
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
			mlx_put_pixel(image, j, i, RED);
			j++;
		}
		i++;
	}
}
