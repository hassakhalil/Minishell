# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/23 11:34:27 by iakry             #+#    #+#              #
#    Updated: 2022/09/17 17:57:51 by hkhalil          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC	= parsing_tester.c executor.c main.c utils.c lexer.c parser.c path.c builtins.c\
					libft/ft_strnstr.c libft/ft_split.c libft/ft_strjoin.c libft/ft_strdup.c\

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