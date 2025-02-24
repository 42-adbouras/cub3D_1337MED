/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loading_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:06:12 by adbouras          #+#    #+#             */
/*   Updated: 2025/02/24 10:43:47 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	check_extension_bonus(char *name)
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

void	import_map_bonus(t_data *data, char *path)
{
	char	*line;
	int		fd;

	data->map = NULL;
	if (check_extension_bonus(path) == 1)
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
		data->map = ft_strjoin(data->map, line);
		free(line);
	}
	data->map_arr = ft_split_cub(data->map, '\n');
	close(fd);
}

void	get_map_size_bonus(t_data *data)
{
	int	width;
	int	height;

	height = 0;
	width = (int)ft_strlen(data->parsed_map[0]);
	while (data->parsed_map[height])
	{
		if (height > 0 && width < (int)ft_strlen(data->parsed_map[height - 1]))
			width = (int)ft_strlen(data->parsed_map[height]);
		height++;
	}
	data->map_height = height;
	data->map_width = width;
}

void	draw_minimap_bonus(t_data	*data)
{
	t_mini_map	m;

	m.y = 0;
	m.start_x = data->player->x - (MINI_MAP_WIDTH / 2) / M_MAP_FACT;
	m.start_y = data->player->y - (MINI_MAP_HEIGHT / 2) / M_MAP_FACT;
	while (m.y < MINI_MAP_HEIGHT)
	{
		m.x = 0;
		while (m.x < MINI_MAP_WIDTH)
		{
			m.map_x = (m.start_x + m.x / M_MAP_FACT) / TILE_SIZE;
			m.map_y = (m.start_y + m.y / M_MAP_FACT) / TILE_SIZE;
			if ((m.x >= 0 && m.x < 4 ) || (m.y >= 0 && m.y < 4) || (m.x >= MINI_MAP_WIDTH - 4 && m.x <= MINI_MAP_WIDTH) \
				|| (m.y >= MINI_MAP_HEIGHT - 4 && m.y <= MINI_MAP_HEIGHT))
				mlx_put_pixel(data->minimap, m.x, m.y, rgba(230, 230, 230, 255));
			else if (m.map_y >= 0 && m.map_x >= 0 && m.map_y < data->map_height \
					&& m.map_x < (int)ft_strlen(data->parsed_map[m.map_y]) && data->parsed_map[m.map_y][m.map_x] == '1')
				mlx_put_pixel(data->minimap, m.x, m.y, rgba(230, 230, 230, 255));
			else
				mlx_put_pixel(data->minimap, m.x, m.y, rgba(33, 53, 85, 180));
			m.x++;
		}
		m.y++;
	}
	draw_player_bonus(data);
}

void	draw_player_bonus(t_data *data)
{	
	t_line		line;

	line.start_x = MINI_MAP_WIDTH / 2;
	line.start_y = MINI_MAP_HEIGHT / 2;
	line.end_x = MINI_MAP_WIDTH / 2 + 10 * cos(data->player->rot_angle);
	line.end_y = MINI_MAP_HEIGHT / 2 + 10 * sin(data->player->rot_angle);
	mlx_put_pixel(data->minimap, (MINI_MAP_WIDTH / 2), (MINI_MAP_HEIGHT / 2), RED);
	mlx_put_pixel(data->minimap, (MINI_MAP_WIDTH / 2) + 1, (MINI_MAP_HEIGHT / 2), RED);
	mlx_put_pixel(data->minimap, (MINI_MAP_WIDTH / 2) - 1, (MINI_MAP_HEIGHT / 2), RED);
	mlx_put_pixel(data->minimap, (MINI_MAP_WIDTH / 2), (MINI_MAP_HEIGHT / 2) + 1, RED);
	mlx_put_pixel(data->minimap, (MINI_MAP_WIDTH / 2), (MINI_MAP_HEIGHT / 2) - 1, RED);
	mlx_put_pixel(data->minimap, (MINI_MAP_WIDTH / 2) + 2, (MINI_MAP_HEIGHT / 2), RED);
	mlx_put_pixel(data->minimap, (MINI_MAP_WIDTH / 2) - 2, (MINI_MAP_HEIGHT / 2), RED);
	mlx_put_pixel(data->minimap, (MINI_MAP_WIDTH / 2), (MINI_MAP_HEIGHT / 2) + 2, RED);
	mlx_put_pixel(data->minimap, (MINI_MAP_WIDTH / 2), (MINI_MAP_HEIGHT / 2) - 2, RED);
	draw_line_bonus(data->minimap, line, RED);	
}
