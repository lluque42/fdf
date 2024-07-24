/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_load_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:00:31 by lluque            #+#    #+#             */
/*   Updated: 2024/07/24 02:46:42 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include "libft.h"
#include "lin_alg.h"

static t_ft_mx	*create_matrix(char *filename,
					char separator,
					double initial_value)
{
	char			*row;
	t_ft_mx_size	size;
	int				fd;
	t_ft_mx			*matrix;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	size.m = 0;
	while (1)
	{
		row = ft_gnl(fd);
		if (row == NULL)
			break ;
		if (size.m == 0)
			size.n = fdf_get_col_num_map_line(row, separator);
		size.m++;
		free(row);
	}
	matrix = ft_mx_create(size.m, size.n);
	if (matrix == NULL)
		return (close(fd), NULL);
	if (initial_value != 0)
		ft_mx_fill(matrix, initial_value);
	return (close(fd), matrix);
}

static int	process_lines(t_ft_mx **map_mx, int fd, char *filename, int row)
{
	char	*line;

	line = ft_gnl(fd);
	if (line == NULL)
		return (ft_mx_destroy(map_mx[Z]), ft_mx_destroy(map_mx[C]),
			free(map_mx), close(fd), 0);
	if (ft_strchr(line, ',') != NULL && map_mx[C] == NULL)
	{
		map_mx[C] = create_matrix(filename, ' ', 0xFFFFFFFF);
		if (map_mx[C] == NULL)
			return (free(line), ft_mx_destroy(map_mx[Z]), free(map_mx),
				close(fd), 0);
	}
	if (!fdf_parse_map_line(line, ' ', row, map_mx))
		return (free(line), ft_free_gnl(fd),
			ft_mx_destroy(map_mx[Z]), ft_mx_destroy(map_mx[C]),
			free(map_mx), close(fd), 0);
	return (free(line), 1);
}

// Array of pointers to matrix, where index Z (0) refers to the matrix with
// the Z values and index C (1) to the matric with the color values.
t_ft_mx	**ft_mx_load_file(char *filename, char separator)
{
	t_ft_mx	**map_mx;
	int		row;
	int		fd;
	int		parsing_ok;

	parsing_ok = 1;
	separator = ' ';
	map_mx = ft_calloc(2, sizeof (t_ft_mx *));
	if (map_mx == NULL)
		return (0);
	map_mx[Z] = create_matrix(filename, separator, 0);
	if (map_mx[Z] == NULL)
		return (free(map_mx), NULL);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ft_mx_destroy(map_mx[Z]), free(map_mx), NULL);
	row = -1;
	while (parsing_ok && ++row < map_mx[Z]->m)
		parsing_ok = process_lines(map_mx, fd, filename, row);
	if (!parsing_ok)
		return (NULL);
	ft_printf("\nMap '%s':\n\tRetrieved a %d x %d matrix.\n", filename,
		map_mx[Z]->m, map_mx[Z]->n);
	return (close(fd), ft_free_gnl(fd), map_mx);
}
