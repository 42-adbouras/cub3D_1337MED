/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parse_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 14:02:54 by fidriss           #+#    #+#             */
/*   Updated: 2025/02/24 10:45:37 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	handle_map_parsing_bonus(t_data *data, int i)
{
	data->parsed_map = extract_map_content_bonus(data->map_arr + i);
	check_map_bonus(data->parsed_map);
}

void	check_missing_elements_bonus(int id[], int size)
{
	int	k;

	k = 0;
	while (k < size)
	{
		if (id[k] != 1)
			print_error_bonus("Error\n Missing element.");
		k++;
	}
}

void	process_single_line_bonus(t_data *data, char *line, int id[], int *flag)
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
			check_elements_bonus(data, line + j, id);
			break ;
		}
		else if (line[j] == '1' || line[j] == '0')
		{
			call_func_bonus(id, data, j, flag);
			break ;
		}
		check_invalid_character_bonus(line[j]);
		j++;
	}
}

void	process_map_lines_bonus(t_data *data, int id[])
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (data->map_arr[i])
	{
		process_single_line_bonus(data, data->map_arr[i], id, &flag);
		if (flag == 1)
			break ;
		i++;
	}
}

void	parse_map_bonus(t_data *data)
{
	int	id[6];
	int	i;

	i = 0;
	while (i < 6)
	{
		id[i] = 0;
		i++;
	}
	process_map_lines_bonus(data, id);
}
