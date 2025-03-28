/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map_content.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:46:19 by starscourge       #+#    #+#             */
/*   Updated: 2025/03/24 13:14:27 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	**allocate_and_copy_map(char **map_arr, int start_index, int row_count)
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

int	find_start_index(char **map_arr)
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

char	**extract_map_content(char **map_arr)
{
	int	start_index;
	int	row_count;

	start_index = find_start_index(map_arr);
	if (start_index == -1)
		return (NULL);
	row_count = count_rows(map_arr, start_index);
	return (allocate_and_copy_map(map_arr, start_index, row_count));
}
