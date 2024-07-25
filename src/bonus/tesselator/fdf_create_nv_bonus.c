/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_create_nv_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:37:06 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 18:59:45 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "fdf_bonus.h"

t_fdf_nv	*fdf_create_nv(t_ft_mx *diag_start,
		t_ft_mx *diag_end,
		t_ft_mx *ort1,
		t_ft_mx *ort2)
{
	t_fdf_nv	*nv;

	nv = ft_calloc(1, sizeof (t_fdf_nv));
	if (nv == NULL)
		return (NULL);
	if (nv == NULL || diag_start == NULL || diag_end == NULL
		|| ort1 == NULL || ort2 == NULL)
		return (free(diag_start), free(diag_end), free(ort1), free(ort2), NULL);
	nv->diag_start = diag_start;
	nv->diag_end = diag_end;
	nv->ort1 = ort1;
	nv->ort2 = ort2;
	return (nv);
}
