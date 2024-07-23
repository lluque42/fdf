/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_load_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:00:31 by lluque            #+#    #+#             */
/*   Updated: 2024/07/23 23:10:40 by lluque           ###   ########.fr       */
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
			size.n = get_number_of_cols(row, separator);
		size.m++;
		free(row);
	}
	matrix = ft_mx_create(size.m, size.n);
	if (matrix == NULL)
		return (close(fd), NULL);
	if (initial_value != 0)
//		ft_memset(matrix->d, initial_value, size.m * size.n * sizeof (double));
		ft_mx_fill(matrix, initial_value);
	return (close(fd), matrix);
}

static int	parse_line(char *line, char separator, int row, t_ft_mx **mx)
{
	int		col;
	char	**col_str_arr;
	char	*color_comma_pos;
	char	*trimmed_line;
	int		color;

	trimmed_line = ft_strtrim(line, " \n\t");
	line = trimmed_line;
	col_str_arr = ft_split(line, separator);
	if (col_str_arr == NULL)
		return (0);
	if (get_number_of_cols(line, separator) != mx[Z]->n)
		return (free(trimmed_line), ft_free_strarr_from(col_str_arr, 0), 0);
	col = -1;
	while (++col < mx[Z]->n)												////	This also assumes.... 
	{
		color_comma_pos = ft_strchr(col_str_arr[col], ',');
		if (color_comma_pos != NULL)
		{



			//int	is_error;

			//is_error = 0;
			//ft_printf("Color info appears to be: '%s'\n", color_comma_pos);
			// checking basic prefix validity
			if (ft_strncmp(color_comma_pos, ",0x", 3) != 0)
				return (free(trimmed_line),
						ft_free_strarr_from(col_str_arr, 0), 0);
			//{
			//	ft_printf("Color info MALFORMED!!!\n");
			//	is_error = 1;
			//}
			color = ft_atoi_b(color_comma_pos + 3, 16);
			if (color == -1)
				return (free(trimmed_line),
						ft_free_strarr_from(col_str_arr, 0), 0);
				//is_error = 1;


			color = color << 8;
			color = color | 255;




			mx[C]->d[row * mx[C]->n + col] = color;



/*
			if (!is_error)
				ft_printf("Color value: '%d'\n", (uint32_t)color);
			else
			{
				// return 0 after freeing everything
				ft_printf("Color info is malformed!!!!\n");
			}
*/



			*color_comma_pos = '\0'; //REMOVE AFTER
		
		}
		if (!ft_aisi(col_str_arr[col]))
			return (free(trimmed_line), ft_free_strarr_from(col_str_arr, 0), 0);
		mx[Z]->d[row * mx[Z]->n + col] = (double)ft_atoi(col_str_arr[col]);
	}
	return (free(trimmed_line), ft_free_strarr_from(col_str_arr, 0), 1);
}



// Array of pointers to matrix, where index Z (0) refers to the matrix with
// the Z values and index C (1) to the matric with the color values.
t_ft_mx	**ft_mx_load_file(char *filename, char separator)
{
	t_ft_mx			**map_mx;
	int				row;
	char			*line;
	int				fd;

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
	while (++row < map_mx[Z]->m)											// This assumes both are of the same size. CHECK if any error could falsify this
	{
		line = ft_gnl(fd);
		if (line == NULL)
			return (ft_mx_destroy(map_mx[Z]), ft_mx_destroy(map_mx[C]),
					free(map_mx), close(fd), NULL);
	//		return (ft_mx_destroy(matrix), close(fd), NULL);
		if (ft_strchr(line, ',') != NULL && map_mx[C] == NULL)
		{
			map_mx[C] = create_matrix(filename, separator, 0xFFFFFFFF);
			if (map_mx[C] == NULL)
				return (free(line), ft_mx_destroy(map_mx[Z]), free(map_mx),
						close(fd), NULL);
		}
		if (!parse_line(line, separator, row, map_mx))
	//		return (free(line), ft_free_gnl(fd),
	//			ft_mx_destroy(matrix), close(fd), NULL);
			return (free(line), ft_free_gnl(fd),
					ft_mx_destroy(map_mx[Z]), ft_mx_destroy(map_mx[C]),
					free(map_mx), close(fd), NULL);
		free(line);
	}
	ft_printf("\nMap '%s' loaded:\n", filename);
	ft_printf("\tMap loaded is a %d x %d matrix (m x n or rows, columns).\n",
			map_mx[Z]->m, map_mx[Z]->n);
	return (ft_free_gnl(fd), close(fd), map_mx);
}
