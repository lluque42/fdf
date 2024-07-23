/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:47:16 by lluque            #+#    #+#             */
/*   Updated: 2024/07/23 23:07:32 by lluque           ###   ########.fr       */
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

// Row flipping the map with "ft_mx_flipr(map_mx);" is what would truly 
// accomplishes the subject's indications:
// • The horizontal position corresponds to its axis (X).
// • The vertical position corresponds to its ordinate (Y).
// • The value corresponds to its altitude (Z).
//
// But the rendering differs too much from the subject's example image
// when using a right-handed convention for drawing XYZ axis.
//
// On the other hand (pun intended), the provided sample program renders the
// image as my version without the row flipping. However, both differ from
// the subject's example image.
//
// Given the "Should render a landscape similar to:" I'll make a deliberate
// compromise and provide my favorite "similar" renderization.
// 		BTW: The image depicted in the subject is not a wireframe since
// 		it has the hidden edges not showing. So the "similar" argument should
// 		go a long way.
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
		return (ft_mx_destroy(map_mx[Z]), ft_mx_destroy(map_mx[C]), free(map_mx), EXIT_FAILURE);
	}
	if (!fdf_start_gui(fdf))
	{
		ft_putendl_fd("fdf: error while starting the GUI", STDERR_FILENO);
		return (fdf_destroy_fdf(fdf), ft_mx_destroy(map_mx[Z]), ft_mx_destroy(map_mx[C]), free(map_mx), EXIT_FAILURE);
	}
	return (fdf_destroy_fdf(fdf), EXIT_SUCCESS);
}
