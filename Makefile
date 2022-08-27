# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/23 11:34:27 by iakry             #+#    #+#              #
#    Updated: 2022/08/27 02:59:31 by hkhalil          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

MINISHELL_SRCS	= parsing_tester.c executor.c main.c utils.c lexer.c parser.c path.c builtins.c\
					libft/ft_strnstr.c libft/ft_split.c libft/ft_strjoin.c libft/ft_strdup.c\

MINISHELL_OBJS	= $(MINISHELL_SRCS:.c=.o)

FLAGS			= -lreadline


all:			$(NAME)

$(NAME):		$(MINISHELL_SRCS)
				gcc  $(FLAGS) $(MINISHELL_SRCS) -o $(NAME)

clean:
				rm -f $(MINISHELL_OBJS)
				
fclean:			clean
				rm -f $(NAME)

re:				fclean $(NAME)