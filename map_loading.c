/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:06:12 by adbouras          #+#    #+#             */
/*   Updated: 2025/03/13 11:04:12 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	check_extension(char *name)
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

void	import_map(t_data *data, char *path)
{
	char	*line;
	int		fd;

	data->map = NULL;
	if (check_extension(path) == 1)
		ft_exit(data, 7, FILE_EXT, true);
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

void	get_map_size(t_data *data)
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
