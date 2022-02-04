GNL_DIR=get_next_line
COMMON_SRC= ft_atoi_errcode.c t_destack1.c \
			t_destack2.c t_destack3.c utils.c \
			ft_strsplit.c
PS_SRC=sort_utils.c push_swap.c algo.c small_sort.c verbose_emul/t_emul1.c \
	   verbose_emul/t_emul2.c verbose_emul/t_emul3.c verbose_emul/t_emul4.c
CHECKER_SRC=checker.c  silent_emul/t_emul1.c silent_emul/t_emul2.c \
			silent_emul/t_emul3.c silent_emul/t_emul4.c \
			${addprefix ${GNL_DIR}/, get_next_line.c get_next_line_utils.c}
COMMON_OBJ=${COMMON_SRC:.c=.o}
PS_OBJ=${PS_SRC:.c=.o}
CHECKER_OBJ=${CHECKER_SRC:.c=.o}
CFLAGS=-Wall -Wextra -Werror -I${GNL_DIR}
CC=gcc
NAME=push_swap
CHECKER_NAME=checker

all: ${NAME} $(CHECKER_NAME) 
	@#empty

${NAME}: ${COMMON_OBJ} ${PS_OBJ} 
	${CC} ${CLAGS} -o $@ $^

${CHECKER_NAME}: ${COMMON_OBJ} ${CHECKER_OBJ}
	${CC} ${CLAGS} -o ${CHECKER_NAME} $^

bonus: ${CHECKER_NAME}
	@#empty

clean: 
	rm -rf ${COMMON_OBJ} ${PS_OBJ} ${CHECKER_OBJ}	

fclean: clean
	rm -f ${CHECKER_NAME} ${NAME}

re: fclean all
	@#empty

.PHONY: all re fclean clean bonus all
