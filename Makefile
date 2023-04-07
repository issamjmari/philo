SRC = philo.c ft_atoi.c philo_utils1.c philo_utils2.c 
OBJ = philo.o ft_atoi.o philo_utils1.o philo_utils2.o
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
NAME = philo

all : $(NAME)

$(NAME) : $(SRC)
	$(CC) -c $(SRC) 
	$(CC) $(SRC) $(CFLAGS) -o $(NAME)
clean :
	$(RM) $(OBJ)
fclean : clean
	$(RM) $(NAME)
re : fclean all