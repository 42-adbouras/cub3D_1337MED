/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:43:40 by starscourge       #+#    #+#             */
/*   Updated: 2025/03/16 11:49:43 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
					ft_exit(NULL, 8, MAP_BORDER, true);
				if (map[i - 1][j] == ' ' || map[i + 1][j] == ' '
					|| map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
					ft_exit(NULL, 8, MAP_BORDER, true);
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
		ft_exit(NULL, 9, MAP_CONTANT, true);
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
				ft_exit(NULL, 14, ERR_CHAR, true);
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
			ft_exit(NULL, 9, EMPTY_LINE, true);
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
