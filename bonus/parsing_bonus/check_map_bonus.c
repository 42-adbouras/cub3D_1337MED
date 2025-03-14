/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:43:40 by starscourge       #+#    #+#             */
/*   Updated: 2025/03/12 11:00:16 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	check_map_borders_bonus(char **map)
{
	int	i;
	int	j;
	int	row_count;

	i = -1;
	row_count = count_rows_bonus(map, i + 1);
	while (map[++i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_bordered_map_char_bonus(map[i][j]))
			{
				if (is_on_border_bonus(i, j, row_count, map)
					|| is_surrounded_by_spaces_bonus(i, j, map))
					print_error_bonus("Error\n Invalid map.\n");
				if (map[i - 1][j] == ' ' || map[i + 1][j] == ' '
					|| map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
					print_error_bonus("Error\n Invalid map.\n");
				if (map[i][j] == 'C' || map[i][j] == 'O')
					parse_door_bonus(map, i, j);
			}
			j++;
		}
	}
}

void	check_map_content_bonus(char **map)
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
		print_error_bonus("Error\n, Invalid map.\n");
}

void	check_characters_bonus(char	**map)
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
					&& map[i][j] != 'W' && map[i][j] != 'E'
					&& map[i][j] == 'C' && map[i][j] == 'O')
				print_error_bonus("Error\n Invalid character.\n");
			j++;
		}
		i++;
	}
}

void	check_for_empty_lines_bonus(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) == 0 || only_spaces_bonus(map[i]))
			print_error_bonus("Error\n Invalid map.\n");
		i++;
	}
}

void	check_map_bonus(char **map)
{
	int		row_count;

	row_count = 0;
	while (map[row_count])
		row_count++;
	check_map_borders_bonus(map);
	check_map_content_bonus(map);
	check_characters_bonus(map);
	check_for_empty_lines_bonus(map);
}
