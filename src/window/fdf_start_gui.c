/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_start_gui.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:22:10 by lluque            #+#    #+#             */
/*   Updated: 2024/03/05 14:16:49 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "tesselator.h"
#include "drawing.h"
#include "lin_alg.h"
#include "fdf.h"

int	fdf_start_gui(t_fdf *fdf)
{
	int			autofit;

	autofit = 1;
	ft_printf("[fdf_start_gui] The model space vertex matrix (%dx%d)...\n", fdf->m->vertex_mx->m, fdf->m->vertex_mx->n);
	ft_mx_print(fdf->m->vertex_mx, ' ');
	ft_printf("\n");
	// En este punto se tiene el modelo...
	// Ahora se transformará del modelo al mundo
	// Por ahora uso matrices de identidad para
	// no transformar donde no hace falta
	fdf->w_rot_mx = ft_mx_create_id(4);
	fdf->w_tra_mx = ft_mx_create_id(4);
	fdf->w_sca_mx = ft_mx_create_id(4);
	// EL ORDEN IMPORTA COÑOOOOO
	fdf->mtow_tr_mx = ft_mx_mult3(fdf->w_rot_mx, fdf->w_sca_mx, fdf->w_tra_mx);
	if (fdf->mtow_tr_mx == NULL)
		return (0);		// Falta...
	fdf->w = fdf_create_model();
	if (fdf->w == NULL)
		return (0);
	//fdf->w->vertex_mx = ft_mx_transf_m3v(fdf->mtow_tr_mx, fdf->m->vertex_mx);
	fdf->w->vertex_mx = ft_mx_mult(fdf->mtow_tr_mx, fdf->m->vertex_mx);

	ft_printf("[fdf_start_gui] The model to world transformation matrix...\n");
	ft_mx_print(fdf->mtow_tr_mx, ' ');
	ft_printf("\n");
	ft_printf("[fdf_start_gui] The world space vertex matrix...\n");
	ft_mx_print(fdf->w->vertex_mx, ' ');
	ft_printf("\n");

	// En este punto se tiene el mundo...
	// Ahora se transformará del mundo al espacio de camara
	// Por ahora uso matrices de identidad para
	// no transformar donde no hace falta
	fdf->c_rot_mx = fdf_get_rot_mx(45, 90 - 35.264, 45);
	//fdf->c_rot_mx = fdf_get_rot_mx(35.264, 45, 0);
	//fdf->c_rot_mx = fdf_get_rot_mx(0, 0, 0);
	if (fdf->c_rot_mx == NULL)
		return (0);
	fdf->c_tra_mx = ft_mx_create_id(4);
	fdf->c_sca_mx = ft_mx_create_id(4);
	// EL ORDEN IMPORTA COÑOOOOO
	fdf->wtoc_tr_mx = ft_mx_mult3(fdf->c_rot_mx, fdf->c_sca_mx, fdf->c_tra_mx);
	if (fdf->wtoc_tr_mx == NULL)
		return (0);		// Falta...
	fdf->c = fdf_create_model();
	if (fdf->c == NULL)
		return (0);
	fdf->c->vertex_mx = ft_mx_mult(fdf->wtoc_tr_mx, fdf->w->vertex_mx);


	ft_printf("[fdf_start_gui] The world to camera transformation matrix...\n");
	ft_mx_print(fdf->wtoc_tr_mx, ' ');
	ft_printf("\n");
	ft_printf("[fdf_start_gui] The camera space vertex matrix...\n");
	ft_mx_print(fdf->c->vertex_mx, ' ');
	ft_printf("\n");


	// En este punto se tiene el espacio de camara...
	// Ahora se transformará del espacio de camara al de vista de pantalla
	// Por ahora uso matrices de identidad para
	// no transformar donde no hace falta
	
	fdf->s_pro_mx = ft_mx_create_ortoproj_mx();
	if (fdf->s_pro_mx == NULL)
		return (0);
	if (autofit)
	{
		if (!fdf_get_autofit_transf_matrixes(fdf))
			return (0);
		/*
		fdf_get_camera_min_max(fdf);
		fdf->s_sca_mx = fdf_create_vsautofit_scale_mx(fdf);
		if (fdf->s_sca_mx == NULL)
			return (0);
		fdf->s_tra_mx = fdf_create_vsautofit_transl_mx(fdf);
		if (fdf->s_tra_mx == NULL)
			return (0);
		*/
	}
	ft_printf("[fdf_start_gui] The fdf->s_pro_mx...\n");
	ft_mx_print(fdf->s_pro_mx, ' ');
	ft_printf("\n");
	ft_printf("[fdf_start_gui] The fdf->s_tra_mx...\n");
	ft_mx_print(fdf->s_tra_mx, ' ');
	ft_printf("\n");
	ft_printf("[fdf_start_gui] The fdf->s_sca_mx...\n");
	ft_mx_print(fdf->s_sca_mx, ' ');
	ft_printf("\n");
	
	
	
	// EL ORDEN IMPORTA COÑOOOOO
	//temp_mx = ft_mx_mult(fdf->s_tra_mx, fdf->s_sca_mx);			GIGANTE
	//temp_mx = ft_mx_mult(fdf->s_sca_mx, fdf->s_tra_mx);				GIGANTE
	//temp_mx = ft_mx_mult(fdf->s_pro_mx, fdf->s_sca_mx);			
	// EL ORDEN IMPORTA COÑOOOOO
	fdf->ctos_tr_mx = ft_mx_mult3(fdf->s_pro_mx, fdf->s_tra_mx, fdf->s_sca_mx);
	if (fdf->ctos_tr_mx == NULL)
		return (0);		// Falta...
	fdf->s = fdf_create_model();
	if (fdf->s == NULL)
		return (0);
	fdf->s->vertex_mx = ft_mx_mult(fdf->ctos_tr_mx, fdf->c->vertex_mx);


	ft_printf("[fdf_start_gui] The camera to screen transformation matrix...\n");
	ft_mx_print(fdf->ctos_tr_mx, ' ');
	ft_printf("\n");
	ft_printf("[fdf_start_gui] The screen space vertex matrix...\n");
	ft_mx_print(fdf->s->vertex_mx, ' ');
	ft_printf("\n");








	



	ft_printf("[fdf_start_gui] Initializing window...\n");
	ft_printf("fdf->wlayout->window_w = %d, fdf->wlayout->window_h = %d\n", (int)fdf->wlayout->window_w, (int)fdf->wlayout->window_h);
	fdf->wlayout->window = mlx_init(fdf->wlayout->window_w, fdf->wlayout->window_h, "lluque's fdf", true);
	//check en todos lados, retornar 0

	ft_printf("[fdf_start_gui] Creating image...\n");
	fdf->wlayout->image = mlx_new_image(fdf->wlayout->window, fdf->wlayout->window_w, fdf->wlayout->window_h);
	
	ft_printf("[fdf_start_gui] Putting image on windows...\n");
	mlx_image_to_window(fdf->wlayout->window, fdf->wlayout->image, fdf->wlayout->wintoimg_xoffset, fdf->wlayout->wintoimg_yoffset);

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

	ft_printf("[fdf_start_gui] Drawing vertexes of screen space...\n");

	fdf_drw_vertexes(fdf->wlayout->image, fdf->s->vertex_mx, 0xFFFFFFFF);

	mlx_resize_hook(fdf->wlayout->window, fdf_resizehook, fdf);

	mlx_key_hook(fdf->wlayout->window, &fdf_keyhook, fdf);

	mlx_close_hook(fdf->wlayout->window, &fdf_closehook, fdf);

	mlx_loop(fdf->wlayout->window);

	//mlx_delete_image(window, image);
	//mlx_terminate(window);

	//close(fd);
	//free(window);
	//free(image);
	return (1);
}
