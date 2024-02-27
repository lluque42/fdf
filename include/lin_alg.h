/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lin_alg.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:55:20 by lluque            #+#    #+#             */
/*   Updated: 2024/02/27 20:28:24 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file lin_alg.h
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

#ifndef LIN_ALG_H
# define LIN_ALG_H
# include "libft.h"
# define VAL_SEPARATOR_FILE 32

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
typedef struct s_ft_mx
{
	double	*d;
	int		m;
	int		n;
	int		is_sqr;
}				t_ft_mx;

/**
 * @struct s_ft_mx_size
 * @brief Base for typedef <b>t_ft_mx_size</b>.
 * @details This type is used to store a size (int x int).
 * @var s_ft_mx_size::m
 * Number of rows as a positive integer value.
 * @var s_ft_mx_size::n
 * Number of columns as a positive integer value.
*/
typedef struct s_ft_mx_size
{
	int		m;
	int		n;
}				t_ft_mx_size;

/**
 * @brief <b>ft_mx_create</b> -- TODO.
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
t_ft_mx	*ft_mx_create(int m, int n);

/**
 * @brief <b>ft_mx_destroy</b> -- TODO.
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
void	ft_mx_destroy(t_ft_mx *matrix);

/**
 * @brief <b>ft_mx_set_element</b> -- TODO.
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
void	ft_mx_set_element(t_ft_mx *matrix, double element, int i, int j);

/**
 * @brief <b>ft_mx_get_element</b> -- TODO.
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
double	ft_mx_get_element(t_ft_mx *matrix, int i, int j);

/**
 * @brief <b>ft_mx_set_row</b> -- TODO.
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
int		ft_mx_set_row(t_ft_mx *matrix, int i, t_ft_mx *row);

/**
 * @brief <b>ft_mx_set_col</b> -- TODO.
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
void	ft_mx_set_col(t_ft_mx *matrix, t_ft_mx *col);

/**
 * @brief <b>ft_mx_get_row</b> -- TODO.
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
t_ft_mx	*ft_mx_get_row(t_ft_mx *matrix, int i);

/**
 * @brief <b>ft_mx_get_col</b> -- TODO.
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
t_ft_mx	*ft_mx_get_col(t_ft_mx *matrix, int j);

/**
 * @brief <b>ft_mx_print</b> -- TODO.
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
void	ft_mx_print(t_ft_mx *matrix, char separator);

/**
 * @brief <b>ft_mx_load_file</b> -- TODO.
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
t_ft_mx	*ft_mx_load_file(char *filename, char separator);

/**
 * @brief <b>ft_mx_dup</b> -- TODO.
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
t_ft_mx	*ft_mx_dup(t_ft_mx *old);

/**
 * @brief <b>ft_mx_smult</b> -- TODO.
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
void	ft_mx_smult(t_ft_mx *matrix, double scalar);

/**
 * @brief <b>ft_mx_mult</b> -- TODO.
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
t_ft_mx	*ft_mx_mult(t_ft_mx *m1, t_ft_mx *m2);

/**
 * @brief <b>ft_mx_create_id</b> -- TODO.
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
t_ft_mx	*ft_mx_create_id(int size);

/**
 * @brief <b>ft_mx_create_bid</b> -- TODO backward.
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
t_ft_mx	*ft_mx_create_bid(int size);

/**
 * @brief <b>ft_mx_transpose</b> -- TODO.
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
t_ft_mx	*ft_mx_transpose(t_ft_mx *m);

/**
 * @brief <b>ft_mx_flipr</b> -- TODO Flip along the row axis (y axis).
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
t_ft_mx	*ft_mx_flipr(t_ft_mx *m);

#endif
