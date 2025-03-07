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
	int		x;		// Horizontal coordinates of the player
	int 		y;		// Vertical coordinates of the player
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

1. Input Handling:

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

W/S: Forward/Backward (walk_dir)\
A/D: Left/Right strafe (strafe_dir)\
Left/Right arrows: Rotation (turn_dir)\
Left Shift: Sprint (increases walk_dir)

2. Updating player position:

	This is how the player is able to move in a 2D environment:

	```c
	void	update_player_pose(t_data *data)
	{
		double	move_step;
		double	straf_step;
		int32_t	new_x;
		int32_t	new_y;

		data->player->rot_angle += data->player->turn_dir * (data->rot_speed);
		data->player->rot_angle = norm_angle(data->player->rot_angle);
		move_step = data->player->walk_dir * (SPEED);
		straf_step = data->player->strafe_dir * (SPEED);
		new_x = round(cos(data->player->rot_angle) * move_step - sin(data->player->rot_angle) * straf_step);
		new_y = round(sin(data->player->rot_angle) * move_step + cos(data->player->rot_angle) * straf_step);
		if (if_collition(data, new_x, new_y))
		{
			data->player->imge->instances->x += new_x;
			data->player->imge->instances->y += new_y;
		}
		data->player->x = data->player->imge->instances->x;
		data->player->y = data->player->imge->instances->y;
	}
	```

	`move_step`: the movement in the forward/backward direction (walking).\
	`strafe_step`: the movement in the left/right direction (strafing).\
	`new_x, new_y`: the new target coordinates the player will try to move to.

	- Adjust Player Rotation (Turning):

		```c
		data->player->rot_angle += data->player->turn_dir * (data->rot_speed);
		data->player->rot_angle = norm_angle(data->player->rot_angle);
		```

	- The player's rotation angle:
		`(rot_angle)` is updated based on the turn direction (turn_dir) and the rotation speed `(rot_speed)`.\
		`turn_dir` is typically `1` for turning right and `-1` for turning left, so this updates the angle the player is facing.\
		`norm_angle` is used to normalize the angle, making sure it stays within the range [0, 2π] in radians.

	- Calculate Movement Step:

		```c
		move_step = data->player->walk_dir * (SPEED);
		strafe_step = data->player->strafe_dir * (SPEED);
		```

		The player can move in the forward/backward direction `(walk_dir)` and in the left/right direction `(strafe_dir)`.

	- `walk_dir` is `1` for moving forward, `-1` for moving backward and `0` you guesses it, not moving.
	- `strafe_dir` is `1` for moving right, `-1` for moving left and `0` not moving.
	- These direction values are multiplied by a constant `(SPEED)`, which defines the speed at which the player moves. So, `move_step` and `strafe_step` are the distances the player will move in each respective direction.

	- Calculate New Position (X and Y):

	```c
	new_x = round(cos(data->player->rot_angle) * move_step - sin(data->player->rot_angle) * strafe_step);
	new_y = round(sin(data->player->rot_angle) * move_step + cos(data->player->rot_angle) * strafe_step);
	```

	![Movement](source_img/movement.png)

	- Forward/Backward Movement:
		- Direction based on viewing angle θ
		- X = cos(θ) * move_step
		- Y = sin(θ) * move_step

	- Strafe Movement:
		- Perpendicular to viewing direction
		- X = -sin(θ) * strafe_step
		- Y = cos(θ) * strafe_step

	- Combined Movement:
		- Sum of forward/backward and strafe vectors
		- Final X = cos(θ) * move_step - sin(θ) * strafe_step
		- Final Y = sin(θ) * move_step + cos(θ) * strafe_step

3. Collision System:

	```c
	bool if_collition(t_data *data, int32_t x, int32_t y)
	{
		int		p_x;
		int		p_y;
		int		h_x;
		int		h_y;

		// Calculate the actual position on the map
		p_x = (x + data->player->x) / TILE_SIZE;
		p_y = (y + data->player->y) / TILE_SIZE;

		// Calculate the position of the opposite corner of hitbox
		h_x = (x + data->player->x + HITBOX - 1) / TILE_SIZE;
		h_y = (y + data->player->y + HITBOX - 1) / TILE_SIZE;

		// Check all corners for collisions
		if (data->parsed_map[p_y][p_x] != '1' \
 			&& data->parsed_map[h_y][h_x] != '1' \
			&& data->parsed_map[p_y][h_x] != '1' \
			&& data->parsed_map[h_y][p_x] != '1')
			return (true);
		return (false);

	}
	```

	The collision system works by checking multiple points around the player's hitbox to prevent walking through walls.

	![Collition](source_img/collision.png)
