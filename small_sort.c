/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_small_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:47:58 by najacque          #+#    #+#             */
/*   Updated: 2021/12/15 18:46:43 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort_utils.h"
#include "utils.h"

/* get the index of the maximum (min if rev)
 * of the 3 topmost vals of t */
static int	ft_imax3(t_destack *t, int rev)
{
	int	imax;

	if (ft_less(ft_nth(t, 1), ft_nth(t, 0), rev)
		&& ft_less(ft_nth(t, 2), ft_nth(t, 0), rev))
		imax = 0;
	else if (ft_less(ft_nth(t, 0), ft_nth(t, 1), rev)
		&& ft_less(ft_nth(t, 2), ft_nth(t, 1), rev))
		imax = 1;
	else
		imax = 2;
	return (imax);
}

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
void	ft_sort3orless(t_emul *t, t_aorb aorb, int rev)
{
	t_destack	*u;
	int			imax;

	u = ft_getaorb(t, aorb);
	if (ft_stacksz(u) == 2 && ft_less(ft_nth(u, 1), ft_nth(u, 0), rev))
		ft_sx(t, aorb);
	if (!(ft_stacksz(u) == 3))
		return ;
	imax = ft_imax3(u, rev);
	if (imax == 1)
		ft_rrx(t, aorb);
	if (imax == 0)
		ft_rx(t, aorb);
	if (ft_less(ft_nth(u, 1), ft_nth(u, 0), rev))
		ft_sx(t, aorb);
}

/* with n <= 2 sort the n topmost elems in a according to opt */
void	ft_a_sorttop(t_emul *t, int n, int opt)
{
	if (n == 2 && ft_less(ft_nth(t->a, 1), ft_nth(t->a, 0), opt & REVO))
		ft_sx(t, A);
	if (opt & ATBOT)
		ft_smart_rotate(t, A, n);
}

static void	ft_binsert_helper(t_emul *t, int *npushed, int *ntop, int opt)
{
	int	x;

	x = ft_nth(ft_getaorb(t, A), 0);
	if (*ntop != 0 && ft_less(ft_nth(t->b, 0), x, opt & REVO))
	{
		ft_rx(t, B);
		--(*ntop);
	}
	else if (*ntop != *npushed && ft_less(x, ft_rnth(t->b, 0), opt & REVO))
	{
		ft_rrx(t, B);
		++(*ntop);
	}
	else
	{
		ft_px(t, B);
		++(*npushed);
		++(*ntop);
	}
}

// TODO norminette num of line pb...
/* take n elems from a and sort them into b according to opt */
void	ft_binsert_sort(t_emul *t, int n, int opt)
{
	int	ntop;
	int	npushed;

	npushed = 0;
	ntop = 0;
	while (n > npushed)
		ft_binsert_helper(t, &npushed, &ntop, opt);
	if (opt & ATBOT)
		ft_smart_rotate(t, B, ntop);
	else
		ft_smart_rotate(t, B, ntop - n);
}
