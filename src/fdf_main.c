/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:47:16 by lluque            #+#    #+#             */
/*   Updated: 2024/03/17 14:38:35 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "window.h"
#include "libft.h"
#include "lin_alg.h"
#include "main_utils.h"
#include "drawing.h"
#include "tesselator.h"
#define DEF_DRW_WIDTH 500
#define DEF_DRW_HEIGHT 500

int	main(int argc, char **argv)
{
	t_fdf	*fdf;
	t_ft_mx	*map_mx;

	if (!fdf_args_valid(argc, argv))
		return (1);
	ft_printf("[main] Loading file...'\n");
	map_mx = ft_mx_load_file(argv[1], VAL_SEPARATOR_FILE);
	if (map_mx == NULL)
		return (ft_printf("Error while loading '%s'\n", argv[1]), 1);
	fdf = fdf_create_fdf(DEF_DRW_WIDTH, DEF_DRW_HEIGHT);
	if (fdf == NULL)
		return (ft_printf("Error creating fdf\n"), ft_mx_destroy(map_mx), 1);
	ft_printf("[main] Tesselating map...'\n");
	fdf->object = fdf_tesselate_map(map_mx);
	ft_mx_destroy(map_mx);
	if (fdf->object == NULL)
		return (ft_printf("Error while tesselating\n"), 1);
	ft_printf("[main] Starting GUI...'\n");
	if (!fdf_start_gui(fdf))
	{
		ft_printf("Error while starting the GUI\n");
		return (fdf_destroy_fdf(fdf), 1);
	}
	ft_printf("[main] Vuelta al main...'\n");
	return (fdf_destroy_fdf(fdf), 0);
}
