# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bvarlamo <bvarlamo@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/23 22:05:50 by bvarlamo          #+#    #+#              #
#    Updated: 2022/02/23 22:26:35 by bvarlamo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PHILO=	philos.c helpers.c \

NAME	=	philo

CC	=	gcc

RM	=	rm -f

CFLAGS	=	-Wall -Wextra -Werror

PHILOO=	$(PHILO:.c=.o)

all :		$(NAME)

${NAME}:	${PHILOO}
	${CC} ${CFLAGS} ${PHILOO} -o ${NAME}

clean :
	$(RM) ${PHILOO}

fclean :	clean
	$(RM) $(NAME)

re :		fclean all