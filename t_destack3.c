#include <stdlib.h>
#include "t_destack.h"

/* return the val of the nth elem 
 * of t 
 * 0 if does not exist 
 * maybe todo : explicit way to tell 
 * "does not exist" */
int	ft_nth(t_destack *t, size_t n)
{
	t_node	*it;

	if (!t || ! t->top)
		return (0);
	it = t->top;
	while (it && n)
	{
		it = it->down;
		--n;
	}
	if (!it)
		return (0);
	else 
		return (it->x);
}

/* return 1 if t contains at least n elems
 * 0 otherwise 
 *
 * if n is 0 but t is NULL return 0 
 * (as t is then not a valid stack)
 * but return 1 if t->top is NULL */
int	ft_atleast_n(t_destack *t, size_t n)
{
	t_node	*it;

	if (!t)
		return (0);
	it = t->top;
	while (it && n)
	{
		it = it->down;
		--n;
	}
	if (n == 0)
		return (1);
	else 
		return (0);
}

