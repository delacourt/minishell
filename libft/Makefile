# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: delacourt <delacourt@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/09 09:43:38 by delacourt         #+#    #+#              #
#    Updated: 2019/10/16 14:33:46 by delacourt        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

SRC			= 	char_in_str.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
				ft_isdigit.c ft_isprint.c ft_memset.c ft_strjoin.c \
				ft_strlen.c ft_strtrim.c ft_substr.c ft_tolower.c ft_bzero.c \
				ft_toupper.c ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c \
				ft_putendl_fd.c ft_revstr.c ft_strtrim.c ft_itoa.c ft_strmapi.c\
				ft_memcpy.c ft_atoi.c ft_memccpy.c ft_memmove.c ft_memchr.c \
				ft_memcmp.c ft_strrchr.c ft_strchr.c ft_strncmp.c \
				ft_split.c ft_strlcpy.c ft_strlcat.c ft_strnstr.c ft_strdup.c \
				ft_calloc.c ft_lstnew.c

HEADER			= libft.h

FLAGS			= -Wall -Wextra -Werror -I${HEADER}

CC				= gcc -O3

OBJS		= ${SRC:.c=.o}

%.o : %.c
	${CC} ${FLAGS} -c  $< -o ${<:.c=.o}

$(NAME) :		${OBJS}

all :		$(NAME)
				ar rc ${NAME} ${OBJS}

clean :
				rm -f ${OBJS}

fclean :		clean
				rm -f ${NAME}

re : 			fclean all

.PHONY:			all clean fclean re
