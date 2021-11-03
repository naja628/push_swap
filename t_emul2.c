#include "t_emul.h"
#include "t_destack.h"
#include "utils.h"

void	ft_ra(t_emul *t)
{
	ft_putstr_endl("ra");
	ft_rotate(t->a);
}

void	ft_rb(t_emul *t)
{
	ft_putstr_endl("rb");
	ft_rotate(t->b);
}

void	ft_rr(t_emul *t)
{
	ft_putstr_endl("rr");
	ft_rotate(t->a);
	ft_rotate(t->b);
}

void	ft_rra(t_emul *t)
{
	ft_putstr_endl("rra");
	ft_rrotate(t->a);
}

void	ft_rrb(t_emul *t)
{
	ft_putstr_endl("rrb");
	ft_rrotate(t->b);
}
