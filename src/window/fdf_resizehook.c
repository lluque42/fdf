/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_resizehook.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 15:11:50 by lluque            #+#    #+#             */
/*   Updated: 2024/03/05 14:12:21 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "libft.h"

void	fdf_resizehook(int32_t width, int32_t height, void *f)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)f;
	ft_printf("Window (%p) resize detected, ", fdf);
	ft_printf("new size: width = %d and height = %d\n", width, height);
}
