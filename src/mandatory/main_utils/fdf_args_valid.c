/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_args_valid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 20:49:29 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 17:59:01 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "fdf.h"

int	fdf_args_valid(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putendl_fd("fdf: must have one and only one argument",
			STDERR_FILENO);
		return (0);
	}
	if (!fdf_filename_valid(argv[1]))
	{
		ft_putendl_fd("fdf: argument must have a .fdf file extension",
			STDERR_FILENO);
		return (0);
	}
	return (1);
}
