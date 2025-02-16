/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: starscourge <starscourge@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:43:40 by starscourge       #+#    #+#             */
/*   Updated: 2025/02/15 16:40:04 by starscourge      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_map_borders(char **map)
{
	int	i;
	int	j;
	int	row_count;

	i = 0;
	j = 0;
	row_count = count_rows(map, i);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_bordered_map_char(map[i][j]))
			{
				if (is_on_border(i, j, row_count, map)
					|| is_surrounded_by_spaces(i, j, map))
					print_error("Error\n Invalid map.\n");
				if (map[i - 1][j] == ' ' || map[i + 1][j] == ' '
					|| map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
					print_error("Error\n Invalid map.\n");
			}
			j++;
		}
		i++;
	}
}

void	check_map_content(char **map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'S' || map[i][j] == 'N'
				|| map[i][j] == 'W' || map[i][j] == 'E')
				count++;
			j++;
		}
		i++;
	}
	if (count != 1)
		print_error("Error\n, Invalid map.\n");
}

void	check_characters(char	**map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != ' ' && map[i][j] != '1' && map[i][j] != '0'
				&& map[i][j] != 'N' && map[i][j] != 'S'
					&& map[i][j] != 'W' && map[i][j] != 'E')
				print_error("Error\n Invalid character.\n");
			j++;
		}
		i++;
	}
}

void	check_for_empty_lines(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) == 0 || only_spaces(map[i]))
			print_error("Error\n Invalid map.\n");
		i++;
	}
}

void	check_map(char **map)
{
	int		row_count;

	row_count = 0;
	while (map[row_count])
		row_count++;
	check_map_borders(map);
	check_map_content(map);
	check_characters(map);
	check_for_empty_lines(map);
}
