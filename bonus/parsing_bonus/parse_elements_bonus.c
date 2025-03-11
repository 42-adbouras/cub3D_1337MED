/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:07:10 by starscourge       #+#    #+#             */
/*   Updated: 2025/03/10 12:16:51 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	handle_color_parsing_bonus(t_data *data, char *line, int id[])
{
	if (ft_strncmp("F ", line, 2) == 0)
	{
		if (id[4] == 1)
			print_error_bonus("Error\n Invalid file.");
		id[4] = 1;
	}
	else
	{
		if (id[5] == 1)
			print_error_bonus("Error\n Invalid file.");
		id[5] = 1;
	}
	parse_color_bonus(data, line, id);
}

void	parse_texture_bonus(t_data *data, char *line, int id[], int text_idx)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	while (line[i] && line[i] == ' ')
		i++;
	if (id[text_idx] == 1)
		print_error_bonus("Error\n, Invalid file.\n");
	if (text_idx == 0)
		data->north_texture = ft_strdup(line + i);
	else if (text_idx == 1)
		data->south_texture = ft_strdup(line + i);
	else if (text_idx == 2)
		data->west_texture = ft_strdup(line + i);
	else if (text_idx == 3)
		data->east_texture = ft_strdup(line + i);
	id[text_idx] = 1;
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
		print_error_bonus("Error\n Invalid file.\n");
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
