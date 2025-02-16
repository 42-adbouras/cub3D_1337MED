/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: starscourge <starscourge@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:00:54 by starscourge       #+#    #+#             */
/*   Updated: 2025/02/15 17:29:15 by starscourge      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	skip_spaces(const char *line, int i)
{
	while (line[i] != ' ')
		i++;
	while (line[i] == ' ')
		i++;
	return (i);
}

char	**split_and_trim_colors(const char *line, int i)
{
	char	**colors;
	char	*tmp;
	int		j;

	j = 0;
	colors = ft_split(line + i, ',');
	while (colors[j])
	{
		tmp = ft_strtrim(colors[j], " ");
		free(colors[j]);
		colors[j] = tmp;
		j++;
	}
	return (colors);
}

void	validate_colors(char **colors)
{
	int	i;
	int	j;

	i = 0;
	while (colors[i])
	{
		j = 0;
		while (colors[i][j])
		{
			if (ft_isdigit(colors[i][j]))
				j++;
			else
				print_error("Error\n Invalid color.\n");
		}
		i++;
	}
}

void	convert_and_assign_colors(t_data *data, char **colors,
				const char *line, int id[])
{
	int	i;
	int	color_check;

	i = 0;
	while (colors[i])
	{
		color_check = ft_atoi(colors[i]);
		if (color_check < 0 || color_check > 255)
			print_error("Error\n Invalid color.\n");
		if (ft_strncmp("F ", line, 2) == 0)
		{
			data->floor_color[i] = color_check;
			id[4] = 1;
		}
		else
		{
			data->ceiling_color[i] = color_check;
			id[5] = 1;
		}
		i++;
	}
}

void	parse_color(t_data *data, char *line, int id[])
{
	int		i;
	char	**colors;

	i = 0;
	i = skip_spaces(line, i);
	colors = split_and_trim_colors(line, i);
	validate_colors(colors);
	convert_and_assign_colors(data, colors, line, id);
	i = 0;
	while (colors[i])
	{
		free(colors[i]);
		i++;
	}
	free(colors);
	i++;
}
