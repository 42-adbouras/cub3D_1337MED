/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_more_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 19:33:08 by starscourge       #+#    #+#             */
/*   Updated: 2025/02/23 19:11:57 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

bool	is_on_border_bonus(int i, int j, int row_count, char **map)
{
	return (i == 0 || j == 0 || i == row_count
		|| (size_t)j == ft_strlen(map[i]) - 1);
}

bool	is_surrounded_by_spaces_bonus(int i, int j, char **map)
{
	return ((size_t)j > ft_strlen(map[i - 1]) - 1
		|| (size_t)j > ft_strlen(map[i + 1]) - 1);
}

bool	is_bordered_map_char_bonus(char c)
{
	return (c == '0' || c == 'N' || c == 'S' | c == 'W' || c == 'E');
}

void	call_func_bonus(int id[], t_data	*data, int j, int *flag)
{
	check_missing_elements_bonus(id, 6);
	handle_map_parsing_bonus(data, j);
	*flag = 1;
}
