#include "../t_emul.h"

void	ft_ra(t_emul *t)
{
	ft_rotate(t->a);
}

void	ft_rb(t_emul *t)
{
	ft_rotate(t->b);
}

void	ft_rr(t_emul *t)
{
	ft_rotate(t->a);
	ft_rotate(t->b);
}

void	ft_rra(t_emul *t)
{
	ft_rrotate(t->a);
}

void	ft_rrb(t_emul *t)
{
	ft_rrotate(t->b);
}
