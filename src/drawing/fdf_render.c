/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:22:10 by lluque            #+#    #+#             */
/*   Updated: 2024/03/08 12:24:09 by lluque           ###   ########.fr       */
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
	fdf->w_rot_mx = fdf_create_rot_mx(fdf->w_deg_x, fdf->w_deg_y, fdf->w_deg_z);
	fdf->w_tra_mx = fdf_create_transl_mx(fdf->w_offset_x,
			fdf->w_offset_y,
			fdf->w_offset_z);
	fdf->w_sca_mx = fdf_create_scale_mx(fdf->w_sca_x, fdf->w_sca_y,
			fdf->w_sca_z);
	if (fdf->w_rot_mx == NULL || fdf->w_tra_mx == NULL || fdf->w_sca_mx == NULL)
		return (0);
	fdf->mtow_tr_mx = ft_mx_mult3(fdf->w_rot_mx, fdf->w_sca_mx, fdf->w_tra_mx);
	if (fdf->mtow_tr_mx == NULL)
		return (0);
	fdf->w = fdf_create_model();
	if (fdf->w == NULL)
		return (0);
	fdf->w->vertex_mx = ft_mx_mult(fdf->mtow_tr_mx, fdf->m->vertex_mx);
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
	fdf->c_rot_mx = fdf_create_rot_mx(fdf->c_deg_x, fdf->c_deg_y, fdf->c_deg_z);
	fdf->c_tra_mx = fdf_create_transl_mx(fdf->c_offset_x,
			fdf->c_offset_y,
			fdf->c_offset_z);
	fdf->c_sca_mx = fdf_create_scale_mx(fdf->c_sca_x,
			fdf->c_sca_y,
			fdf->c_sca_z);
	if (fdf->c_rot_mx == NULL || fdf->c_tra_mx == NULL || fdf->c_sca_mx == NULL)
		return (0);
	fdf->wtoc_tr_mx = ft_mx_mult3(fdf->c_rot_mx, fdf->c_sca_mx, fdf->c_tra_mx);
	if (fdf->wtoc_tr_mx == NULL)
		return (0);
	fdf->c = fdf_create_model();
	if (fdf->c == NULL)
		return (0);
	fdf->c->vertex_mx = ft_mx_mult(fdf->wtoc_tr_mx, fdf->w->vertex_mx);
	return (1);
}

// This function requires the camera space to be already loaded in fdf.
// This function re-calculates the 2D screen view space from the 3D camera
// space, which is required if some event affects the projection, translation
// or scaling at the screen view level (such as resizing the GUI's window).
// To put it briefly: this function transforms the camera space into the screen
// view space.
static int	fdf_setup_screen(t_fdf *fdf, int autofit)
{
	fdf->s_pro_mx = fdf_create_ortoproj_mx();
	if (fdf->s_pro_mx == NULL)
		return (0);
	if (autofit)
	{
		if (!fdf_get_autofit_transf_matrixes(fdf))
			return (0);
	}
	else
	{
		fdf->s_tra_mx = fdf_create_transl_mx(fdf->s_offset_x, fdf->s_offset_y,
				0);
		fdf->s_sca_mx = fdf_create_scale_mx(fdf->s_sca_x, fdf->s_sca_y, 0);
	}
	if (fdf->s_pro_mx == NULL || fdf->s_tra_mx == NULL || fdf->s_sca_mx == NULL)
		return (0);
	fdf->ctos_tr_mx = ft_mx_mult3(fdf->s_pro_mx, fdf->s_tra_mx, fdf->s_sca_mx);
	if (fdf->ctos_tr_mx == NULL)
		return (0);
	fdf->s = fdf_create_model();
	if (fdf->s == NULL)
		return (0);
	fdf->s->vertex_mx = ft_mx_mult(fdf->ctos_tr_mx, fdf->c->vertex_mx);
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
	int			autofit;

	autofit = 1;
	if (render_level <= FROM_WORLD)
		if (!fdf_setup_world(fdf))
			return (0);
	if (render_level <= FROM_CAMERA)
		if (!fdf_setup_camera(fdf))
			return (0);
	if (render_level <= FROM_SCREEN)
		if (!fdf_setup_screen(fdf, autofit))
			return (0);
	if (render_level <= FROM_IMAGE)
		if (!fdf_setup_image(fdf))
			return (0);
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
