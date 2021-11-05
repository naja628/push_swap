#include "algo.h"
#include "t_destack.h"
#include "t_emul.h"
#include "utils.h"



//TODO check no duplicate values
//TODO validate input


int main(int ac, char **av)
{
	t_emul		t;
	t_destack	a;
	t_destack	b;
	
	a = ft_newstack();
	b = ft_newstack();
	while (ac != 1)
		ft_push(&a, ft_atoi(av[--ac]));
	t = ft_mk_emul(&a, &b);
	ft_merge_sort(&t, A, ft_stacksz(&a), 0);
	ft_clear(t.a);
	ft_clear(t.b);
	return (0);
}


