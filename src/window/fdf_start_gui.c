/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_start_gui.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:22:10 by lluque            #+#    #+#             */
/*   Updated: 2024/03/03 16:20:55 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "tesselator.h"
#include "drawing.h"
#include "lin_alg.h"
#include "fdf.h"

int	fdf_start_gui(t_fdf *fdf)
{
	t_ft_mx		*transf_mx;
	//t_ft_mx		*temp;
	mlx_t		*window;
	mlx_image_t	*image;

	ft_printf("\t[fdf_start_gui] Rotating model...\n");
	
	
	fdf->c_rot_mx = fdf_get_rot_mx(45, 90 - 35.264, 45);
	if (fdf->c_rot_mx == NULL)
		return (0);
	fdf->vs_pro_mx = ft_mx_create_ortoproj_mx();
	if (fdf->vs_pro_mx == NULL)
		return (0); // falta??? o destruye arriba al destruir fdf
	// EL ORDEN IMPORTA COÑOOOOO
	transf_mx = ft_mx_mult(fdf->vs_pro_mx, fdf->c_rot_mx);
	if (transf_mx == NULL)
		return (0); // falta??? o destruye arriba al destruir fdf
	ft_mx_transf_m3v(transf_mx, fdf->model->vertex_mx);
	//if (!get_sca_

/*
	if (!fdf_rot_xyz_deg(fdf->model->vertex_mx, 45, 90 - 35.264, 45))
	//if (!ft_rot_xyz_deg(vertex_mx, 0, 35.264, 45))
	//if (!ft_rot_xyz_deg(vertex_mx, 0, 0, 45))
	//if (!ft_rot_xyz_deg(vertex_mx, 0, 0, 0))
		return (0);		//falta
	
	ft_printf("\t[fdf_start_gui] Generating a 2D ortographic projection...\n");

	t_ft_mx	*ortotransfmx;
	
	ortotransfmx = ft_mx_create_ortoproj_mx();
	if (ortotransfmx == NULL)
	{
		ft_printf("There was a problem while creating ortotransfmx\n");
		return (0);		//falta
	}
	ft_mx_transf_m3v(ortotransfmx, fdf->model->vertex_mx);
*/


	/*
	ft_printf("\n");
	ft_printf("The 2D vertex matrix...\n");
	ft_mx_print(model->vertex_mx, VAL_SEPARATOR_FILE);
	ft_printf("\n");
	ft_printf("About to auto scale and center (model = %p)\n", model);
	*/
	//fdf_scale_center(fdf->model->vertex_mx, fdf->wlayout->image_w, fdf->wlayout->image_h);
	fdf_scale_center(fdf);
	//ft_printf("About to create window\n");
	window = mlx_init(fdf->wlayout->window_w, fdf->wlayout->window_h, "lluque's fdf", true);
	//check en todos lados, retornar 0

	image = mlx_new_image(window, fdf->wlayout->window_w, fdf->wlayout->window_h);

	mlx_image_to_window(window, image, fdf->wlayout->wintoimg_xoffset, fdf->wlayout->wintoimg_yoffset);

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
	fdf_drw_vertexes(image, fdf->model->vertex_mx, 0xFFFFFFFF);

	mlx_resize_hook(window, fdf_resizehook, window);

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
