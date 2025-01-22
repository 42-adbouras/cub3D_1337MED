/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:43:43 by adbouras          #+#    #+#             */
/*   Updated: 2025/01/22 10:38:56 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	clear_image(mlx_image_t *image)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	while (i < image->height)
	{
		j = 0;
		while (j < image->width)
			mlx_put_pixel(image, j++, i, 0x00000000);
		i++;
	}
}

void	draw_walls(t_data *data)
{
	int	ray;

	ray = -1;
	while (++ray < RAYS)
		render_strip(data, ray, data->text[ray].distance);
}

void	draw_rays(t_data *data)
{
	int	ray;
	
	ray = -1;
	while (++ray < RAYS)
		draw_line(data->frame,
				(data->player->x + (HITBOX / 2)) * MAP_FACT,
				(data->player->y + (HITBOX / 2)) * MAP_FACT,
				data->text[ray].wall_hit_x * MAP_FACT,
				data->text[ray].wall_hit_y * MAP_FACT,
				rgba(192, 242, 255, 255));
}

void	game_loop(void *param)
{
	t_data	*data;

	data = (t_data*) param;
	player_hook(data);
	raycasting(data);

	mlx_delete_image(data->game->window, data->frame);
	data->frame = mlx_new_image(data->game->window, WIDTH, HEIGHT);

	draw_bg(data);
	draw_walls(data);
	if (data->mini_map)
	{
		draw_minimap(data);
		draw_rays(data);
	}

	mlx_image_to_window(data->game->window, data->frame, 0, 0);
}

int	main(int ac, char **av)
{
	t_data	data;

	(void) ac;
	init_data(&data, av[1]);
	// draw_player(data.player->imge);
	mlx_image_to_window(data.game->window, data.player->imge, data.player->x * TILE_SIZE + (TILE_SIZE / 2 - HITBOX), data.player->y * TILE_SIZE + (TILE_SIZE / 2 - HITBOX));
	mlx_loop_hook(data.game->window, game_loop, &data);
	mlx_loop(data.game->window);
}
