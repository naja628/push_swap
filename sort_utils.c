/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:48:01 by najacque          #+#    #+#             */
/*   Updated: 2021/12/15 18:05:40 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort_utils.h"
#include "t_emul.h"

int	ft_lucky(t_emul *t, t_aorb to, size_t n, int opt)
{
	t_node	*it;
	t_node	*down;

	if (to == B)
		return (0);
	it = ft_getaorb(t, A)->top;
	if (opt & ATBOT)
		it = ft_getaorb(t, A)->bot;
	while (n > 1)
	{
		if (opt & ATBOT)
			it = it->up;
		down = it->down;
		if (ft_less(down->x, it->x, (opt & REVO)))
			return (0);
		--n;
		if (!(opt & ATBOT))
			it = it->down;
	}
	return (1);
}

int	ft_less(int x, int y, int rev)
{
	if (rev)
		return (x > y);
	else
		return (x < y);
}

/* note : just the else part of the first if would suffice
 * (correctness wise)
 * but checking if the stack is small allows us to
 * not temper with the time complexity of the whole algorithm...
 *
 * another solution would be to keep track of the size of the stacks
 *
 * note : no var for stacksz(u) for dumb norminette reasons
 * (num of lines)
 */
void	ft_smart_rotate(t_emul *t, t_aorb aorb, int shift)
{
	int			rshift;
	t_destack	*u;

	u = ft_getaorb(t, aorb);
	if (ft_atleast_n(u, 2 * ft_abs(shift)))
		rshift = -shift;
	else
	{
		shift %= (int) ft_stacksz(u);
		if (shift <= 0)
			shift += ft_stacksz(u);
		rshift = ft_stacksz(u) - shift;
	}
	if (rshift < 0 || (shift <= rshift && shift >= 0))
	{
		while (--shift + 1)
			ft_rx(t, aorb);
	}
	else
	{
		while (--rshift + 1)
			ft_rrx(t, aorb);
	}
}
