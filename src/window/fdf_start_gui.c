/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_start_gui.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:22:10 by lluque            #+#    #+#             */
/*   Updated: 2024/03/05 12:28:06 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "tesselator.h"
#include "drawing.h"
#include "lin_alg.h"
#include "fdf.h"

int	fdf_start_gui(t_fdf *fdf)
{
	//t_ft_mx		*transf_mx;
	//t_ft_mx		*temp_mx;
	mlx_t		*window;
	mlx_image_t	*image;
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
	
	if (autofit)
	{
		fdf_get_camera_min_max(fdf);
		fdf->s_pro_mx = ft_mx_create_ortoproj_mx();
		if (fdf->s_pro_mx == NULL)
			return (0);
		fdf->s_sca_mx = fdf_create_vsautofit_scale_mx(fdf);
		if (fdf->s_sca_mx == NULL)
			return (0);
		fdf->s_tra_mx = fdf_create_vsautofit_transl_mx(fdf);
		if (fdf->s_tra_mx == NULL)
			return (0);
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
	window = mlx_init(fdf->wlayout->window_w, fdf->wlayout->window_h, "lluque's fdf", true);
	//check en todos lados, retornar 0

	ft_printf("[fdf_start_gui] Creating image...\n");
	image = mlx_new_image(window, fdf->wlayout->window_w, fdf->wlayout->window_h);
	
	ft_printf("[fdf_start_gui] Putting image on windows...\n");
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

	ft_printf("[fdf_start_gui] Drawing vertexes of screen space...\n");

	fdf_drw_vertexes(image, fdf->s->vertex_mx, 0xFFFFFFFF);

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




/*
	ft_printf("\t[fdf_start_gui] Rotating model...\n");

	// aquí vendrían las transformaciones del modelo al mundo
	// TODO or not TODO
	// Se multiplicarían en el orden correcto las matrices de rotación,
	// traslación y escala de modelo a mundo y el resultado queda en
	// transf_mx.
	transf_mx = ft_mx_dup(fdf->c_rot_mx);
	if (transf_mx == NULL)
		return (ft_mx_destroy(fdf->c_rot_mx), 0);
	// TODO or not TODO
	fdf->w = fdf_create_model();
	if (fdf->w == NULL)
		return (ft_mx_destroy(fdf->c_rot_mx), 0);
	fdf->w->vertex_mx = ft_mx_transf_m3v(transf_mx, fdf->m->vertex_mx);

	// aquí vendrían las transformaciones del mundo al espacio de camara
	// TODO or not TODO
	// Se multiplicarían en el orden correcto las matrices de rotación,
	// traslación y escala de modelo a mundo y el resultado queda en
	// transf_mx.


	fdf->vs_pro_mx = ft_mx_create_ortoproj_mx();
	if (fdf->vs_pro_mx == NULL)
		return (0); // falta??? o destruye arriba al destruir fdf
	// EL ORDEN IMPORTA COÑOOOOO
	transf_mx = ft_mx_mult(fdf->vs_pro_mx, fdf->c_rot_mx);
	if (transf_mx == NULL)
		return (0); // falta??? o destruye arriba al destruir fdf
	ft_mx_transf_m3v(transf_mx, fdf->m->vertex_mx);
	//if (!get_sca_


	if (!fdf_rot_xyz_deg(fdf->m->vertex_mx, 45, 90 - 35.264, 45))
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
	ft_mx_transf_m3v(ortotransfmx, fdf->m->vertex_mx);




	ft_printf("\n");
	ft_printf("The 2D vertex matrix...\n");
	ft_mx_print(model->vertex_mx, VAL_SEPARATOR_FILE);
	ft_printf("\n");
	ft_printf("About to auto scale and center (model = %p)\n", model);


	//fdf_scale_center(fdf->m->vertex_mx, fdf->wlayout->image_w, fdf->wlayout->image_h);
	fdf_scale_center(fdf);
	//ft_printf("About to create window\n");
	window = mlx_init(fdf->wlayout->window_w, fdf->wlayout->window_h, "lluque's fdf", true);
	//check en todos lados, retornar 0

	image = mlx_new_image(window, fdf->wlayout->window_w, fdf->wlayout->window_h);

	mlx_image_to_window(window, image, fdf->wlayout->wintoimg_xoffset, fdf->wlayout->wintoimg_yoffset);

	
	// (0,0) rojo
	mlx_put_pixel(image, 0+10, 0+10, 0xFF0000FF);
	// (0,W_HEIGHT) verde
	mlx_put_pixel(image, 0+10, W_HEIGHT-10, 0x00FF00FF);
	// (W_WIDTH, 0) blanco
	mlx_put_pixel(image, W_WIDTH-10, 0+10, 0xFFFFFFFF);
	// (W_WIDTH, W_HEIGHT) azul
	mlx_put_pixel(image, W_WIDTH-10, W_HEIGHT-10, 0x0000FFFF);
	


	fdf_drw_vertexes(image, fdf->m->vertex_mx, 0xFFFFFFFF);

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
*/
