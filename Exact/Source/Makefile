NAME = graph_exact

SRC = main.cpp 				\
	  define.cpp			\


OBJ = $(SRC:.cpp=.o)

CC = g++

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) -o $(NAME) $(OBJ)

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re