RED    = \033[31m
GREEN  = \033[32m
YELLOW = \033[33m
BLUE   = \033[34m
RESET  = \033[0m

WIDTH = 20

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = philo
PROGRAMS = main.c actions.c error.c init.c aux.c
OBJ = $(PROGRAMS:.c=.o)

all : progress $(NAME)

$(NAME) : $(OBJ)
		@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
clean :
		rm -f $(OBJ)
fclean : clean
		rm -f $(NAME)
re : fclean all

progress:
	@for i in $$(seq 1 $(WIDTH)); do \
		PCT=$$(( i * 100 / $(WIDTH) )); \
		COLOR=$$( [ $$(( i % 4 )) -eq 0 ] && printf "$(RED)" || \
				 [ $$(( i % 4 )) -eq 1 ] && printf "$(GREEN)" || \
				 [ $$(( i % 4 )) -eq 2 ] && printf "$(YELLOW)" || \
				 echo "$(BLUE)" ); \
		BAR=$$(printf "%-$(i)s" "####################" | cut -c -$$i); \
		printf "\r$${COLOR}[%-$(WIDTH)s] $${PCT}%%$(RESET)" "$${BAR}"; \
		sleep 0.1; \
	done; \
	printf "\n"

