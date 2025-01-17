/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:12:43 by adbouras          #+#    #+#             */
/*   Updated: 2025/01/17 14:01:03 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

double	norm_angle(double angle)
{
	double	new;

	new = remainder(angle, 2 * M_PI);
	if (new < 0)
		new += (2 * M_PI);
	return (new);
}
