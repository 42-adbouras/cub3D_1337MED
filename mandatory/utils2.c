/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: starscourge <starscourge@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 04:25:38 by starscourge       #+#    #+#             */
/*   Updated: 2025/03/23 04:33:36 by starscourge      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static	char	*allocate_empty_string(void)
{
	return (ft_substr("", 0, 0));
}

static	int	allocate_and_store(char **array, int line, char const *substring)
{
	array[line] = ft_substr(substring, 0, ft_strlen(substring));
	if (!array[line])
	{
		ft_free(array);
		return (0);
	}
	return (1);
}

static int	handle_delimiter_case(char **array, int *line)
{
	array[*line] = allocate_empty_string();
	if (!array[*line])
		return (0);
	(*line)++;
	return (1);
}

static int	handle_word_case(char **array, char const *s, int *i, int *line)
{
	int		old_i;
	char	*substring;

	old_i = *i;
	while (s[*i] != '\0' && s[*i] != ' ')
		(*i)++;
	substring = ft_substr(s, old_i, *i - old_i);
	if (!allocate_and_store(array, *line, substring))
	{
		free(substring);
		return (0);
	}
	free(substring);
	(*line)++;
	return (1);
}

static int	process_split(char **array, char const *s, char c, int n)
{
	int	i;
	int	line;

	i = 0;
	line = 0;
	while (s[i] != '\0' && line < n)
	{
		if (s[i] == c && (i == 0 || s[i - 1] == c))
		{
			if (!handle_delimiter_case(array, &line))
				return (0);
		}
		if (s[i] != c)
		{
			if (!handle_word_case(array, s, &i, &line))
				return (0);
		}
		if (s[i] == c)
			i++;
	}
	array[line] = NULL;
	return (1);
}

