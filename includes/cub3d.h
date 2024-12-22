/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:42:38 by adbouras          #+#    #+#             */
/*   Updated: 2024/12/22 21:05:54 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/get_next_line/get_next_line.h"
#include "../libraries/MLX42/include/MLX42/MLX42.h"
#include "../libraries/libft/libft.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>

typedef	struct		s_data
{
	const char*		map;
}					t_data;