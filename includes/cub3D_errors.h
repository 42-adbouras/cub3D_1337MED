/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_errors.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:34:14 by adbouras          #+#    #+#             */
/*   Updated: 2025/03/13 13:10:13 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define STDERR 2

#define USAGE "[Usage ./cub3D <map path>]"								//	1
#define USAGE_BONUS "[Usage ./cub3D_bonus <map path>]"					//	1
#define ERR_MALLOC "[Error while allocating memory]"					//	2
#define GAME_WIN "[Failed while loading game window]"					//	3
#define ERR_TEXTURE "[Failed while loading a texture]"					//	4
#define ERR_IMG "[Failed while loading an image]"						//	5
#define IMG_2_WIN "[Failed while loading an image to the window]"		//	6
#define GAME_EXIT "[Thanks for playing]"								//	0

#define FILE_EXT "[Invalide file extention <*.cub>]"					//	7
#define MAP_BORDER "[Invalide map: border]"								//	8
#define MAP_CONTANT "[Invalide map: contant]"							//	9
#define	EMPTY_LINE "[Invalide map: impty line]"							//	10
#define	ERR_COLOR "[Error: invalid color]"								//	11
#define	ERR_FILE "[Error: invalid file]"								//	12
#define ERR_CHAR "[Error: invalid character]"							//	13
#define ERR_ELEM "[Error: missing element]"								//	14