/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loading_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:06:12 by adbouras          #+#    #+#             */
/*   Updated: 2025/03/23 16:40:52 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
		ft_exit_bonus(data, 12, FILE_EXT, true);
	fd = open(path, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		data->map = ft_strjoin(data->map, line);
		free(line);
	}
	if (!data->map)
		ft_exit_bonus(data, 17, EMPTY_MAP, true);
	printf("------------%s----------\n\n\n\n", data->map);
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
