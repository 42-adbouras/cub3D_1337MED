/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 14:02:54 by fidriss           #+#    #+#             */
/*   Updated: 2025/03/24 13:14:27 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	handle_map_parsing(t_data *data, int i)
{
	data->parsed_map = extract_map_content(data->map_arr + i);
	if (!data->parsed_map || !(*data->parsed_map))
		ft_exit(data, 15, ERR_MAP, true);
	check_map(data->parsed_map);
}

void	check_missing_elements(int id[], int size)
{
	int	k;

	k = 0;
	while (k < size)
	{
		if (id[k] != 1)
			ft_exit(NULL, 14, ERR_ELEM, true);
		k++;
	}
}

void	process_single_line(t_data *data, char *line, int id[], int *flag)
{
	int	j;

	j = 0;
	while (line[j])
	{
		while (line[j] == ' ')
			j++;
		if (ft_strncmp("NO ", line + j, 3) == 0
			|| ft_strncmp("SO ", line + j, 3) == 0
			|| ft_strncmp("WE ", line + j, 3) == 0
			|| ft_strncmp("EA ", line + j, 3) == 0
			|| ft_strncmp("F ", line + j, 2) == 0
			|| ft_strncmp("C ", line + j, 2) == 0)
		{
			check_elements(data, line + j, id);
			break ;
		}
		else if (line[j] == '1' || line[j] == '0')
		{
			call_func(id, data, j, flag);
			break ;
		}
		check_invalid_character(line[j]);
		j++;
	}
}

void	process_map_lines(t_data *data, int id[])
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (data->map_arr[i])
	{
		process_single_line(data, data->map_arr[i], id, &flag);
		if (flag == 1)
			break ;
		i++;
	}
}

void	parse_map(t_data *data)
{
	int	id[6];
	int	i;

	i = 0;
	while (i < 6)
	{
		id[i] = 0;
		i++;
	}
	process_map_lines(data, id);
}
