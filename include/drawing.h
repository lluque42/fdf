/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:55:20 by lluque            #+#    #+#             */
/*   Updated: 2024/03/21 13:50:45 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file drawing.h
 * TODO Header file for linearly-storaged matrixes (row-major order) operations.
*/

#ifndef DRAWING_H
# define DRAWING_H
# include <math.h>
# include "MLX42.h"
# include "lin_alg.h"
# include "fdf.h"

// Forward declaration, something like a prototype for typedef.
// Needed because both fdf.h and window.h have structs typedefs with member
// types defined in the other file.
typedef struct s_fdf	t_fdf; 

/**
 * @struct s_fdf_line
 * @brief Base for typedef <b>t_ft_mx_line</b>.
 * @details This type is used to store the parameters of a line defined as
 * f(i) = i * m + b. Where i could be X or Y and f(i) Y or X.
 * @var s_fdf_line::m
 * The slope of the line.
 * @var s_fdf_line::b
 * The f(i) value where the associated rect intersects the f(i) axis.
 * @var s_fdf_line::first_i
 * The minimum i coordinate value from where the drawing of the line
 * should start.
 * @var s_fdf_line::last_i
 * The maximum i coordinate value from where the drawing of the line
 * should stop.
 * @var s_fdf_line::i_is_x
 * If 1 the line is a y = f(x) function and must be drawn iterating X
 * from first_i to last_i.  
 * If 0 the line is a x = f(y) function and must be drawn iterating Y
 * from first_i to last_i.
*/
typedef struct s_fdf_line
{
	double		m;
	double		b;
	double		first_i;
	double		last_i;
	int			i_is_x;
}				t_fdf_line;

/**
 * @brief <b>ft_draw_edges</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in] image - The image on which to draw the line.
 *
 * @param [in] object - The 3D object whose edges will be drawn.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
int		fdf_drw_edges(mlx_image_t *image, t_fdf_object *object);

/**
 * @brief <b>fdf_get_autofit_transf_par</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in] img_w - The width of the target image on which to
 * render the object.
 *
 * @param [in] img_h - The height of the target image on which to
 * render the object.
 *
 * @param [in] object - The 3D object to be render.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
void	fdf_get_autofit_transf_par(uint32_t img_w,
			uint32_t img_h,
			t_fdf_object *object);

/**
 * @brief <b>fdf_render</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in, out] fdf - The fdf struct.
 *
 * @return Non-zero value if correct.
 * Value of 0 if error.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
int		fdf_render(t_fdf *fdf);

/**
 * @brief <b>fdf_get_vertex_min_max</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in] vertex_mx - The vertex matrix to analyze.
 *
 * @param [out] min - The size 3 array of double type to store the minimum
 * values found for each axis (0:X: 1:Y; 2:Z) in the vertex matrix. There
 * is no need to initialize this array before calling the function.
 *
 * @param [out] max - The size 3 array of double type to store the maximum
 * values found for each axis (0:X: 1:Y; 2:Z) in the vertex matrix. There
 * is no need to initialize this array before calling the function.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
void	fdf_get_vertex_min_max(t_ft_mx *vertex_mx, double *min, double *max);

#endif
