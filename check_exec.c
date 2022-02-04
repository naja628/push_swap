#include "check_exec.h"

void	ft_check_exec_stdin(t_emul *t)
{
	char	*line;
	int		ec;

	line = get_next_line(0);
	ec = 0;
	while (ec == 0 && line)
	{
		ft_op_ofline(t, line, &ec);
		free(line);
		line = get_next_line(0);
	}
	if (ec == -1)
		ft_putstr_endl("Error.");
	else if (ft_issorted(t->a))
		ft_putstr_endl("OK");
	else
		ft_putstr_endl("KO");
}
