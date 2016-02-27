# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rabougue <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/10 19:16:51 by rabougue          #+#    #+#              #
#    Updated: 2016/01/25 14:48:42 by rabougue         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_DIR = libft

FLAG = -Wall -Wextra -Werror

NAME = ft_ls

SRC = main.c

COMPIL_LIB = make

OBJS = $(SRC:.c=.o)

HEAD = ./libft/libft.a

all: $(NAME)

$(NAME):
	@echo "\033[33mCompiling libft.a ...]\033[0m"
	@-make -C ./libft/
	@echo "\033[36mCompiling libft.a done !\033[0m"
	@echo "\033[33mCompiling in .o ...\033[0m"
	@gcc -c $(SRC)
	@echo "\033[36mCompiling in .o done !\033[0m"
	@gcc $(SRC) $(HEAD) -o $(NAME)
	@echo "\033[33mCompiling ft_ls ...\033[0m"
	@echo "\033[36mCompiling ft_ls done !\033[0m"

mc: fclean all clean

clean:
	@echo "\033[31mdeleting all .o ...\033[0m"
	@rm -f $(OBJS)
	@echo "\033[32mThe folder is clean !\033[0m"

fclean:
	@echo "\033[31mDeleting libft.a and all .o ...\033[0m"
	@rm -f $(NAME) $(OBJS)
	@echo "\033[32mThe folder is clean\033[0m"
	@make fclean -C ./libft/

re: fclean all
