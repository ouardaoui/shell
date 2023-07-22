# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/10 12:45:20 by mlagrini          #+#    #+#              #
#    Updated: 2023/07/22 21:39:32 by aouardao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		=	minishell_main.c builtin_commands/ms_env.c builtin_commands/ms_pwd.c \
			builtin_commands/ms_cd.c builtin_commands/ms_freenodes.c \
			builtin_commands/ms_utils.c builtin_commands/ms_export.c \
			builtin_commands/ms_unset.c builtin_commands/ms_echo.c builtin_commands/ms_exit.c \
			pipes_exec/ms_pipes.c signal_handler/ms_signals.c \
			../parse/ft_create_tree.c ../parse/linked_list.c \
			../parse/parse.c ../parse/utiles.c pipes_exec/ms_execute_utiles.c \
			pipes_exec/ms_execute_pipes.c ../parse/handle_quote.c \
			../parse/re_shap.c ../parse/redirection.c ../parse/tools.c \
			builtin_commands/ms_env_fork.c pipes_exec/ms_absolute_cmd.c
OBJ		=	${SRC:.c=.o}
NAME	=	minishell
CC		=	cc -g
FLAGS	=	-Wall -Wextra -Werror -fsanitize=address -g
RL		=	-lreadline -L /Users/mlagrini/.brew/opt/readline/lib
LIBFT	=	42_libft/libft.a
RM		=	rm -rf

all:	${NAME} ${LIBFT}

%.o:%.c
		${CC} ${FLAGS} -I /Users/mlagrini/.brew/opt/readline/include -c $< -o $@

${LIBFT}:
		make -C 42_libft

${NAME}: ${OBJ} ${LIBFT}
		${CC} ${FLAGS} ${RL} ${OBJ} ${LIBFT} -o ${NAME}
		clear

clean:
		cd 42_libft && make clean
		${RM} ${OBJ}
		
fclean:	clean
		cd 42_libft && make fclean
		${RM} ${NAME}
		clear

re:		fclean all

.PHONY:	all clean fclean re