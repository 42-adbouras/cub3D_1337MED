/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:34:54 by adbouras          #+#    #+#             */
/*   Updated: 2025/03/24 13:15:20 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	import_frames_bonus(t_data *data)
{
	int		i;

	i = 0;
	while (i < NUM_SPRITES)
	{
		data->sprites.s_texture[i] = mlx_load_png(data->sprites.path[i]);
		if (!data->sprites.s_texture[i])
			ft_exit_bonus(data, 5, ERR_IMG, true);
		data->sprites.s_images[i] = mlx_texture_to_image(data->game, \
				data->sprites.s_texture[i]);
		i++;
	}
}

void	load_sprites_bonus(t_data *data)
{
	char	*path;
	char	*temp;
	int		fd;

	path = NULL;
	fd = open("assets/sprites/sheet.txt", O_RDONLY);
	while (1)
	{
		temp = get_next_line(fd);
		if (!temp)
			break ;
		path = ft_strjoin(path, temp);
		free(temp);
	}
	data->sprites.path = ft_split_cub(path, '\n');
	free(path);
	close(fd);
	import_frames_bonus(data);
}
