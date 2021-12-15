/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_destack2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:48:03 by najacque          #+#    #+#             */
/*   Updated: 2021/12/15 18:07:32 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "t_destack.h"

/* remove the topmost node of a stack and return its value
 * if empty return 0
 * (maybe fix : no way to tell if top was 0 or empty) */
int	ft_pop(t_destack *t)
{
	t_node	*store;
	int		x;

	if (!t->top)
		return (0);
	store = t->top->down;
	x = t->top->x;
	free(t->top);
	t->top = store;
	if (t->top)
		t->top->up = NULL;
	else
		t->bot = NULL;
	return (x);
}

/* clear t (dealloc everything)
 * set both top and bot to NULL */
void	ft_clear(t_destack *t)
{
	while (t->top)
		ft_pop(t);
	t->bot = NULL;
}

/* return 1 if t is sorted (smallest on top)
 * 0 otherwise */
int	ft_issorted(t_destack *t)
{
	t_node	*it;

	if (!t->top)
		return (1);
	it = t->top;
	while (it->down)
	{
		if (it->x > it->down->x)
			return (0);
		it = it->down;
	}
	return (1);
}

/* return 1 if the topmost n elems of t are sorted
 * 0 otherwise */
int	ft_nfstsorted(t_destack *t, size_t n)
{
	t_node	*it;

	if (!t->top)
		return (1);
	it = t->top;
	while (it->down && n > 1)
	{
		if (it->x > it->down->x)
			return (0);
		it = it->down;
		--n;
	}
	return (1);
}

/* return the number of elems in t
 *
 * note : techincally the return type has no
 * reason to be size_t rather than any other
 * unsigned int type but semantically it makes
 * sense so... */
size_t	ft_stacksz(t_destack *t)
{
	size_t	count;
	t_node	*it;

	count = 0;
	it = t->top;
	while (it)
	{
		++count;
		it = it->down;
	}
	return (count);
}
