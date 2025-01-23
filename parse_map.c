/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 14:02:54 by fidriss           #+#    #+#             */
/*   Updated: 2025/01/23 12:04:19 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

int	parse_color(t_data *data, char	*line, int id[])
{
	int		i;
	int		j;
	char	**colors;
	int		color_check;

	i = 0;
	j = 0;
	while (line[i] != ' ')
		i++;
	while (line[i] == ' ')
		i++;
	colors = ft_split(line + i, ',');
	i = 0;
	while (colors[i])
	{
		j = 0;
		while(colors[i][j])
		{
			if (ft_isdigit(colors[i][j]))
				j++;
			else
			{
				printf("Error, invalid color.\n");
				return (1);
			}
		}
		i++;
	}
	i = 0;
	while (colors[i])
	{
		color_check = ft_atoi(colors[i]);
		if (color_check < 0 || color_check > 255)
		{
			printf("Error, invalid color.\n");
			return (1);
		}
		if (ft_strncmp("F ", line, 2) == 0)
		{
			data->floor_color[i] = color_check;
			id[4] = 1;
		}
		else
		{
			data->ceiling_color[i] = color_check;
			id[5] = 1;
		}
		i++;
	}
	return (0);
}

int check_elements(t_data *data, char *line, int id[])
{
	int	i;
	int	fd;

	i = 0;
	while (line[i] != ' ')
		i++;
	printf("%s\n", line + i);
	fd = open(line + i, O_RDONLY);
	if (fd < 0)
	{
		printf("Error, file not found.\n");
		return (1);
	}
	else
	{
		if (ft_strncmp("NO ", line, 3) == 0)
		{
			if (id[0] == 1)
			{
				printf("Error, invalid file.\n");
				return (1);
			}
			data->north_texture = ft_strdup(line + i);
			id[0] = 1;
		}
		else if (ft_strncmp("SO ", line, 3) == 0)
		{
			if (id[1] == 1)
			{
				printf("Error, invalid file.\n");
				return (1);
			}
			data->south_texture = ft_strdup(line + i);
			id[1] = 1;
		}
		else if (ft_strncmp("WE ", line, 3) == 0)
		{
			if (id[2] == 1)
			{
				printf("Error, invalid file.\n");
				return (1);
			}
			data->west_texture = ft_strdup(line + i);
			id[2] = 1;
		}
		else if (ft_strncmp("EA ", line, 3) == 0)
		{
			if (id[3] == 1)
			{
				printf("Error, invalid file.\n");
				return (1);
			}
			data->east_texture = ft_strdup(line + i);
			id[3] = 1;
		}
		else if (ft_strncmp("F ", line, 2) == 0 || ft_strncmp("C ", line, 2) == 0)
		{
			if (id[4] == 1 || id[5] == 1)
			{
				printf("Error, invalid file.\n");
				return (1);
			}
			if (parse_color(data, line, id) == 1)
				return (1);
		}
	}
	close(fd);
	return (0);
}

int check_map_borders(char **map)
{
	int i;
	int j;
	int row_count;

	i = 0;
	j = 0;
	while (map[row_count])
		row_count++;
	row_count--;
	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E')
			{
				if (i == 0 || j == 0 || i == row_count || j == ft_strlen(map[i]) - 1)
				{
					printf("Error, invalid map.\n");
					return (1);
				}
				if (map[i - 1][j] == ' ' || map[i + 1][j] == ' ' || map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
				{
					printf("Error, invalid map.\n");
					return (1);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_map_content(char **map)
{
	int i;
	int j;
	int count;

	i = 0;
	j = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if (map[i][j] == 'S' || map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'E')
				count++;
			j++;
		}
		i++;
	}
	if (count != 1)
	{
		printf("Error, invalid map.\n");
		return (1);
	}
	return (0);
}

int check_characters(char	**map)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != ' ' && map[i][j] != '1' && map[i][j] != '0'&& map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'W' && map[i][j] != 'E')
			{
				printf("Error, invalid character.\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_map(t_data *data, char **map)
{
	int		i;
	int		row_count;

	i = 0;
	row_count = 0;
	while (map[row_count])
		row_count++;
	
	if (check_map_borders(map) == 1)
		return (1);
	if (check_map_content(map) == 1)
		return (1);
	if (check_characters(map) == 1)
		return (1);
	return (0);
}

char **extract_map_content(char **map_arr)
{
    int	 i = 0;
    int 	j = 0;
    int 	start_index = -1;
    int 	row_count = 0;
	char	**new_map_arr;

    while (map_arr[i])
    {
        j = 0;
        while (map_arr[i][j])
        {
            if (map_arr[i][j] == '1')
            {
                start_index = i;
                break;
            }
            j++;
        }
        if (start_index != -1)
            break;
        i++;
    }
    if (start_index != -1)
    {
        i = start_index;
        while (map_arr[i])
        {
            row_count++;
            i++;
        }
    }

    new_map_arr = malloc((row_count + 1) * sizeof(char *));
    if (!new_map_arr)
        return NULL;

    i = start_index;
    j = 0;
    while (map_arr[i])
    {
        new_map_arr[j] = ft_strdup(map_arr[i]);
        i++;
        j++;
    }
    new_map_arr[j] = NULL;

    return (new_map_arr);
}

int parse_map(t_data *data)
{
    int i;
    int j;
    int id[6];
    int k;

    i = 0;
    j = 0;
    k = 0;
    while (i < 6)
	{
        id[i] = 0;
		i++;
	}
    i = 0;
    while (data->map_arr[i])
    {
        j = 0;
        while (data->map_arr[i][j])
        {
            while (data->map_arr[i][j] == ' ')
                j++;
            if (ft_strncmp("NO ", data->map_arr[i] + j, 3) == 0 || ft_strncmp("SO ", data->map_arr[i] + j, 3) == 0
                || ft_strncmp("WE ", data->map_arr[i] + j, 3) == 0 || ft_strncmp("EA ", data->map_arr[i] + j, 3) == 0
                || ft_strncmp("F ", data->map_arr[i] + j, 2) == 0 || ft_strncmp("C ", data->map_arr[i] + j, 2) == 0)
            {
                if (check_elements(data, data->map_arr[i] + j, id) == 1)
					return (1);
            }
            else if (data->map_arr[i][j] == '1')
            {
                while (k < 6)
                {
                    if (id[k] != 1)
                    {
                        printf("Error, missing element.\n");
                        return (1);
                    }
                    k++;
                }
                data->parsed_map = extract_map_content(data->map_arr);
                if (check_map(data, data->parsed_map) == 1)
					return (1);
            }
            else
            {
                printf("Error, invalid map.\n");
                return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}