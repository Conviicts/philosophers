NAME			=		philo
CC				=		clang
FLAGS			=		-g -Wall -Werror -Wextra -I $(dir $(HEADER)) #-fsanitize=address

HEADER          =		./inc/philo.h
SRCS            =		src/main.c									\
						src/utils.c									\
						src/init.c									\
						src/errors.c								\
						src/thread.c								
.c.o:
						$(CC) $(FLAGS) -c $< -o ${<:.c=.o}

OBJS			=		$(SRCS:.c=.o)

all				:		$(NAME)

$(NAME)			:		$(OBJS) $(HEADER)
						$(CC) -o $(NAME) $(FLAGS) $(OBJS) -pthread
						@echo "\033[1;31m$(NAME)\033[0;33m created\033[0m"

clean			:
						rm -rf $(OBJS)
						@echo "\033[0;33mCleaning philosopher: \033[1;31m.o\033[0;33m files\033[0m"

fclean			:		clean
						rm -f $(NAME)
						@echo "\033[0;33mCleaning philosopher: \033[1;31m$(NAME)\033[0m"

re				:		fclean all

.PHONY:		all clean fclean re