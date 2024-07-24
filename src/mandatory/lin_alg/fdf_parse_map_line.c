/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse_map_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 01:57:08 by lluque            #+#    #+#             */
/*   Updated: 2024/07/24 03:10:42 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include "libft.h"
#include "lin_alg.h"

int	fdf_parse_map_line(char *line, char separator, int row, t_ft_mx **mx)
{
	int		col;
	char	**col_str_arr;
	char	*color_comma_pos;
	char	*trimmed_line;
	int		color;

	trimmed_line = ft_strtrim(line, " \n\t");
	if (line == NULL)
		return (0);
	line = trimmed_line;
	col_str_arr = ft_split(line, separator);
	if (col_str_arr == NULL)
		return (0);
	if (fdf_get_col_num_map_line(line, separator) != mx[Z]->n)
		return (free(trimmed_line), ft_free_strarr_from(col_str_arr, 0), 0);
	col = -1;
	while (++col < mx[Z]->n)
	{
		color_comma_pos = ft_strchr(col_str_arr[col], ',');
		if (color_comma_pos != NULL)
		{
			if (ft_strncmp(color_comma_pos, ",0x", 3) != 0)
				return (free(trimmed_line),
					ft_free_strarr_from(col_str_arr, 0), 0);
			color = ft_atoi_b(color_comma_pos + 3, 16);
			if (color == -1)
				return (free(trimmed_line),
					ft_free_strarr_from(col_str_arr, 0), 0);
			color = (color << 8) | 255;
			mx[C]->d[row * mx[C]->n + col] = color;
			*color_comma_pos = '\0';
		}
		if (!ft_aisi(col_str_arr[col]))
			return (free(trimmed_line), ft_free_strarr_from(col_str_arr, 0), 0);
		mx[Z]->d[row * mx[Z]->n + col] = (double)ft_atoi(col_str_arr[col]);
	}
	return (free(trimmed_line), ft_free_strarr_from(col_str_arr, 0), 1);
}
