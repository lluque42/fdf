/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_destroy_nv_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:43:59 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 18:43:54 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fdf_bonus.h"

void	fdf_destroy_nv(t_fdf_nv *nv)
{
	ft_mx_destroy(nv->diag_start);
	ft_mx_destroy(nv->diag_end);
	ft_mx_destroy(nv->ort1);
	ft_mx_destroy(nv->ort2);
	free(nv);
}
