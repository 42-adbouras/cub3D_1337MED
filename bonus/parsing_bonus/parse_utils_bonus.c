/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:47:58 by starscourge       #+#    #+#             */
/*   Updated: 2025/03/16 13:00:10 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	check_invalid_character_bonus(char c)
{
	if (c != ' ' && c != '\0')
		ft_exit_bonus(NULL, 13, ERR_CHAR, true);
}

int	isspace_bonus(int c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int	only_spaces_bonus(char	*line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (isspace_bonus(line[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	count_rows_bonus(char **map, int i)
{
	while (map[i])
		i++;
	return (i);
}
