# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/23 11:34:27 by iakry             #+#    #+#              #
#    Updated: 2022/10/03 19:53:26 by hkhalil          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC	=  env.c builtin.c clean.c parsing_tester.c quote_remover.c expander.c executor.c main.c lexer.c parser.c path.c\
	utils/libft/utils0.c utils/libft/utils1.c utils/libft/utils2.c utils/libft/utils3.c utils/libft/utils4.c utils/utils.c \

OBJ	= $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g


$(NAME): $(OBJ)
	$(CC)  $(CFLAGS) $(OBJ) -o $(NAME) -lreadline  -L /Users/hkhalil/.brew/opt/readline/lib -I /Users/hkhalil/.brew/opt/readline/include

all: $(NAME)

clean:
	rm -rf $(OBJ)
				
fclean:	clean
	rm -rf $(NAME)

re:	fclean all
