# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/23 11:34:27 by iakry             #+#    #+#              #
#    Updated: 2022/08/23 01:06:56 by hkhalil          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

MINISHELL_SRCS	= executor.c main.c utils.c  lexer.c parser.c tokenizer.c path.c execution.c builtins.c\
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