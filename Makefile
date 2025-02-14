CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRCS = pipex.c check_input.c find_cmd.c ft_split.c help.c utils.c utils_2.c 

OBJS = ${SRCS:.c=.o}

NAME = pipex

.c.o:
	${CC} -g ${CFLAGS} -c $< -o $@

all: ${NAME}

${NAME}: ${OBJS}
	${CC} -o $@ $^

clean:
	${RM} ${OBJS} ${O_BONUS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all fclean re clean