/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_get_col_num_map_line_bonus.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 01:58:55 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 18:40:35 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include "libft.h"
#include "fdf_bonus.h"

// Takes a line with words separated by a DELIMITER, creates a NULL terminated
// array with said substrings and returns the number of substrings or 0 if
// error.
int	fdf_get_col_num_map_line(char *line, char separator)
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
