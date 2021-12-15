/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:48:06 by najacque          #+#    #+#             */
/*   Updated: 2021/12/14 15:48:06 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORT_UTILS_H
# define SORT_UTILS_H
# include "t_emul.h"

//opt masks for ft_merge sort
# define REVO 1
# define ATBOT 2

// check for cases when we can skip an iteration of ft_merge_sort
int		ft_lucky(t_emul *t, t_aorb to, size_t n, int opt);
// like return (rev)? (x > y) : (x < y);
int		ft_less(int x, int y, int rev);
/* sort the stack a or b when sz <= 3 
 * if rev == 1 sort in reverse order
 * note : ad hoc, non-general implementation
 * when sz = 3, this function implements the following table :
 * 1 2 3 : /
 * 1 3 2 : rrx sx
 * 2 1 3 : sx
 * 2 3 1 : rrx
 * 3 1 2 : rx
 * 3 2 1 : rx sx */
void	ft_sort3orless(t_emul *t, t_aorb aorb, int rev);
/* with n <= 2 sort the n topmost elems in a according to opt */
void	ft_a_sorttop(t_emul *t, int n, int opt);
/* take n elems from a and sort them into b according to opt */
void	ft_binsert_sort(t_emul *t, int n, int opt);

#endif
