/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_destack1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:48:02 by najacque          #+#    #+#             */
/*   Updated: 2021/12/15 18:06:17 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "t_destack.h"

/* convention the 'canonical' stack we operate on is gonna be
 * called t in most functions */

/* returns an empty stack
 * no allocation is performed */
t_destack	ft_newstack(void)
{
	t_destack	t;

	t.top = NULL;
	t.bot = NULL;
	return (t);
}

/* push x onto t
 * return 0 if ok
 * -1 if malloc error */
int	ft_push(t_destack *t, int x)
{
	t_node	*new_node;

	if (!t)
		return (-1);
	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (-1);
	new_node->x = x;
	new_node->down = t->top;
	new_node->up = NULL;
	t->top = new_node;
	if (t->bot == NULL)
		t->bot = new_node;
	else
		t->top->down->up = new_node;
	return (0);
}

/* swap the 2 topmost elems of t
 * return -1 if t contains less than 2 elems
 * (0 if successful) */
int	ft_swap(t_destack *t)
{
	int	store;

	if (!t || !t->top || !t->top->down)
		return (-1);
	store = t->top->x;
	t->top->x = t->top->down->x;
	t->top->down->x = store;
	return (0);
}

/* rotate stack (top goes to bottom) */
void	ft_rotate(t_destack *t)
{
	if (!t || !t->top || !t->top->down)
		return ;
	t->bot->down = t->top;
	t->top->up = t->bot;
	t->bot = t->bot->down;
	t->top = t->top->down;
	t->bot->down = NULL;
	t->top->up = NULL;
}

/* rotate stack (bot goes to top) */
void	ft_rrotate(t_destack *t)
{
	if (!t || !t->bot || !t->bot->up)
		return ;
	t->bot->down = t->top;
	t->top->up = t->bot;
	t->top = t->top->up;
	t->bot = t->bot->up;
	t->bot->down = NULL;
	t->top->up = NULL;
}
