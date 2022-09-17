# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/23 11:34:27 by iakry             #+#    #+#              #
#    Updated: 2022/09/17 18:47:27 by hkhalil          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC	= parsing_tester.c executor.c main.c lexer.c parser.c path.c builtins.c\
					utils/libft/utils0.c utils/libft/utils1.c utils/libft/utils2.c utils/utils.c\

OBJ	= $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror


$(NAME): $(OBJ)
	$(CC)  $(CFLAGS) $(OBJ) -o $(NAME) -lreadline  -L /Users/hkhalil/.brew/opt/readline/lib -I /Users/hkhalil/.brew/opt/readline/include

all: $(NAME)

clean:
	rm -rf $(OBJ)
				
fclean:	clean
	rm -rf $(NAME)

re:	fclean all