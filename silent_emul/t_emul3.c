#include "../t_emul.h"

void	ft_rrr(t_emul *t)
{
	ft_rrotate(t->a);
	ft_rrotate(t->b);
}

t_aorb	ft_other(t_aorb aorb)
{
	return (!aorb);
}

t_destack	*ft_getaorb(t_emul *t, t_aorb aorb)
{
	if (aorb == B)
		return (t->b);
	else 
		return (t->a);
}

void	ft_sx(t_emul *t, t_aorb aorb)
{
	if (aorb == A)
		ft_sa(t);
	else
		ft_sb(t);
}

/* malloc less implementation 
 * so malloc errors cannot happen 
 * once everything has been init'ed properly */
void	ft_px(t_emul *t, t_aorb aorb)
{
	t_node		*tmp;
	t_destack	*from;
	t_destack	*to;

	from = ft_getaorb(t, !aorb);
	to = ft_getaorb(t, aorb);
	if (!from || !from->top)
		return ;
	tmp = from->top->down;
	from->top->down = to->top;
	if (to == NULL)
		to->bot = from->top;
	else 
		to->top->up = from->top;
	to->top = from->top;
	from->top = tmp;
	tmp->up = NULL;	
}
