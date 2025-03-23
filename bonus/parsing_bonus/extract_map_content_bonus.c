/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map_content_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: starscourge <starscourge@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:46:19 by starscourge       #+#    #+#             */
/*   Updated: 2025/03/23 18:14:44 by starscourge      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

char	**allocate_and_copy_map_bonus(char **map_arr,
			int start_index, int row_count)
{
	char	**new_map_arr;
	int		i;
	int		j;

	i = start_index;
	j = 0;
	new_map_arr = malloc((row_count + 1) * sizeof(char *));
	if (!new_map_arr)
		return (NULL);
	while (map_arr[i])
	{
		new_map_arr[j] = ft_strdup(map_arr[i]);
		i++;
		j++;
	}
	new_map_arr[j] = NULL;
	return (new_map_arr);
}

int	find_start_index_bonus(char **map_arr)
{
	int	i;
	int	j;

	i = 0;
	while (map_arr[i])
	{
		j = 0;
		while (map_arr[i][j])
		{
			if (map_arr[i][j] == 'F' || map_arr[i][j] == 'C')
				break ;
			if (map_arr[i][j] == '1')
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

char	**extract_map_content_bonus(char **map_arr)
{
	int	start_index;
	int	row_count;

	start_index = find_start_index_bonus(map_arr);
	if (start_index == -1)
		return (NULL);
	row_count = count_rows_bonus(map_arr, start_index);
	return (allocate_and_copy_map_bonus(map_arr, start_index, row_count));
}
