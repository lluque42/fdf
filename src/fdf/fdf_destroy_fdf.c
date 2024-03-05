/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_destroy_fdf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:07:42 by lluque            #+#    #+#             */
/*   Updated: 2024/03/05 12:56:26 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fdf.h"

void	fdf_destroy_fdf(t_fdf *fdf)
{
	fdf_destroy_model(fdf->m);
	fdf_destroy_model(fdf->w);
	fdf_destroy_model(fdf->c);
	fdf_destroy_model(fdf->s);
	ft_mx_destroy(fdf->w_rot_mx);
	ft_mx_destroy(fdf->w_tra_mx);
	ft_mx_destroy(fdf->w_sca_mx);
	ft_mx_destroy(fdf->mtow_tr_mx);
	ft_mx_destroy(fdf->c_rot_mx);
	ft_mx_destroy(fdf->c_tra_mx);
	ft_mx_destroy(fdf->c_sca_mx);
	ft_mx_destroy(fdf->wtoc_tr_mx);
	ft_mx_destroy(fdf->s_pro_mx);
	ft_mx_destroy(fdf->s_tra_mx);
	ft_mx_destroy(fdf->s_sca_mx);
	ft_mx_destroy(fdf->ctos_tr_mx);
	fdf_destroy_wlayout(fdf->wlayout);
	free(fdf);
}
