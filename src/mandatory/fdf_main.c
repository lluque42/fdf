/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:47:16 by lluque            #+#    #+#             */
/*   Updated: 2024/04/04 23:46:48 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	t_ft_mx	*map_mx;

	if (!fdf_args_valid(argc, argv))
		return (1);
	ft_printf("[main] Loading file...'\n");
	map_mx = ft_mx_load_file(argv[1], VAL_SEPARATOR_FILE);
	if (map_mx == NULL)
		return (ft_printf("Error while loading '%s'\n", argv[1]), 1);
	fdf = fdf_create_fdf(DEF_DRW_WIDTH, DEF_DRW_HEIGHT, map_mx);
	if (fdf == NULL)
		return (ft_printf("Error creating fdf\n"), ft_mx_destroy(map_mx), 1);
	ft_printf("[main] Starting GUI...'\n");
	if (!fdf_start_gui(fdf))
	{
		ft_printf("Error while starting the GUI\n");
		return (fdf_destroy_fdf(fdf), 1);
	}
	ft_printf("[main] Vuelta al main...'\n");
	return (fdf_destroy_fdf(fdf), 0);
}
/*
// Some old tests for auxiliary functions
	t_ft_mx	*a;
	t_ft_mx	*b;
	t_ft_mx	*c;
	t_ft_mx	*d;
	t_ft_mx	*e;
	t_fdf_plane	*plane;

	b = ft_vx_create(1, 2, 3, 0);
	c = ft_vx_create(3, 4, 5, 0);
	a = ft_vx_xproduct(b, c);
	d = ft_vx_substract(b, c);
	ft_printf("Vertex b is:\n");
	ft_mx_print(b, ' ');
	ft_printf("Vertex c is:\n");
	ft_mx_print(c, ' ');
	ft_printf("Vertex a (b x c) is:\n");
	ft_mx_print(a, ' ');
	ft_printf("Vertex d (b - c) is:\n");
	ft_mx_print(d, ' ');
	e = ft_vx_create(1, -2, -7, 0);
	plane = fdf_create_plane(b, c, e);
	ft_printf("Vertex b is in plane: %d\n", fdf_point_is_in_plane(b, plane));
	ft_printf("Vertex c is in plane: %d\n", fdf_point_is_in_plane(c, plane));
	ft_printf("Vertex e is in plane: %d\n", fdf_point_is_in_plane(e, plane));
	ft_printf("Vertex a is in plane: %d\n", fdf_point_is_in_plane(a, plane));
*/
