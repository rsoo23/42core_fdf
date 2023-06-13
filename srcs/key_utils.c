/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 08:41:07 by rsoo              #+#    #+#             */
/*   Updated: 2023/06/13 18:39:11 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == ESC_KEY)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
		exit(EXIT_SUCCESS);
	}
	else if (keysym == LEFT_ARROW)
		data->shift_x -= 10;
	else if (keysym == RIGHT_ARROW)
		data->shift_x += 10;
	else if (keysym == DOWN_ARROW)
		data->shift_y += 10;
	else if (keysym == UP_ARROW)
		data->shift_y -= 10;
	else if (keysym == 8)
		data->scale_factor += 5;
	else if (keysym == 7 && data->scale_factor > 0)
		data->scale_factor -= 5;
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	make_grid(data);
	printf("keypress: %d\n", keysym);
	return (0);
}

int	handle_mouse(int keysym, t_data *data)
{
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	make_grid(data);
	printf("keypress: %d\n", keysym);
	return (0);
}
