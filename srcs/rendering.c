/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:16:12 by rsoo              #+#    #+#             */
/*   Updated: 2023/06/16 09:54:38 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x > 0 && y > 0 && x < WINDOW_WIDTH && y < WINDOW_HEIGHT)
	{
		pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(unsigned int *)pixel = color;
	}
}

void	render_background(t_img *img, int color)
{
	int x;
	int	y;

	y = -1;
	while (++y < WINDOW_HEIGHT)
	{
		x = -1;
		while (++x < WINDOW_WIDTH)
			img_pix_put(img, x, y, color);
	}
}

void	render_map(t_data *data)
{
	int j;
	int i;

	j = -1;
	while (++j <= data->width)
	{
		i = -1;
		while (++i <= data->length)
		{
			draw_horizontal(i, j, data);
			draw_vertical(i, j, data);
		}
	}
}
