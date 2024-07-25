/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:47:16 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 16:46:52 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "fdf.h"
#include "window.h"
#include "libft.h"
#include "lin_alg.h"
#include "main_utils.h"
#include "drawing.h"
#include "tesselator.h"

int	main(int argc, char **argv)
{
	t_fdf	*fdf;
	t_ft_mx	**map_mx;

	if (!fdf_args_valid(argc, argv))
		return (EXIT_FAILURE);
	map_mx = ft_mx_load_file(argv[1], VAL_SEPARATOR_FILE);
	if (map_mx == NULL)
	{
		ft_putendl_fd("fdf: error while loading the file", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	fdf = fdf_create_fdf(DEF_DRW_WIDTH, DEF_DRW_HEIGHT, map_mx);
	if (fdf == NULL)
	{
		ft_putendl_fd("fdf: error creating fdf", STDERR_FILENO);
		return (ft_mx_destroy(map_mx[Z]), ft_mx_destroy(map_mx[C]),
			free(map_mx), EXIT_FAILURE);
	}
	if (!fdf_start_gui(fdf))
	{
		ft_putendl_fd("fdf: error while starting the GUI", STDERR_FILENO);
		return (fdf_destroy_fdf(fdf), ft_mx_destroy(map_mx[Z]),
			ft_mx_destroy(map_mx[C]), free(map_mx), EXIT_FAILURE);
	}
	return (fdf_destroy_fdf(fdf), EXIT_SUCCESS);
}
//	ft_mx_print(map_mx[Z], ' ');
