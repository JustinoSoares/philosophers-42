CC = cc
CFLAGS = -g -Wall -Wextra -Werror
NAME = philo
PROGRAMS = main.c actions.c error.c init.c aux.c
OBJ = $(PROGRAMS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
		 $(CC) $(CFLAGS) $(OBJ) -o $(NAME)
clean :
		rm -f $(OBJ)
fclean : clean
		rm -f $(NAME)
re : fclean all
