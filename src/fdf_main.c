/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:47:16 by lluque            #+#    #+#             */
/*   Updated: 2024/02/26 21:31:20 by lluque           ###   ########.fr       */
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
		return (1);
	ft_printf("\n");
	ft_mx_print(matrix, VAL_SEPARATOR_FILE);
	ft_printf("\n");
	
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
