/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:22:10 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 17:41:57 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// This function requires the model space to be already loaded in fdf.
// This function re-calculates the 3D world space from the 3D model space,
// which is required when first rendering, and if some event affects
// the rotation, translation or scaling at the model level.
// To put it briefly: this function transforms the model space to place it into
// the world space.
static int	fdf_setup_world(t_fdf_object *obj)
{
	t_ft_mx			*rot_mx;
	t_ft_mx			*sca_mx;
	t_ft_mx			*tra_mx;
	t_ft_mx			*transf_mx;

	rot_mx = fdf_create_rot_mx(obj->m2w_rot_par[0],
			obj->m2w_rot_par[1],
			obj->m2w_rot_par[2]);
	sca_mx = fdf_create_scale_mx(obj->m2w_sca_par[0],
			obj->m2w_sca_par[1],
			obj->m2w_sca_par[2]);
	tra_mx = fdf_create_transl_mx(obj->m2w_tra_par[0],
			obj->m2w_tra_par[1],
			obj->m2w_tra_par[2]);
	if (rot_mx == NULL || tra_mx == NULL || sca_mx == NULL)
		return (ft_mx_destroy(rot_mx), ft_mx_destroy(sca_mx),
			ft_mx_destroy(tra_mx), 0);
	transf_mx = ft_mx_mult3(rot_mx, sca_mx, tra_mx);
	if (transf_mx == NULL)
		return (ft_mx_destroy(rot_mx), ft_mx_destroy(sca_mx),
			ft_mx_destroy(tra_mx), 0);
	ft_mx_destroy(obj->world_mx);
	obj->world_mx = ft_mx_mult(transf_mx, obj->model_mx);
	return (ft_mx_destroy(rot_mx), ft_mx_destroy(sca_mx), ft_mx_destroy(tra_mx),
		ft_mx_destroy(transf_mx), 1);
}

// This function requires the world space to be already loaded in fdf.
// This function re-calculates the 3D camera space from the 3D world space,
// which is required if some event affects the rotation, translation
// or scaling at the camera level.
// To put it briefly: this function transforms the world space into the camera
// space.
static int	fdf_setup_camera(t_fdf_object *obj)
{
	t_ft_mx			*rot_mx;
	t_ft_mx			*sca_mx;
	t_ft_mx			*tra_mx;
	t_ft_mx			*transf_mx;

	rot_mx = fdf_create_rot_mx(obj->w2c_rot_par[0],
			obj->w2c_rot_par[1],
			obj->w2c_rot_par[2]);
	sca_mx = fdf_create_scale_mx(obj->w2c_sca_par[0],
			obj->w2c_sca_par[1],
			obj->w2c_sca_par[2]);
	tra_mx = fdf_create_transl_mx(obj->w2c_tra_par[0],
			obj->w2c_tra_par[1],
			obj->w2c_tra_par[2]);
	if (rot_mx == NULL || tra_mx == NULL || sca_mx == NULL)
		return (ft_mx_destroy(rot_mx), ft_mx_destroy(sca_mx),
			ft_mx_destroy(tra_mx), 0);
	transf_mx = ft_mx_mult3(rot_mx, sca_mx, tra_mx);
	if (transf_mx == NULL)
		return (ft_mx_destroy(rot_mx), ft_mx_destroy(sca_mx),
			ft_mx_destroy(tra_mx), 0);
	ft_mx_destroy(obj->camera_mx);
	obj->camera_mx = ft_mx_mult(transf_mx, obj->world_mx);
	return (ft_mx_destroy(rot_mx), ft_mx_destroy(sca_mx), ft_mx_destroy(tra_mx),
		ft_mx_destroy(transf_mx), 1);
}

// This function requires the camera space to be already loaded in fdf.
// This function re-calculates the 2D screen view space from the 3D camera
// space, which is required if some event affects the projection, translation
// or scaling at the screen view level (such as resizing the GUI's window).
// To put it briefly: this function transforms the camera space into the screen
// view space.
static int	fdf_setup_screen(uint32_t img_w,
		uint32_t img_h,
		t_fdf_object *obj,
		int autofit)
{
	t_ft_mx			*pro_mx;
	t_ft_mx			*sca_mx;
	t_ft_mx			*tra_mx;
	t_ft_mx			*transf_mx;

	pro_mx = fdf_create_ortoproj_mx();
	if (autofit)
		fdf_get_autofit_transf_par(img_w, img_h, obj);
	sca_mx = fdf_create_scale_mx(obj->c2s_sca_par[0],
			obj->c2s_sca_par[1],
			obj->c2s_sca_par[2]);
	tra_mx = fdf_create_transl_mx(obj->c2s_tra_par[0],
			obj->c2s_tra_par[1],
			obj->c2s_tra_par[2]);
	if (pro_mx == NULL || tra_mx == NULL || sca_mx == NULL)
		return (ft_mx_destroy(pro_mx), ft_mx_destroy(sca_mx),
			ft_mx_destroy(tra_mx), 0);
	transf_mx = ft_mx_mult3(pro_mx, tra_mx, sca_mx);
	if (transf_mx == NULL)
		return (ft_mx_destroy(pro_mx), ft_mx_destroy(sca_mx),
			ft_mx_destroy(tra_mx), 0);
	ft_mx_destroy(obj->screen_mx);
	obj->screen_mx = ft_mx_mult(transf_mx, obj->camera_mx);
	return (ft_mx_destroy(pro_mx), ft_mx_destroy(sca_mx), ft_mx_destroy(tra_mx),
		ft_mx_destroy(transf_mx), 1);
}

// This function requires the view screen space (i.e. the image) to be already
// loaded in fdf.
// This function only manipulates the collection of pixels stored in the image,
// which is required if some event affects the color of the pixels.
// To put it briefly: Here the pixels are drawn on the image.
static int	fdf_setup_image(mlx_image_t *image,
		t_fdf_object *object,
		int drw_hidden_edges,
		int drw_valid_diag_edges)
{
	ft_memset(image->pixels,
		0,
		image->width * image->height * sizeof (int32_t));
	if (!fdf_drw_edges(image, object, drw_hidden_edges, drw_valid_diag_edges))
		return (0);
	return (1);
}

int	fdf_render(t_fdf *fdf)
{
	if (fdf->render_request <= FROM_MODEL)
	{
		if (!fdf_tesselate_map(fdf->object))
			return (0);
	}
	if (fdf->render_request <= FROM_WORLD)
		if (!fdf_setup_world(fdf->object))
			return (0);
	if (fdf->render_request <= FROM_CAMERA)
		if (!fdf_setup_camera(fdf->object))
			return (0);
	if (fdf->render_request <= FROM_SCREEN)
		if (!fdf_setup_screen(fdf->wlayout->image->width,
				fdf->wlayout->image->height,
				fdf->object,
				fdf->autofit))
			return (0);
	if (fdf->render_request <= FROM_IMAGE)
		if (!fdf_setup_image(fdf->wlayout->image, fdf->object,
				fdf->drw_hidden_edges, fdf->drw_valid_diag_edges))
			return (0);
	fdf->render_request = NO_RENDER;
	return (1);
}
/*	

	double		smin[3];
	double		smax[3];
	fdf_get_vertex_min_max(obj->screen_mx, smin, smax);
	printf("[fdf_setup_screen] Min and max for screen space:\n");
	printf("Min X = %f\n", smin[0]);
	printf("Min Y = %f\n", smin[1]);
	printf("Min Z = %f\n", smin[2]);
	printf("Max X = %f\n", smax[0]);
	printf("Max Y = %f\n", smax[1]);
	printf("Max Z = %f\n", smax[2]);


*/	
/*
ft_printf("[fdf_render] The model space vertex matrix");
ft_printf("(%dx%d)...\n", fdf->m->vertex_mx->m, fdf->m->vertex_mx->n);
	ft_mx_print(fdf->m->vertex_mx, ' ');
	ft_printf("\n");
	ft_printf("[fdf_render] The model to world transformation matrix...\n");
	ft_mx_print(fdf->mtow_tr_mx, ' ');
	ft_printf("\n");
	ft_printf("[fdf_render] The world space vertex matrix...\n");
	ft_mx_print(fdf->w->vertex_mx, ' ');
	ft_printf("\n");
	ft_printf("[fdf_render] The world to camera transformation matrix...\n");
	ft_mx_print(fdf->wtoc_tr_mx, ' ');
	ft_printf("\n");
	ft_printf("[fdf_render] The camera space vertex matrix...\n");
	ft_mx_print(fdf->c->vertex_mx, ' ');
	ft_printf("\n");
	ft_printf("[fdf_render] The fdf->s_pro_mx...\n");
	ft_mx_print(fdf->s_pro_mx, ' ');
	ft_printf("\n");
	ft_printf("[fdf_render] The fdf->s_tra_mx...\n");
	ft_mx_print(fdf->s_tra_mx, ' ');
	ft_printf("\n");
	ft_printf("[fdf_render] The fdf->s_sca_mx...\n");
	ft_mx_print(fdf->s_sca_mx, ' ');
	ft_printf("\n");
	ft_printf("[fdf_render] The camera to screen transformation matrix...\n");
	ft_mx_print(fdf->ctos_tr_mx, ' ');
	ft_printf("\n");
	ft_printf("[fdf_render] The screen space vertex matrix...\n");
	ft_mx_print(fdf->s->vertex_mx, ' ');
	ft_printf("\n");
*/
