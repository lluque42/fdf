/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:55:20 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 17:32:53 by lluque           ###   ########.fr       */
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
# include "fdf.h"

/**
 * @def RGBA_RED
 * 32 bits mask to obtain the color component from a uint32_t RGBA color value.
 */
# define RGBA_RED 0xFF000000

/**
 * @def RGBA_GREEN
 * 32 bits mask to obtain the color component from a uint32_t RGBA color value.
 */
# define RGBA_GREEN 0x00FF0000

/**
 * @def RGBA_BLUE
 * 32 bits mask to obtain the color component from a uint32_t RGBA color value.
 */
# define RGBA_BLUE 0x0000FF00

/**
 * @def RGBA_ALPHA
 * 32 bits mask to obtain the color component from a uint32_t RGBA color value.
 */
# define RGBA_ALPHA 0x000000FF

// Forward declaration, something like a prototype for typedef.
// Needed because both fdf.h and drawing.h have structs typedefs with member
// types defined in the other file or functions refering those types..
typedef struct s_fdf	t_fdf; 

/**
 * @struct s_fdf_line
 * 
 * @brief Base for typedef <b>t_ft_mx_line</b>.
 * 
 * @details This type is used to store the parameters of a line defined as
 * f(i) = i * m + b. Where i could be X or Y and f(i) Y or X.
 * 
 * @var s_fdf_line::m
 * The slope of the line.
 * 
 * @var s_fdf_line::b
 * The f(i) value where the associated rect intersects the f(i) axis.
 * 
 * @var s_fdf_line::first_i
 * The minimum i coordinate value from where the drawing of the line
 * should start.
 * 
 * @var s_fdf_line::last_i
 * The maximum i coordinate value from where the drawing of the line
 * should stop.
 *
 * @var s_fdf_line::i_length
 * The absolute value of first_i - last_i. Used for color fading.
 * 
 * @var s_fdf_line::i_base
 * The initial i to calculate the color using each color component "slope"
 * and the start_color value.
 *
 * @var s_fdf_line::start_color
 * The index of the starting vertex color stored in the map color matrix.
 * 
 * @var s_fdf_line::end_color
 * The index of the end vertex color stored in the map color matrix.
 * 
 * @var s_fdf_line::red_m
 * The "slope" from start_color to end_color considering only this color
 * component. This is how the start value changes for each pixel from the
 * value of start_color to get to the value of the end_color.
 *
 * @var s_fdf_line::green_m
 * The "slope" from start_color to end_color considering only this color
 * component. This is how the start value changes for each pixel from the
 * value of start_color to get to the value of the end_color.
 *
 * @var s_fdf_line::blue_m
 * The "slope" from start_color to end_color considering only this color
 * component. This is how the start value changes for each pixel from the
 * value of start_color to get to the value of the end_color.
 *
 * @var s_fdf_line::alpha_m
 * The "slope" from start_color to end_color considering only this color
 * component. This is how the start value changes for each pixel from the
 * value of start_color to get to the value of the end_color.
 *
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
	double		i_length;
	double		i_base;
	uint32_t	start_color;
	uint32_t	end_color;
	double		red_m;
	double		green_m;
	double		blue_m;
	double		alpha_m;
	int			i_is_x;
}				t_fdf_line;
/**
 * @typedef t_fdf_line
 * Based on the @link s_fdf_line @endlink struct.
 */

/**
 * @brief <b>ft_draw_edges</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in] image - The image on which to draw the line.
 *
 * @param [in] object - The 3D object whose edges will be drawn.
 *
 * @param [in] drw_hidden_edges - Tells the function to draw hidden flagged
 * edges or not.
 * 
 * @param [in] drw_valid_diag_edges - Tells the function to draw valid diagonals
 * flagged edges or not.
 * 
 * @warning TODO.
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
int				fdf_drw_edges(mlx_image_t *image,
					t_fdf_object *object,
					int drw_hidden_edges,
					int drw_valid_diag_edges);

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
void			fdf_get_autofit_transf_par(uint32_t img_w,
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
int				fdf_render(t_fdf *fdf);

/**
 * @brief <b>fdf_get_color_comp</b> -- Obtains the value of a specific color
 * component from a 32 bits word with RGBA color information.
 *
 * @details TODO.
 *
 * @param [in] color - The 32 bits word with RGBA color information.
 *
 * @param [in] rgba_color_mask - The and-ing mask to obtain the 8 bits color
 * component value.
 *
 * @return The byte with the value of the required color component.
*/
unsigned char	fdf_get_color_comp(uint32_t color, int rgba_color_mask);

/**
 * @brief <b>fdf_get_color_rgba</b> -- Obtains a 32 bits word with RGBA color
 * information from the value of each color component.
 *
 * @details TODO.
 *
 * @param [in] red - The 8 bits value of this color component.
 *
 * @param [in] green - The 8 bits value of this color component.
 *
 * @param [in] blue - The 8 bits value of this color component.
 *
 * @param [in] alpha - The 8 bits value of this color component.
 *
 * @return The 32 bits word with RGBA color information collected from its
 * color components.
*/
uint32_t		fdf_get_color_rgba(unsigned char red,
					unsigned char green,
					unsigned char blue,
					unsigned char alpha);

/**
 * @brief <b>fdf_calc_line_pixel_color</b> -- Obtains the 32 bits word with
 * RGBA color corresponding to a pixel in a line.
 *
 * @details TODO.
 *
 * @param [in] line - The line struct.
 *
 * @param [in] i - The index of the pixel between the line abscissa start value
 * and end value.
 *
 * @return The 32 bits word with RGBA color information collected from its
 * color components.
*/
uint32_t		fdf_calc_line_pixel_color(t_fdf_line *line, double i);

/**
 * @brief <b>fdf_create_line</b> -- Creates a 2D line from an edge of an
 * object.
 *
 * @details TODO.
 *
 * @param [in] obj - The object struct.
 *
 * @param [in] e - The index in the array of edges.
 *
 * @return The 32 bits word with RGBA color information collected from its
 * color components.
*/
t_fdf_line		*fdf_create_line(t_fdf_object *obj, int e);

#endif
