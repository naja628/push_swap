#ifndef T_DESTACK_H
# define T_DESTACK_H
# include <stddef.h>

/* implementation of an (int) stack as a double-ended queue
 * (to allow for O(1) rotations) */
typedef struct s_node
{
	int					x;
	struct s_node	*down;
	struct s_node	*up;
}	t_node;

typedef struct
{
	t_node	*bot;
	t_node	*top;
}	t_destack;

/* returns an empty stack 
 * no allocation is performed */
t_destack	ft_newstack(void);

/* push x onto t 
 * return 0 if ok 
 * -1 if malloc error */
int			ft_push(t_destack *t, int x);

/* swap the 2 topmost elems of t
 * return -1 if t contains less than 2 elems 
 * (0 if successful) */
int			ft_swap(t_destack *t);

/* rotate stack (top goes to bottom) */
void		ft_rotate(t_destack *t);

/* rotate stack (bot goes to top) */
void		ft_rrotate(t_destack *t);

/* remove the topmost node of a stack and return its value 
 * if empty return 0
 * (maybe fix : no way to tell if top was 0 or empty) */
int			ft_pop(t_destack *t);

/* clear t (dealloc everything) 
 * set both top and bot to NULL */
void		ft_clear(t_destack *t);

/* return 1 if t is sorted (smallest on top)
 * 0 otherwise */
int			ft_issorted(t_destack *t);

/* return the number of elems in t
 *
 * note : techincally the return type has no 
 * reason to be size_t rather than any other 
 * unsigned int type but semantically it makes 
 * sense so... 
 * (note this is true throughout the codebase) */
size_t		ft_stacksz(t_destack *t);

/* return 1 if the topmost n elems of t are sorted
 * 0 otherwise */
int			ft_nfstsorted(t_destack *t, size_t n);

/* return the val of the nth elem 
 * of t 
 * 0 if does not exist 
 * maybe todo : explicit way to tell 
 * "does not exist"
 * rnth starts at the bottom */
int			ft_nth(t_destack *t, size_t n);
int			ft_rnth(t_destack *t, size_t n);

/* return 1 if t contains at least n elems
 * 0 otherwise 
 *
 * if n is 0 but t is NULL return 0 
 * (as t is then not a valid stack)
 * but return 1 if t->top is NULL */
int			ft_atleast_n(t_destack *t, size_t n);

#endif
