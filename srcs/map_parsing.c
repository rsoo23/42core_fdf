/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:07:20 by rsoo              #+#    #+#             */
/*   Updated: 2023/06/19 15:24:58 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	assign_altitude_matrix(t_data *data)
{
	char	*line;
	char	**num_arr;

	data->alt_matrix = malloc(sizeof(int *) * (data->height + 2));
	if (!(data->alt_matrix))
		return ;
	data->fd = open(data->infile, O_RDONLY);
	if (data->fd < 0)
		exit_fdf(data, "Failed to open file", EXIT_FAILURE);
	line = get_next_line(data->fd);
	while (line)
	{
		*(data->alt_matrix) = malloc(sizeof(int) * (data->width + 1));
		num_arr = ft_split(line, ' ');
		j = -1;
		while ((*num_arr)++)
			data->alt_matrix[i][j] = ft_atoi(*num_arr);
		free(num_arr);
		free(line);
		line = get_next_line(data->fd);
		*(data->alt_matrix)++;
	}
	*(data->alt_matrix) = 0;
	free(line);
	close(data->fd);
}

static void	get_map_length(char *line, t_data *data)
{
	int	i;
	int	space_count;

	i = 0;
	space_count = 0;
	while (line[i] != '\0')
	{
		i++;
		while (ft_isdigit(line[i]) && line[i])
			i++;
		if (line[i] == ' ')
			space_count++;
		while (line[i] == ' ')
			i++;
	}
	free(line);
	if (data->width == 0)
		data->width = space_count;
	else if (data->width != space_count)
		exit_fdf(data, "Map length error", EXIT_FAILURE);
}

static void	get_map_dimensions(t_data *data)
{
	char	*line;

	data->fd = open(data->infile, O_RDONLY);
	if (data->fd < 0)
		exit_fdf(data, "Failed to open file", EXIT_FAILURE);
	line = get_next_line(data->fd);
	while (line)
	{
		get_map_length(line, data);
		line = get_next_line(data->fd);
		data->height++;
	}
	data->height--;
	free(line);
}

void	parse_map(char **av, t_data *data)
{
	data->infile = ft_strdup(av[1]);
	data->width = 0;
	data->height = 0;
	get_map_dimensions(data);
	assign_altitude_matrix(data);
	free(data->infile);
}
