/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_resizehook_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 15:11:50 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 18:46:00 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf_bonus.h"

void	fdf_resizehook(int32_t width, int32_t height, void *f)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)f;
	fdf_window_resize(fdf, width, height);
}
