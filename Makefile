# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rabougue <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/10 19:16:51 by rabougue          #+#    #+#              #
#    Updated: 2017/02/12 05:52:02 by rabougue         ###   ########.fr        #
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
SRCS = ./sources/main.c

OBJS = $(SRCS:.c=.o)

###########################_RELINK_MODIFY_.h####################################
INCLUDE = ./include/ft_ls.h
################################################################################

all: $(NAME)

$(NAME): $(OBJS)
	@make -s -C ./libft/
	@$(CC) $(FLAG) $(LFT) $(OBJS) -o $(NAME)
	@printf "✅  Compilation done.\n"

%.o : %.c $(INCLUDE) ./Makefile
	@printf "                                                               \r"
	@printf "✅  $(notdir $<)\r"
	@$(CC) -c $(FLAG) $< -o $@

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

