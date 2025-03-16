/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_errors.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:34:14 by adbouras          #+#    #+#             */
/*   Updated: 2025/03/16 12:14:08 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define STDERR 2

#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
#define BBLU "\e[1;34m"
#define RSET "\e[0m"

#define USAGE "[Usage ./cub3D <map path>]"
#define USAGE_BONUS "[Usage ./cub3D_bonus <map path>]"
#define ERR_MALLOC "[Error while allocating memory]"
#define GAME_WIN "[Failed while loading game window]"
#define ERR_TEXTURE "[Failed while loading a texture]"
#define ERR_IMG "[Failed while loading an image]"
#define IMG_2_WIN "[Failed while loading an image to the window]"
#define GAME_EXIT "[Thanks for playing]"

#define FILE_EXT "[Invalide file extention <*.cub>]"
#define MAP_BORDER "[Invalide map: border]"
#define MAP_CONTANT "[Invalide map: contant]"
#define EMPTY_LINE "[Invalide map: impty line]"
#define ERR_COLOR "[Error: invalid color]"
#define ERR_FILE "[Error: invalid file]"
#define ERR_CHAR "[Error: invalid character]"
#define ERR_ELEM "[Error: missing element]"
#define ERR_MAP "[Error: invalid map]"	
#define ERR_DOOR "[Error: invalid door]"
#define EMPTY_MAP "[Error: empty map]"	
