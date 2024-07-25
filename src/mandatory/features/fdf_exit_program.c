/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_exit_program.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:24:21 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 17:56:37 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Both key hook for ESCAPE and window close hook call this function.
// After calling mlx_close_window() closes the window and breaks the
// MLX loop, re-taking control fdf_startgui().
//
// fdf_startgui() then calls mlx_terminate() and returns to main().
//
// main() does not do any more cleaning MLX-wise. Every cleaning must be done
// either at fdf_exit_program() and fdf_startgui().
//
// A free(fdf->wlayout->image) after mlx_delete_image() throws
// errors (double free).
void	fdf_exit_program(t_fdf *fdf)
{
	mlx_delete_image(fdf->wlayout->window, fdf->wlayout->image);
	mlx_close_window(fdf->wlayout->window);
}
