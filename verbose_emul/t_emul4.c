#include "../t_emul.h"

void	ft_rx(t_emul *t, t_aorb aorb)
{
	if (aorb == A)
		ft_ra(t);
	else
		ft_rb(t);
}

void	ft_rrx(t_emul *t, t_aorb aorb)
{
	if (aorb == A)
		ft_rra(t);
	else
		ft_rrb(t);
}

t_emul	ft_mk_emul(t_destack *a, t_destack *b)
{
	t_emul	t;

	t.a = a;
	t.b = b;
	return (t);
}
