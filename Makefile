RED=\033[1;31m
GREEN=\033[1;32m
YELLOW=\033[1;33m
BLUE=\033[1;34m
MAGENTA=\033[1;35m
CYAN=\033[1;36m
END=\033[0m

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
NAME = pipex

MANDATORY = mandatory/main.c\
	mandatory/get_cmds.c\
	mandatory/ft_split_args.c\
	mandatory/children.c

BONUS = bonus/main_bonus.c\
	bonus/open_fds_bonus.c\
	bonus/get_cmds_bonus.c\
	bonus/ft_split_args_bonus.c\
	bonus/children_bonus.c

LIBFT = libft/libft.a

SRCS = ${addprefix ${DIR_S}/,${SOURCES}}
OBJS = ${addprefix ${DIR_O}/,${SOURCES:.c=.o}}

DIR_S = srcs
DIR_I = incs

ifdef ADD_BONUS
SOURCES = ${BONUS}
else
SOURCES = ${MANDATORY}
endif

${NAME}: ${SRCS}
	@make -s -C libft
	@echo "${BLUE}Compiling ${NAME}${END}"
	@gcc ${CFLAGS} ${SRCS} ${LIBFT} -I ${DIR_I} -o ${NAME}
	@echo "${GREEN}Done!${END}"


bonus: fclean
	@${MAKE} ADD_BONUS=1

all: ${NAME}

clean: 
	@make clean -C libft
	@echo "${RED}Removing in/outfile${END}"
	@rm -rf infile
	@rm -rf outfile
	@echo "${GREEN}Done!${END}"

fclean: clean
	@make fclean -C libft
	@echo "${RED}Removing ${NAME}${END}"
	@rm -rf ${NAME}
	@echo "${GREEN}Done!${END}"

re: fclean all

.PHONY: all clean fclean re bonus test