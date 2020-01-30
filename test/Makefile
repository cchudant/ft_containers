CXX=clang++
CXXFLAGS=-Wall -Wextra -Werror -fsanitize=address
OBJECTS=Test.o main.o main_vector.o main_list.o main_stack.o main_queue.o
NAME=test_all

.PHONY: all clean fclean re

run: $(NAME)
	./test_all

all: clean run

$(NAME): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(NAME)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all
