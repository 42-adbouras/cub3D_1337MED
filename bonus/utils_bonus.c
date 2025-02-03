/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:12:43 by adbouras          #+#    #+#             */
/*   Updated: 2025/02/03 13:22:41 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

double	norm_angle(double angle)
{
	double	new;

	new = remainder(angle, 2 * M_PI);
	if (new < 0)
		new += (2 * M_PI);
	return (new);
}

static	int	word_count(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c && (i == 0 || s[i - 1] == c)) // Consecutive delimiter case
			count++;
		if (s[i] != c && (i == 0 || s[i - 1] == c)) // Start of a word
			count++;
		i++;
	}
	return (count);
}

static void	ft_free(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static	char	**ft_write(char **array, char const *s, char c, int n)
{
	int	i;
	int	line;
	int	old_i;

	i = 0;
	line = 0;
	while (s[i] != '\0' && line < n)
	{
		if (s[i] == c && (i == 0 || s[i - 1] == c))
		{
			array[line] = ft_substr("", 0, 0);
			if (!array[line])
			{
				ft_free(array);
				return (NULL);
			}
			line++;
		}
		if (s[i] != c)
		{
			old_i = i;
			while (s[i] != '\0' && s[i] != c)
				i++;
			array[line] = ft_substr(s, old_i, i - old_i);
			if (!array[line])
			{
				ft_free(array);
				return (NULL);
			}
			line++;
		}
		if (s[i] == c)
			i++;
	}
	array[line] = NULL;
	return (array);
}

char	**ft_split_cub(char const *s, char c)
{
	int		words;
	char	**array;

	if (s == NULL)
		return (NULL);
	words = word_count(s, c);
	array = (char **)malloc((words + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	array = ft_write(array, s, c, words);
	return (array);
}
