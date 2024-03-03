/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:47:16 by lluque            #+#    #+#             */
/*   Updated: 2024/03/02 19:12:13 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lin_alg.h"
#include "main_utils.h"
#include "drawing.h"
#include "window.h"
#include "fdf.h"
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
		return (ft_printf("Error while creating fdf\n"), ft_mx_destroy(map_mx),  1);
	ft_printf("[main] Tesselating map...'\n");
	fdf->model = fdf_tesselate_map(map_mx);
	ft_mx_destroy(map_mx);
	if (fdf->model == NULL)
		return (ft_printf("Error while tesselating\n"), 1);
	ft_printf("[main] Starting GUI...'\n");
	if (!fdf_start_gui(fdf))
	{
		ft_printf("Error while starting the GUI\n");
		return (fdf_destroy_fdf(fdf), 1);
	}
	return (fdf_destroy_fdf(fdf), 0);
}
/*	
	t_ft_mx	*copy;
	copy = ft_mx_dup(matrix);
	ft_printf("\n");
	ft_printf("A copy...\n");
	ft_mx_print(copy, VAL_SEPARATOR_FILE);
	ft_printf("\n");
	
	ft_mx_smult(copy, 2);
	ft_printf("\n");
	ft_printf("An scalar mutliplication...\n");
	ft_mx_print(copy, VAL_SEPARATOR_FILE);
	ft_printf("\n");

	t_ft_mx	*a_row;
	a_row = ft_mx_get_row(matrix, 2);
	ft_printf("\n");
	ft_printf("A row...\n");
	if (a_row == NULL)
		ft_printf("Nothing to print\n");
	else
		ft_mx_print(a_row, VAL_SEPARATOR_FILE);
	ft_printf("\n");

	t_ft_mx	*a_col;
	a_col = ft_mx_get_col(matrix, 3);
	ft_printf("\n");
	ft_printf("A col...\n");
	if (a_col == NULL)
		ft_printf("Nothing to print\n");
	else
		ft_mx_print(a_col, VAL_SEPARATOR_FILE);
	ft_printf("\n");

	t_ft_mx	*mult;
	mult = ft_mx_mult(matrix, copy);
	ft_printf("\n");
	ft_printf("A result of 2 matrixes multiplicated...\n");
	if (mult == NULL)
		ft_printf("Nothing to print\n");
	else
		ft_mx_print(mult, VAL_SEPARATOR_FILE);
	ft_printf("\n");

	t_ft_mx	*id;
	id = ft_mx_create_id(10);
	ft_printf("\n");
	ft_printf("A identity matrix...\n");
	if (id == NULL)
		ft_printf("Nothing to print\n");
	else
		ft_mx_print(id, VAL_SEPARATOR_FILE);
	ft_printf("\n");

	t_ft_mx	*bid;
	bid = ft_mx_create_bid(5);
	ft_printf("\n");
	ft_printf("A backward identity matrix...\n");
	if (bid == NULL)
		ft_printf("Nothing to print\n");
	else
		ft_mx_print(bid, VAL_SEPARATOR_FILE);
	ft_printf("\n");

	t_ft_mx	*transpose;
	transpose = ft_mx_transpose(matrix);
	ft_printf("\n");
	ft_printf("A transposed matrix...\n");
	if (transpose == NULL)
		ft_printf("Nothing to print\n");
	else
		ft_mx_print(transpose, VAL_SEPARATOR_FILE);
	ft_printf("\n");

	t_ft_mx	*flipped;
	flipped = ft_mx_mult(matrix, bid);
	ft_printf("\n");
	ft_printf("A flipped matrix...\n");
	if (flipped == NULL)
		ft_printf("Nothing to print\n");
	else
		ft_mx_print(flipped, VAL_SEPARATOR_FILE);
	ft_printf("\n");

	t_ft_mx	*flipped2;
	flipped2 = ft_mx_mult(transpose, ft_mx_create_bid(transpose->n));
	ft_printf("\n");
	ft_printf("A flipped2 matrix...\n");
	if (flipped2 == NULL)
		ft_printf("Nothing to print\n");
	else
		ft_mx_print(flipped2, VAL_SEPARATOR_FILE);
	ft_printf("\n");

	ft_printf("\n");
	ft_printf("Again... The matrix read from a file...\n");
	ft_mx_print(matrix, VAL_SEPARATOR_FILE);
	ft_printf("\n");

	t_ft_mx	*flipped3;
	flipped3 = ft_mx_flipr(matrix);
	ft_printf("\n");
	ft_printf("The former flipped along row axis...\n");
	if (flipped3 == NULL)
		ft_printf("Nothing to print\n");
	else
		ft_mx_print(flipped3, VAL_SEPARATOR_FILE);
	ft_printf("\n");
*/
