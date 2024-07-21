/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_load_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:00:31 by lluque            #+#    #+#             */
/*   Updated: 2024/07/21 12:43:43 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>														// for uint32_t
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
		return (free(trimmed_line), ft_free_strarr_from(col_str_arr, 0), 0);
	col = -1;
	while (++col < matrix->n)
	{
		color_comma_pos = ft_strchr(col_str_arr[col], ',');
		if (color_comma_pos != NULL)
		{



			int	is_error;
			int	color;

			is_error = 0;
			ft_printf("Color info appears to be: '%s'\n", color_comma_pos);
			// checking basic prefix validity
			if (ft_strncmp(color_comma_pos, ",0x", 3) != 0)
				//ft_printf("Color info MALFORMED!!!\n");
				is_error = 1;
			//uint32_t	color;
			color = ft_atoi_b(color_comma_pos + 3, 16);
			if (color == -1)
				is_error = 1;
			if (!is_error)
				ft_printf("Color value: '%d'\n", (uint32_t)color);
			else
				ft_printf("Color info is malformed!!!!\n");





			*color_comma_pos = '\0'; //REMOVE AFTER
		
		}
		if (!ft_aisi(col_str_arr[col]))
			return (free(trimmed_line), ft_free_strarr_from(col_str_arr, 0), 0);
		matrix->d[row * matrix->n + col] = (double)ft_atoi(col_str_arr[col]);
	}
	return (free(trimmed_line), ft_free_strarr_from(col_str_arr, 0), 1);
}

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
			return (free(line), ft_free_gnl(fd),
				ft_mx_destroy(matrix), close(fd), NULL);
		free(line);
	}
	return (ft_free_gnl(fd), close(fd), matrix);
}
