/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:43:40 by starscourge       #+#    #+#             */
/*   Updated: 2025/03/24 13:15:20 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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
					ft_exit_bonus(NULL, 8, MAP_BORDER, true);
				if (map[i - 1][j] == ' ' || map[i + 1][j] == ' '
					|| map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
					ft_exit_bonus(NULL, 8, MAP_BORDER, true);
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
		ft_exit_bonus(NULL, 9, MAP_CONTANT, true);
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
				&& map[i][j] != 'C' && map[i][j] != 'O')
				ft_exit_bonus(NULL, 14, ERR_CHAR, true);
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
			ft_exit_bonus(NULL, 9, EMPTY_LINE, true);
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
