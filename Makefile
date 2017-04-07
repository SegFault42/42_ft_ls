# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rabougue <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/10 19:16:51 by rabougue          #+#    #+#              #
#    Updated: 2017/04/07 19:58:14 by rabougue         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

####################################_COLOR_#####################################
GREEN = \033[38;5;10m
GREY = \033[38;5;60m
RED = \033[38;5;9m
END = \033[0m
##################################_COMPILATION_#################################
NAME = ft_ls
CC = gcc
FLAG = -Wall -Wextra -Werror
LFT = ./libft/libft.a
SRCS =	./source/lst.c\
		./source/lst1.c\
		./source/lst2.c\
		./source/lst3.c\
		./source/check.c\
		./source/directory.c\
		./source/init.c\
		./source/main.c\
		./source/parsing_argv.c\
		./source/print.c\
		./source/quit.c\
		./source/recursive.c\
		./source/sort.c\
		./source/sort_argv.c\
		./source/sort_argv_2.c\
		./source/minus_l.c\
		./source/minus_l_2.c\
		./source/padding.c\
		./source/padding_2.c\
		./source/padding_3.c\
		./source/sort_by_time.c\
		./source/print_directory.c\
		./source/print_directory_2.c\
		./source/directory_2.c\
		./source/sort_lst.c\

OBJS = $(SRCS:.c=.o)

INCLUDE = -I ./include \
		  -I ./libft
###########################_RELINK_MODIFY_.h####################################
RELINK = ./include/ft_ls.h
################################################################################

all: $(NAME)

$(NAME): $(OBJS)
	@make -s -C ./libft/
	@$(CC) $(FLAG) -o $(NAME) $(OBJS) $(LFT)
	@printf "✅  Compilation done.\n"

%.o : %.c $(RELINK) ./Makefile
	@printf " ✅                                                              \r"
	@printf "✅  $(notdir $<)\r"
	@$(CC) -c $(FLAG) $< -o $@ $(INCLUDE)

clean:
	@printf "                                                               \r"
	@printf "✅  all .o deleted\n"
	@rm -f $(OBJS)
	@make -s clean -C ./libft/

fclean:
	@printf "                                                               \r"
	@printf "✅  libft.a, all .o and rabougue.filler deleted\n"
	@rm -f $(NAME) $(OBJS)
	@make -s fclean -C ./libft/

re: fclean all

