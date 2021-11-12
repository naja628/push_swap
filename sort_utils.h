#ifndef SORT_UTILS_H
# define SORT_UTILS_H
# include "t_emul.h"

//opt masks for ft_merge sort
# define REVO 1
# define ATBOT 2

// check for cases when we can skip an iteration of ft_merge_sort
int	ft_lucky(t_emul *t, t_aorb to, size_t n, int opt);
// like return (rev)? (x > y) : (x < y);
int			ft_less(int x, int y, int rev);
// n times px where x = to
void	ft_split(t_emul *t, t_aorb to, size_t n);
// special implementation of ft_merge_sort for n <= 3
void		ft_sort_topmost3max(t_emul *t, t_aorb aorb, size_t n, int opt);

#endif
