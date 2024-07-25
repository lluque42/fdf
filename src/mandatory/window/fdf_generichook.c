/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_generichook.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 21:56:31 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 19:08:22 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "fdf.h"

void	fdf_generichook(void *f)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)f;
	if (!fdf_render(fdf))
	{
		ft_putendl_fd("fdf: error while rendering", STDERR_FILENO);
		fdf_exit_program(fdf);
	}
}
