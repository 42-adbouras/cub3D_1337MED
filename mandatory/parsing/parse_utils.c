/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:47:58 by starscourge       #+#    #+#             */
/*   Updated: 2025/03/16 11:50:06 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	check_invalid_character(char c)
{
	if (c != ' ' && c != '\0')
		ft_exit(NULL, 13, ERR_CHAR, true);
}

int	isspace(int c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int	only_spaces(char	*line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (isspace(line[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	count_rows(char **map, int i)
{
	while (map[i])
		i++;
	return (i);
}
