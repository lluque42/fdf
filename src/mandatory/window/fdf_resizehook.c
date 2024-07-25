/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_resizehook.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 15:11:50 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 18:04:13 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

void	fdf_resizehook(int32_t width, int32_t height, void *f)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)f;
	fdf_window_resize(fdf, width, height);
}
