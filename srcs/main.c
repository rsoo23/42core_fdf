/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:40:53 by rsoo              #+#    #+#             */
/*   Updated: 2023/05/24 14:40:53 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
Notes:
mlx_new_window(mlx, width, height, name): 
    ctrl + c to close window

mlx_loop: 
    initiate window rendering

mlx_loop_hook: 
    add extra functionality to your program by defining 
    a function that gets executed repeatedly within the main loop of 
    your program. It allows you to perform specific tasks or actions at 
    regular intervals while the program is running.

mlx_ptr:
    special key that grants access to the graphics system, 
    allowing you to create and manage graphical windows

win_ptr:
    represents the game window itself, enabling you to interact with 
    it, change its size, and respond to user input.

mlx_ptr is required to create win_ptr and establish a connection to 
the graphics system. Together, they provide the means to display graphics
 and create interactive experiences in a game or program.
*/

// gcc srcs/*.c -lmlx -framework OpenGL -framework AppKit

void	init_point(t_point *point)
{
	point->x = 0;
	point->y = 0;
	point->z = 0;
}

void	init_data(t_data *data)
{
	init_point(&(data->p1));
	init_point(&(data->p2));
	data->shift_x = 0;
	data->shift_y = 0;
	data->scale_factor = 50;
}

int	make_grid(t_data *data)
{
	int		x_index;
	int		y_index;

	y_index = -1;
	while (++y_index < data->width)
	{
		x_index = -1;
		while (++x_index < data->length)
		{
			data->p1.x = x_index * data->scale_factor + data->shift_x;
			data->p1.y = y_index * data->scale_factor + data->shift_y;
			data->p2.x = (x_index + 1) * data->scale_factor + data->shift_x;
			data->p2.y = y_index * data->scale_factor + data->shift_y;
			if (x_index != data->length - 1)
				bresenham_alg(data->p1, data->p2, data);
			data->p2.x = x_index * data->scale_factor + data->shift_x;
			data->p2.y = (y_index + 1) * data->scale_factor + data->shift_y;
			if (y_index != data->width - 1)
				bresenham_alg(data->p1, data->p2, data);
		}
	}
	return (0);
}

int	keyrelease_checker(int keysym)
{
	printf("Keyrelease: %d\n", keysym);
	return (0);
}

// gcc srcs/main.c -Lminilibx_macos -lmlx -framework OpenGL -framework AppKit && ./a.out 42.fdf

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (1);
    data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "FDF");
	if (data.win_ptr == NULL)
		return (1);
	parse_map(av, &data);
	init_data(&data);
	make_grid(&data);
	mlx_hook(data.win_ptr, 2, 1, handle_keypress, &data);
	mlx_hook(data.win_ptr, 4, 0, handle_mouse, &data);
	mlx_loop(data.mlx_ptr);
	free(data.mlx_ptr);
}

/*
Notes:
draw lines based on the width and lengths 

width: 2, length: 2

0 __ 0 __ 0 
|    |    
0 __ 0 __ 0 
|    |    
0    0    0 

Scale up by setting mulitplying the coordinates by a zoom factor

Set color for different altitudes

Isometric Projection Formulas:
 - x' = (x - y) * cos(angle)
 - y' = (x + y) * sin(angle) - z
- the values of x' and y' are in 3d, default angle = 0.8

Translation / Shifting
- use mlx_clear_window
*/
