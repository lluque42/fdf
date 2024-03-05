/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_closehook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:12:54 by lluque            #+#    #+#             */
/*   Updated: 2024/03/05 15:34:05 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "libft.h"

void	fdf_closehook(void *f)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)f;
	ft_printf("Bye!!! (X button) (%p)\n", fdf->wlayout->window);
}
