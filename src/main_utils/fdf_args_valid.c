/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_args_valid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 20:49:29 by lluque            #+#    #+#             */
/*   Updated: 2024/03/01 23:07:17 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main_utils.h"

int	fdf_args_valid(int argc, char **argv)
{
	if (argc == 2)
	{
		if (fdf_filename_valid(argv[1]))
			return (1);
	}
	ft_printf("The argument must be a filename with a .fdf file extension\n");
	return (0);
}
