/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_empty_gnl_mem.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:23:00 by lluque            #+#    #+#             */
/*   Updated: 2024/07/17 16:45:16 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/**
 * @brief <b>fdf_empty_gnl_mem</b> -- Calls ft_gnl() until NULL freeing memory
 *
 * @details When ft_gnl() is used, if the caller doesn't keep calling it until
 * receiving a NULL line, its static variable keeps non-freed memory which
 * results in an pseudo-leak as "still reachable" reported by Valgrind.
 * Calling this function triggers the ft_gnl() to free every memory associated
 * to the static variable in a per-fd basis.
 *
 * @param [in] fd - The file descriptor previously used with ft_gnl().
 *
 * @warning Uses free().
*/
void	fdf_empty_gnl_mem(int fd)
{
	char	*line;

	line = ft_gnl(fd);
	while (line != NULL)
	{
		free(line);
		line = ft_gnl(fd);
	}
}
