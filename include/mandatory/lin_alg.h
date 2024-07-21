/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lin_alg.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:55:20 by lluque            #+#    #+#             */
/*   Updated: 2024/07/21 14:51:31 by lluque           ###   ########.fr       */
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

/**
 * @def VAL_SEPARATOR_FILE
 * ASCII value for the expected char separator between column values on
 * source altitude map file.
 */
# define VAL_SEPARATOR_FILE 32

/**
 * @def Z
 * Mnemonic to refer to the Z values matrix in the array of pointers to matrices
 * that represent both Z values and color values for each vertex.
 */
#define Z 0

/**
 * @def C
 * Mnemonic to refer to the color values matrix in the array of pointers to
 * matrices that represent both Z values and color values for each vertex.
 */
#define C 1

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
 * @typedef t_ft_mx
 * Based on the @link s_ft_mx @endlink struct.
 */

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
 * @typedef t_ft_mx_size
 * Based on the @link s_ft_mx_size @endlink struct.
 */

/**
 * @brief <b>ft_mx_create</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in] m - Number of rows.
 *
 * @param [in] n - Number of columns.
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
 * @param [in] matrix - TODO.
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
 * @param [in] matrix - TODO.
 *
 * @param [in] value - TODO.
 *
 * @param [in] i - The row (from 0 to matrix->m) of the element.
 *
 * @param [in] j - The column (from 0 to matrix->n) of the element.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
void	ft_mx_set_element(t_ft_mx *matrix, double value, int i, int j);

/**
 * @brief <b>ft_mx_get_element</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in] matrix - TODO.
 *
 * @param [in] i - The row (from 0 to matrix->m) of the element.
 *
 * @param [in] j - The column (from 0 to matrix->n) of the element.
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
 * @param [in] matrix - TODO.
 *
 * @param [in] i - The row number (from 0 to matrix->m) to be replaced in the
 * matrix.
 *
 * @param [in] row - The row-vector (1 x n matrix) to be copied in the matrix.
 * The row-vector must have the same number of columns as the target matrix.
 *
 * @return Non-zero value if correct.
 * A value of zero if error.
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
 * @param [in] matrix - TODO.
 *
 * @param [in] j - The column number (from 0 to matrix->m) to be replaced in the
 * matrix.
 *
 * @param [in] col - The col-vector (m x 1 matrix) to be copied in the matrix.
 * The col-vector must have the same number of rows as the target matrix.
 *
 * @return Non-zero value if correct.
 * A value of zero if error.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
int		ft_mx_set_col(t_ft_mx *matrix, int j, t_ft_mx *col);

/**
 * @brief <b>ft_mx_get_row</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in] matrix - TODO.
 *
 * @param [in] i - The row number (from 0 to matrix->m) to be returned.
 *
 * @return A row-vector (1 x n matrix).
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
 * @param [in] matrix - TODO.
 *
 * @param [in] j - The column number (from 0 to matrix->n) to be returned.
 *
 * @return A column-vector (m x 1 matrix).
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
 * @param [in] matrix - The matrix to be printed.
 *
 * @param [in] separator - The character to be printed between column values.
 *
 * @warning Uses stdio's printf for printing double type variables.
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
 * @param [in] filename - The relative path and name of the plain-text file to
 * read the matrix values from. The formating accepted is: each row on a single
 * line; each column value can be separated with any number of seapartor
 * character.
 *
 * @param [in] separator - The character to be printed between column values.
 *
 * @return A pointer to an array of two pointers to matrix that represent both
 * Z values and color values for the vertices of the map.
 * NULL if error.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
t_ft_mx	**ft_mx_load_file(char *filename, char separator);

/**
 * @brief <b>ft_mx_dup</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in] src - The matrix to be duplicated.
 *
 * @return TODO..
 * NULL if error.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
t_ft_mx	*ft_mx_dup(t_ft_mx *src);

/**
 * @brief <b>ft_mx_smult</b> -- Scalar multiplication.
 *
 * @details TODO.
 *
 * @param [in, out] matrix - TODO.
 *
 * @param [in] scalar - TODO.
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
 * @param [in] m1 - TODO.
 *
 * @param [in] m2 - TODO.
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
 * @brief <b>ft_mx_mult3</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in] m1 - TODO.
 *
 * @param [in] m2 - TODO.
 *
 * @param [in] m3 - TODO.
 *
 * @return TODO..
 * NULL if error.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
t_ft_mx	*ft_mx_mult3(t_ft_mx *m1, t_ft_mx *m2, t_ft_mx *m3);

/**
 * @brief <b>ft_mx_create_id</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in] size - TODO.
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
 * @param [in] size - TODO.
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
 * @param [in] m - The matrix to be transposed.
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
 * @brief <b>ft_mx_flipr</b> -- Flip along the row axis (y axis).
 *
 * @details TODO.
 *
 * @param [in] m - The matrix to be flipped.
 *
 * @return TODO..
 * NULL if error.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * The result of post-multiplying a backward-identity matrix to the matrix to 
 * be flipped.
*/
int		ft_mx_flipr(t_ft_mx *m);

/**
 * @brief <b>ft_mx_flipc</b> -- Flip along the column axis (x axis).
 *
 * @details TODO.
 *
 * @param [in] m - The matrix to be flipped.
 *
 * @return TODO..
 * NULL if error.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * The result of pre-multiplying a backward-identity matrix to the matrix to 
 * be flipped.
*/
int		ft_mx_flipc(t_ft_mx *m);

/**
 * @brief <b>ft_vx_create</b> -- Creates a xyzw vertex as a column vector
 * matrix.
 *
 * @details Takes 4 double type values corresponding to a xyzw vertex to create
 * and initialize a column vector matrix.
 *
 * @param [in] x - The X coordinate value.
 *
 * @param [in] y - The Y coordinate value.
 *
 * @param [in] z - The Z coordinate value.
 *
 * @param [in] w - The W value.
 *
 * @return TODO..
 * NULL if error.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
t_ft_mx	*ft_vx_create(double x, double y, double z, double w);

/**
 * @brief <b>ft_vx_xproduct</b> -- Calculates the cross product of two xyzw
 * vertexes passed as column vector matrixes.
 *
 * @details Takes two matrixes which must be  column vectors with 4 rows
 * (to allow for xyzw vertexes calculations) and returns the result of their
 * cross product as a new column vector of 4 rows.
 *
 * @param [in] b - A column vector matrix representing a xyzw vertex.
 *
 * @param [in] c - A column vector matrix representing a xyzw vertex.
 *
 * @return TODO..
 * NULL if error.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
t_ft_mx	*ft_vx_xproduct(t_ft_mx *b, t_ft_mx *c);

/**
 * @brief <b>ft_vx_substract</b> -- Calculates the substraction of two xyzw
 * vertexes passed as column vector matrixes.
 *
 * @details Takes two matrixes which must be  column vectors with 4 rows
 * (to allow for xyzw vertexes calculations) and returns the result of their
 * substraction (b - c).
 *
 * @param [in] b - A column vector matrix representing a xyzw vertex.
 *
 * @param [in] c - A column vector matrix representing a xyzw vertex.
 *
 * @return b - c. TODO..
 * NULL if error.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
t_ft_mx	*ft_vx_substract(t_ft_mx *b, t_ft_mx *c);

/**
 * @brief <b>ft_vx_dproduct</b> -- Calculates the dot product of two vectors.
 *
 * @details Takes two vectors as any combination of row/col vectors in the
 * t_ft_mx matrix (the only requisite is that both must have the same number
 * of elements) and calculates the dot product returning a scalar.
 *
 * @param [in] a - A column/row vector matrix.
 *
 * @param [in] b - A column/row vector matrix.
 *
 * @param [out] result - A pointer to a double where the result value will
 * be output. If the function returns 0 the value of *result is invalid.
 *
 * @return Non-zero value if the arguments are consistent with the operation,
 * zero otherwise.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * This function exploits the linear storage of values inside a matrix, making
 * irrelevant if we're dealing with row-vectors or col-vectors. Once checked
 * that both matrixes are vectors (1xn, mx1, doesn't matter), and of the same
 * size (the other non 1 size is the same); and since every element is linearly
 * storaged inside the matrix's ->d[] array, the addressing is very simple.
*/
int		ft_vx_dproduct(t_ft_mx *a, t_ft_mx *b, double *result);

/**
 * @brief <b>ft_mx_fill</b> -- Sets every element in the matrix to a value.
 *
 * @details Sets every element in the matrix to a value.
 *
 * @param [in] matrix - The matrix pointer to modify.
 *
 * @param [in] element_value - The new value to apply to every element
 * in the matrix.
*/
void	ft_mx_fill(t_ft_mx *matrix, double element_value);

#endif
