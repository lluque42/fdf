/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse_map_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 01:57:08 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 12:37:08 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include "libft.h"
#include "lin_alg.h"

// This function is only called if memory was previously allocated for
// map_mx[C] and initializar to 0xFFFFFFFF in ft_mx_load_file() after detecting
// the first samples line with color info (it is not assume that every single
// sample actually has color info). Along the same phillosophy, this function
// only writes color info when it is found for the current sample, if not, the
// initialized value of 0xFFFFFFFF remains. None of the previous conditions are
// considered bad enough to throw an error, not here, neither in
// ft_mx_load_file(): some samples may have color information while others
// don't.
//
static int	set_color_value(char *str, int address_index, t_ft_mx **map_mx)
{
	char	*color_str;
	int		color_value;

	color_str = ft_strnstr(str, ",0x", ft_strlen(str));
	if (color_str == NULL)
		return (1);
	color_value = ft_atoi_b(color_str + 3, 16);
	if (color_value == -1)
		return (0);
	color_value = (color_value << 8) | 255;
	map_mx[C]->d[address_index] = color_value;
	return (1);
}

int	fdf_parse_map_line(char *line, char separator, int row, t_ft_mx **mx)
{
	int		col;
	char	**col_str_arr;
	char	*trimmed_line;

	trimmed_line = ft_strtrim(line, " \n\t");
	if (line == NULL)
		return (0);
	line = trimmed_line;
	col_str_arr = ft_split(line, separator);
	if (col_str_arr == NULL)
		return (free(trimmed_line), 0);
	if (fdf_get_col_num_map_line(line, separator) != mx[Z]->n)
		return (free(trimmed_line), ft_free_strarr_from(col_str_arr, 0), 0);
	col = -1;
	while (++col < mx[Z]->n)
	{
		mx[Z]->d[row * mx[Z]->n + col] = (double)ft_atoi(col_str_arr[col]);
		if (!set_color_value(col_str_arr[col], row * mx[Z]->n + col, mx))
			return (free(trimmed_line), ft_free_strarr_from(col_str_arr, 0), 0);
	}
	return (free(trimmed_line), ft_free_strarr_from(col_str_arr, 0), 1);
}
