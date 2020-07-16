# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/09 16:02:37 by avan-pra          #+#    #+#              #
#    Updated: 2019/10/10 13:39:50 by avan-pra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

SRC				=	./srcs/exec_prog.c\
					./srcs/main.c\
					./srcs/sign_handle.c\
					./srcs/prompt.c\
					./srcs/check_quote.c\
					./srcs/reader/inter_line.c\
					./srcs/reader/read_utils.c\
					./srcs/reader/special_event1.c\
					./srcs/reader/special_event2.c\
					./srcs/spliter/split_r_in_out1_part1.c\
					./srcs/spliter/split_r_in_out1_part2.c\
					./srcs/spliter/split_r_in_out2.c\
					./srcs/spliter/split_pipe.c\
					./srcs/spliter/split_semi_colon.c\
					./srcs/builtin/builtin.c\
					./srcs/environement/handle_env.c\
					./srcs/environement/new_env.c\
					./srcs/environement/del_env.c\
					./srcs/spliter2/doll.c\
					./srcs/spliter2/doll_utils.c\
					./srcs/spliter2/enhanced_split.c\
					./srcs/spliter2/advance.c\
					./srcs/spliter2/count_split.c\
					./srcs/spliter2/count_words.c\
					./srcs/spliter2/fill_word.c\

ROAD_S			= $(SRC)

ROAD_O			= $(OBJ)

ROAD_B			= $(SRCB)

FLAGS			= -Wall -Wextra -Werror #-g3 -fsanitize=address

OBJ				= $(SRC:.c=.o)

CC				= clang

HEADER_DIR		= -I./head/get_next_line.h -I./head/minishell.h 

$(NAME) :		$(OBJ)
				cd libft && make
				$(CC) $(FLAGS) $(OBJ) libft/libft.a -ltermcap -o $(NAME)

LIBFT			= libft

all :			$(NAME)

clean :
				cd libft && make clean
				rm -f $(ROAD_O)

fclean :
				cd libft && make fclean
				rm -f $(ROAD_O)
				rm -f $(NAME)

re : 			fclean all

.PHONY: 		all clean fclean re
