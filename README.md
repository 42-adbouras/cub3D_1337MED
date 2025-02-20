# ToC
- [Introduction](#introduction)
- [Features](#features)
- [Code Structure](#code-structure)
- [Controls](#controls)
- [Technical Concepts](#technical-concepts)
  - [Player Movement](#player-movement)
  - [Raycasting](#raycasting)
  - [Minimap](#minimap)
  - [Texturing](#texturing)
<!-- - [Key Functions](#key-functions) -->
<!-- - [Building and Running](#building-and-running) -->
<!-- - [Credits](#credits) -->

# Introduction

In this project we will discover the world of raycasting, a powerful technique that converts a 2D environment into 3D visuals. As a student of computer graphics, raycasting plays a key role in crafting immersive environments. My exploration of this technique began with this project, which I and my peer @Sstarcourge developed during our time at 1337MED School. In this project, we’ll explore the core principles of a raycasting engine, break down the implementation of cub3D, and reflect on the lessons I learned throughout the journey. Join us as we dive into the fascinating mechanics of raycasting and the dynamic virtual worlds it creates.

# Features

- 3D perspective rendering using raycasting
- Textured walls with different textures for each direction
- Customizable floor and ceiling colors
- Minimap for easy navigation
- Smooth player movement and rotation
- Mouse and keyboard controls
- Sprite animation system
- Collision detection
- Map parsing from configuration files

# Code Structure

The player structor is represented as follows:

```c
typedef struct	s_player {
    mlx_image_t	*imge;		// Player's image/object
    int			x;			// Horizontal coordinates of the player
    int 		y;			// Vertical coordinates of the player
    int 		walk_dir;	// Movement indicator (forward/backward)
    int 		strafe_dir;	// Strafing indicator (left/right)
    int 		turn_dir;	// Turning indicator (left/right)
    double		rot_angle;	// Angle where the player is looking
} t_player;
```

# Controls

- `W`: Move forward
- `S`: Move backward
- `A`: Strafe left
- `D`: Strafe right
- `←`: Rotate camera left
- `→`: Rotate camera right
- `Left Shift`: Run (increased movement speed)
- `ESC`: Exit the game

# Technical Concepts

## Player Movement

- Input Handling:

```c
void	key_press(t_data *data)
{
	data->player->turn_dir = 0;
	data->player->walk_dir = 0;
	data->player->strafe_dir = 0;
	if (mlx_is_key_down(data->game, MLX_KEY_ESCAPE))
		ft_exit(data, 0, true);
	if (mlx_is_key_down(data->game, MLX_KEY_RIGHT))
		data->player->turn_dir = 1;
	if (mlx_is_key_down(data->game, MLX_KEY_LEFT))
		data->player->turn_dir = -1;
	if (mlx_is_key_down(data->game, MLX_KEY_W))
		data->player->walk_dir = 1;
	if (mlx_is_key_down(data->game, MLX_KEY_S))
		data->player->walk_dir = -1;
	if (mlx_is_key_down(data->game, MLX_KEY_D))
		data->player->strafe_dir = 1;
	if (mlx_is_key_down(data->game, MLX_KEY_A))
		data->player->strafe_dir = -1;
	if (mlx_is_key_down(data->game, MLX_KEY_LEFT_SHIFT))
		data->player->walk_dir *= 2.5;
}
```

This sets movement directions based on key inputs:

W/S: Forward/Backward (walk_dir)
A/D: Left/Right strafe (strafe_dir)
Left/Right arrows: Rotation (turn_dir)
Left Shift: Sprint (increases walk_dir)
