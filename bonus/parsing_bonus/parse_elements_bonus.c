/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:07:10 by starscourge       #+#    #+#             */
/*   Updated: 2025/03/23 16:09:31 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	handle_color_parsing_bonus(t_data *data, char *line, int id[])
{
	if (ft_strncmp("F ", line, 2) == 0)
	{
		if (id[4] == 1)
			ft_exit_bonus(data, 12, ERR_FILE, true);
		id[4] = 1;
	}
	else
	{
		if (id[5] == 1)
			ft_exit_bonus(data, 12, ERR_FILE, true);
		id[5] = 1;
	}
	parse_color_bonus(data, line, id);
}

void	parse_texture_bonus(t_data *data, char *line, int id[], int texture_index)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	while (line[i] && line[i] == ' ')
		i++;
	if (id[texture_index] == 1)
		ft_exit_bonus(data, 12, ERR_FILE, true);
	if (texture_index == 0)
		data->north_texture = ft_strdup(line + i);
	else if (texture_index == 1)
		data->south_texture = ft_strdup(line + i);
	else if (texture_index == 2)
		data->west_texture = ft_strdup(line + i);
	else if (texture_index == 3)
		data->east_texture = ft_strdup(line + i);
	id[texture_index] = 1;
}

void	handle_texture_parsing_bonus(t_data *data, char *line, int id[])
{
	if (ft_strncmp("NO ", line, 3) == 0)
		parse_texture_bonus(data, line, id, 0);
	else if (ft_strncmp("SO ", line, 3) == 0)
		parse_texture_bonus(data, line, id, 1);
	else if (ft_strncmp("WE ", line, 3) == 0)
		parse_texture_bonus(data, line, id, 2);
	else if (ft_strncmp("EA ", line, 3) == 0)
		parse_texture_bonus(data, line, id, 3);
}

void	open_and_validate_fd_bonus(const char *line, int *fd)
{
	int	i;

	i = 0;
	i = skip_spaces_bonus(line, i);
	*fd = open(line + i, O_RDONLY);
	if (*fd < 0)
		ft_exit_bonus(NULL, 12, ERR_FILE, true);
}

void	check_elements_bonus(t_data *data, char *line, int id[])
{
	int	fd;

	fd = -1;
	if (ft_strncmp("F ", line, 2) == 0 || ft_strncmp("C ", line, 2) == 0)
		handle_color_parsing_bonus(data, line, id);
	else
	{
		open_and_validate_fd_bonus(line, &fd);
		handle_texture_parsing_bonus(data, line, id);
		if (fd != -1)
			close(fd);
	}
}
