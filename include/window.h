/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:55:20 by lluque            #+#    #+#             */
/*   Updated: 2024/03/02 15:11:24 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file window.h
 * TODO.
 * Header file for linearly-storaged matrixes (row-major order) operations.
 * Syntaxis will follow mathematics standard:
 *
 *     i: row index, starts at 0 (NOT 1)
 *     j: col index, starts at 0 (NOT 1)
 *     m: number of rows
 *     n: number of cols
 *     Aij: Element in row i col j. NOTICE that row index comes first...
 *             A00 A02 A03
 *             A10 A11 A12
 *             A20 A21 A22
 *
 * The element addressing of an intuitive C-style matrix (array of arrays,
 * e.g. **double or double[][]) translates to, in a more efficient linear
 * storage data model (one array, e.g. *int or int[]), this addressing:
 *
 *     Given a mxn matrix, the element Aij is addressed in this way...
 *     
 *     Intuitive C-style matrix    Linear storage (row-major order)
 *
 *          double **data;                   double *data;
 *
 *            data[i][j] >>>>>>>>>>>>>>>>>> data[i * m + j]
 *
 * NOTE: Row-major order (aka lexicographic order) means that elements of the
 * same ROW are stored in contiguous memory addresses.
 * The alternative is column-major order (aka colexicographic order). 
*/

#ifndef WINDOW_H
# define WINDOW_H
# include "MLX42.h"
# include "tesselator.h"

/**
 * @struct s_ft_mx
 * @brief Base for typedef <b>t_ft_mx</b>.
 * @details This type is used to store a linearly-storaged (row-major order)
 * matrix of double type elements.
 * @var s_ft_mx::d
 * The elements, stored linearly using a row-major order. Element addressing
 * follows this syntax: data[i * n + j] (where i represents the row, m the
 * number of rows and j the column).
 * @var s_ft_mx::m
 * Number of rows as a positive integer value.
 * @var s_ft_mx::n
 * Number of columns as a positive integer value.
 * @var s_ft_mx::is_sqr
 * Non-zero value to quickly check if this matrix is square (m == n).
*/
/*
typedef struct s_ft_mx
{
	double	*d;
	int		m;
	int		n;
	int		is_sqr;
}				t_ft_mx;
*/

/**
 * @brief <b>fdf_keyhook</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in] c - TODO.
 *
 * @return TODO..
 * NULL if error.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
void	fdf_keyhook(mlx_key_data_t keydata, void *param);

/**
 * @brief <b>fdf_closehook</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in] c - TODO.
 *
 * @return TODO..
 * NULL if error.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
void	fdf_closehook(void *param);

/**
 * @brief <b>fdf_resizehook</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in] c - TODO.
 *
 * @return TODO..
 * NULL if error.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
void	fdf_resizehook(int32_t width, int32_t height, void *param);

/**
 * @brief <b>fdf_start_gui</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in, out] model - TODO.
 *
 * @return Non-zero value if correct.
 * A value of 0 is returned if error.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
int		fdf_start_gui(t_fdf_model *model);

#endif
