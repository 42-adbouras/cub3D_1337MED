/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:00:54 by starscourge       #+#    #+#             */
/*   Updated: 2025/03/14 17:50:13 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	skip_spaces_bonus(const char *line, int i)
{
	while (line[i] != ' ')
		i++;
	while (line[i] == ' ')
		i++;
	return (i);
}

char	**split_and_trim_colors_bonus(const char *line, int i)
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
	if (j != 3)
		print_error_bonus("Error\n Invalid color.\n");
	return (colors);
}

void	validate_colors_bonus(char **colors)
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
				print_error_bonus("Error\n Invalid color.\n");
		}
		i++;
	}
}

void	convert_and_assign_colors_bonus(t_data *data, char **colors,
				const char *line, int id[])
{
	int	i;
	int	color_check;

	i = 0;
	while (colors[i])
	{
		color_check = ft_atoi(colors[i]);
		if (color_check < 0 || color_check > 255)
			print_error_bonus("Error\n Invalid color.\n");
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

void	parse_color_bonus(t_data *data, char *line, int id[])
{
	int		i;
	char	**colors;

	i = 0;
	i = skip_spaces_bonus(line, i);
	colors = split_and_trim_colors_bonus(line, i);
	validate_colors_bonus(colors);
	convert_and_assign_colors_bonus(data, colors, line, id);
	i = 0;
	while (colors[i])
	{
		free(colors[i]);
		i++;
	}
	free(colors);
	i++;
}
