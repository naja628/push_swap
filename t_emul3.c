#include "t_emul.h"
#include "t_destack.h"
#include "utils.h"

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

void	ft_px(t_emul *t, t_aorb aorb)
{
	if	(aorb == A)
		ft_pa(t);
	else
		ft_pb(t);
}
