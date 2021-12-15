/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:48:06 by najacque          #+#    #+#             */
/*   Updated: 2021/12/14 15:48:06 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGO_H
# define ALGO_H
# include <stddef.h>
# include "t_emul.h"

/* sort the n topmost element of the stack a 
 * and put them at the top or bottom (depending on (opt & ATBOT))
 * of stack 'to' (in reverse order if (opt & REVO))
 * expects n to be no greater than the size of the 
 * stack a,
 * and t to be valid (not Null etc) */
void	ft_merge_sort(t_emul *t, t_aorb aorb, size_t n, int opt);

#endif
