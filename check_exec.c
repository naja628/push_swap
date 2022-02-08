/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:42:31 by najacque          #+#    #+#             */
/*   Updated: 2022/02/08 16:55:42 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
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
		write(2, "Error\n", 6);
	else if (ft_issorted(t->a))
		ft_putstr_endl("OK");
	else
		ft_putstr_endl("KO");
}
