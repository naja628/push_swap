#ifndef ALGO_H
# define ALGO_H
# include <stddef.h>
# include "t_emul.h"

/* sort the n topmost element of the stack a or b 
 * expects n to be no greater than the size of the 
 * stack a or b 
 * and a valid t_emul struct */
void	ft_merge_sort(t_emul *t, t_aorb aorb, size_t n, int opt);
//TODO typedef and unsigned
#endif
