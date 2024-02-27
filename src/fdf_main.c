/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:47:16 by lluque            #+#    #+#             */
/*   Updated: 2024/02/27 19:52:30 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lin_alg.h"
#include "main_utils.h"
#include "MLX42.h"
#include <stdlib.h>

// Supone que en param viene un mlx_t. Esto se logra al registrar este callback
void my_keyhook(mlx_key_data_t keydata, void* param)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
	{
		ft_printf("Hello (%p)\n", param);
		mlx_close_window(param);
	}
}

void	my_closehook(void *param)
{
	mlx_terminate(param);	
}

#define W_WIDTH 256
#define W_HEIGHT 256

int	main(int argc, char **argv)
{
	t_ft_mx	*matrix;

	if (!args_valid(argc, argv))
		return (1);
	matrix = ft_mx_load_file(argv[1], VAL_SEPARATOR_FILE);
	if (matrix == NULL)
	{
		ft_printf("There was a problem while loading '%s'\n", argv[1]);
		return (1);
	}
	ft_printf("\n");
	ft_printf("The matrix read from a file...\n");
	ft_mx_print(matrix, VAL_SEPARATOR_FILE);
	ft_printf("\n");
	
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
	
	return (0);

	mlx_t		*window;
	mlx_image_t	*image;

	window = mlx_init(W_WIDTH, W_HEIGHT, "lluque's fdf", true);
	//check
	
	image = mlx_new_image(window, W_WIDTH, W_HEIGHT);

	mlx_image_to_window(window, image, 0, 0);

	mlx_put_pixel(image, 128, 128, 0xFF0000FF);

	mlx_key_hook(window, &my_keyhook, window);

	mlx_close_hook(window, my_closehook, window);

	mlx_loop(window);

	//mlx_delete_image(window, image);
	//mlx_terminate(window);

	//close(fd);
	//free(window);
	//free(image);
	return (0);
}
