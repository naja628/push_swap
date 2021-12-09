#include "../t_emul.h"

void	ft_rrr(t_emul *t)
{
	ft_putstr_endl("rrr");
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
	if (aorb == A)
		ft_putstr_endl("pa");
	else
		ft_putstr_endl("pb");
	tmp = from->top->down;
	from->top->down = to->top;
	if (to->top == NULL)
		to->bot = from->top;
	else 
		to->top->up = from->top;
	to->top = from->top;
	from->top = tmp;
	if (from->top)
		from->top->up = NULL;
	else 
		from->bot = NULL;
}
