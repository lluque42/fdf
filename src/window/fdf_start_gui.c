/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_start_gui.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:22:10 by lluque            #+#    #+#             */
/*   Updated: 2024/03/02 13:17:43 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "tesselator.h"
#include "drawing.h"
#include "lin_alg.h"
#define W_WIDTH 500
#define W_HEIGHT 500

int	fdf_start_gui(t_fdf_model *model)
{

	mlx_t           *window;
	mlx_image_t     *image;
	double i_width;
	double i_height;
	i_width = W_WIDTH * 1;
	i_height = W_HEIGHT * 1;

	ft_printf("\t[fdf_start_gui] Rotating model...\n");
	if (!fdf_rot_xyz_deg(model->vertex_mx, 45, 90 - 35.264, 45))
	//if (!ft_rot_xyz_deg(vertex_mx, 0, 35.264, 45))
	//if (!ft_rot_xyz_deg(vertex_mx, 0, 0, 45))
	//if (!ft_rot_xyz_deg(vertex_mx, 0, 0, 0))
		return (0);		//falta
	
	ft_printf("\t[fdf_start_gui] Generating a 2D ortographic projection...\n");

	t_ft_mx	*ortotransfmx;
	
	ortotransfmx = ft_mx_create_ortoproj();
	if (ortotransfmx == NULL)
	{
		ft_printf("There was a problem while creating ortotransfmx\n");
		return (0);		//falta
	}
	ft_mx_transf_m3v(ortotransfmx, model->vertex_mx);
	/*
	ft_printf("\n");
	ft_printf("The 2D vertex matrix...\n");
	ft_mx_print(model->vertex_mx, VAL_SEPARATOR_FILE);
	ft_printf("\n");
	ft_printf("About to auto scale and center (model = %p)\n", model);
	*/
	fdf_scale_center(model->vertex_mx, i_width, i_height);
	//ft_printf("About to create window\n");
	window = mlx_init(W_WIDTH, W_HEIGHT, "lluque's fdf", true);
	//check en todos lados, retornar 0

	image = mlx_new_image(window, i_width + 10, i_height + 10);

	mlx_image_to_window(window, image, 10, 10);

	/*
	// (0,0) rojo
	mlx_put_pixel(image, 0+10, 0+10, 0xFF0000FF);
	// (0,W_HEIGHT) verde
	mlx_put_pixel(image, 0+10, W_HEIGHT-10, 0x00FF00FF);
	// (W_WIDTH, 0) blanco
	mlx_put_pixel(image, W_WIDTH-10, 0+10, 0xFFFFFFFF);
	// (W_WIDTH, W_HEIGHT) azul
	mlx_put_pixel(image, W_WIDTH-10, W_HEIGHT-10, 0x0000FFFF);
	*/
	fdf_drw_vertexes(image, model->vertex_mx, 0xFFFFFFFF);

	mlx_key_hook(window, &fdf_keyhook, window);

	mlx_close_hook(window, &fdf_closehook, window);

	mlx_loop(window);

	//mlx_delete_image(window, image);
	//mlx_terminate(window);

	//close(fd);
	//free(window);
	//free(image);
	return (1);
}
