/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_load_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:00:31 by lluque            #+#    #+#             */
/*   Updated: 2024/07/18 15:46:28 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "lin_alg.h"

// Takes a line with words separated by a DELIMITER, creates a NULL terminated
// array with said substrings and returns the number of substrings or 0 if
// error.
static int	get_number_of_cols(char *line, char separator)
{
	char	**str_arr;
	char	**temp;
	int		noc;
	char	*trimmed_line;

	trimmed_line = ft_strtrim(line, " \n\t");
	line = trimmed_line;
	str_arr = ft_split(line, separator);
	if (str_arr == NULL)
		return (0);
	noc = 0;
	temp = str_arr;
	while (*temp != NULL)
	{
		noc++;
		free(*temp);
		temp++;
	}
	free(str_arr);
	free(trimmed_line);
	return (noc);
}

static t_ft_mx	*create_matrix(char *filename, char separator)
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
			size.n = get_number_of_cols(row, separator);
		size.m++;
		free(row);
	}
	matrix = ft_mx_create(size.m, size.n);
	if (matrix == NULL)
		return (close(fd), NULL);
	return (close(fd), matrix);
}

static void	free_splitted_from(char **str_arr, int from)
{
	int	i;

	i = from;
	while (str_arr[i] != NULL)
	{
		free(str_arr[i]);
		i++;
	}
	if (from == 0)
		free(str_arr);
}

static int	parse_line(char *line, char separator, int row, t_ft_mx *matrix)
{
	int		col;
	char	**col_str_arr;
	char	*color_comma_pos;
	char	*trimmed_line;

	trimmed_line = ft_strtrim(line, " \n\t");
	line = trimmed_line;
	col_str_arr = ft_split(line, separator);
	if (col_str_arr == NULL)
		return (0);
	if (get_number_of_cols(line, separator) != matrix->n)
		return (free(trimmed_line), free_splitted_from(col_str_arr, 0), 0);
	col = -1;
	while (++col < matrix->n)
	{
		color_comma_pos = ft_strchr(col_str_arr[col], ',');
		if (color_comma_pos != NULL)
			*color_comma_pos = '\0';
		if (!ft_aisi(col_str_arr[col]))
			return (free(trimmed_line), free_splitted_from(col_str_arr, 0), 0);
		matrix->d[row * matrix->n + col] = (double)ft_atoi(col_str_arr[col]);
	}
	return (free(trimmed_line), free_splitted_from(col_str_arr, 0), 1);
}

// Here as prototype to not modify any header because this function is nothing
// more than a future addition to libft
void	fdf_empty_gnl_mem(int fd);

t_ft_mx	*ft_mx_load_file(char *filename, char separator)
{
	t_ft_mx			*matrix;
	int				row;
	char			*line;
	int				fd;

	matrix = create_matrix(filename, separator);
	if (matrix == NULL)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ft_mx_destroy(matrix), NULL);
	row = -1;
	while (++row < matrix->m)
	{
		line = ft_gnl(fd);
		if (line == NULL)
			return (ft_mx_destroy(matrix), close(fd), NULL);
		if (!parse_line(line, separator, row, matrix))
			return (free(line), fdf_empty_gnl_mem(fd),
				ft_mx_destroy(matrix), close(fd), NULL);
		free(line);
	}
	return (fdf_empty_gnl_mem(fd), close(fd), matrix);
}
/*
 * Before compatibility with maps with color info
static int	parse_line(char *line, char separator, int row, t_ft_mx *matrix)
{
	int		col;
	char	**col_str_arr;
	int		len;

	len = ft_strlen(line);
	if (line[len -1] == '\n')
		line[len -1] = '\0';
	col_str_arr = ft_split(line, separator);
	if (col_str_arr == NULL)
		return (0);
	if (get_number_of_cols(line, separator) != matrix->n)
		return (free_splitted_from(col_str_arr, 0), 0);
	col = -1;
	while (++col < matrix->n)
	{
		if (!ft_aisi(col_str_arr[col]))
			return (free_splitted_from(col_str_arr, col), 0);
		matrix->d[row * matrix->n + col] = (double)ft_atoi(col_str_arr[col]);
		free(col_str_arr[col]);
	}
	return (free(col_str_arr), 1);
}
*/
