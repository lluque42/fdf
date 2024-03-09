/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_exit_program.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:24:21 by lluque            #+#    #+#             */
/*   Updated: 2024/03/08 21:31:30 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_features.h"

void	fdf_exit_program(t_fdf *fdf)
{
	ft_printf("Exiting the program...\n");
	mlx_close_window(fdf->wlayout->window);
}
