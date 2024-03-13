/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:22:10 by lluque            #+#    #+#             */
/*   Updated: 2024/03/13 22:54:02 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "tesselator.h"
#include "drawing.h"
#include "lin_alg.h"
#include "fdf.h"

// This function requires the model space to be already loaded in fdf.
// This function re-calculates the 3D world space from the 3D model space,
// which is required when first rendering, and if some event affects
// the rotation, translation or scaling at the model level.
// To put it briefly: this function transforms the model space to place it into
// the world space.
static int	fdf_setup_world(t_fdf *fdf)
{
	t_ft_mx			*rot_mx;
	t_ft_mx			*sca_mx;
	t_ft_mx			*tra_mx;
	t_ft_mx			*transf_mx;
	t_fdf_object	*obj;

	obj = fdf->object;
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
	obj->world_mx = ft_mx_mult(transf_mx, obj->model_mx);
	return (1);
}

// This function requires the world space to be already loaded in fdf.
// This function re-calculates the 3D camera space from the 3D world space,
// which is required if some event affects the rotation, translation
// or scaling at the camera level.
// To put it briefly: this function transforms the world space into the camera
// space.
static int	fdf_setup_camera(t_fdf *fdf)
{
	t_ft_mx			*rot_mx;
	t_ft_mx			*sca_mx;
	t_ft_mx			*tra_mx;
	t_ft_mx			*transf_mx;
	t_fdf_object	*obj;

	obj = fdf->object;
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
	obj->camera_mx = ft_mx_mult(transf_mx, obj->world_mx);
	return (1);
}

// This function requires the camera space to be already loaded in fdf.
// This function re-calculates the 2D screen view space from the 3D camera
// space, which is required if some event affects the projection, translation
// or scaling at the screen view level (such as resizing the GUI's window).
// To put it briefly: this function transforms the camera space into the screen
// view space.
static int	fdf_setup_screen(t_fdf *fdf)
{
	t_ft_mx			*pro_mx;
	t_ft_mx			*sca_mx;
	t_ft_mx			*tra_mx;
	t_ft_mx			*transf_mx;
	t_fdf_object	*obj;

	obj = fdf->object;
	pro_mx = fdf_create_ortoproj_mx();
	if (fdf->autofit)
		fdf_get_autofit_transf_par(fdf);
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
	obj->screen_mx = ft_mx_mult(transf_mx, obj->camera_mx);
	return (1);
}

// TODO. Review when it's clear what I want from this...					//////
// TODO may be fdf_drw_vertexes() should be placed here instead...
// This function requires the view screen space (i.e. the image) to be already
// loaded in fdf.
// This function only manipulates the collection of pixels stored in the image,
// which is required if some event affects the color of the pixels.
// To put it briefly: TODO.
static int	fdf_setup_image(t_fdf *fdf)
{
	if (fdf->wlayout->image != NULL)
		mlx_delete_image(fdf->wlayout->window, fdf->wlayout->image);
	fdf->wlayout->image = mlx_new_image(fdf->wlayout->window,
			fdf->wlayout->window_w,
			fdf->wlayout->window_h);
	if (fdf->wlayout->image == NULL)
		return (mlx_terminate(fdf->wlayout->window), 0);
	mlx_image_to_window(fdf->wlayout->window,
		fdf->wlayout->image,
		fdf->wlayout->wintoimg_xoffset,
		fdf->wlayout->wintoimg_yoffset);
	if (!fdf_drw_edges(fdf))
		return (0);
	return (1);
}

int	fdf_render(t_fdf *fdf, t_render_level render_level)
{
	ft_printf("[fdf_render] Rendering...\n");
	if (render_level <= FROM_WORLD)
		if (!fdf_setup_world(fdf))
			return (0);
	if (render_level <= FROM_CAMERA)
		if (!fdf_setup_camera(fdf))
			return (0);
	if (render_level <= FROM_SCREEN)
		if (!fdf_setup_screen(fdf))
			return (0);
	if (render_level <= FROM_IMAGE)
		if (!fdf_setup_image(fdf))
			return (0);
	fdf->render_needed = 0;
	return (1);
}
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
