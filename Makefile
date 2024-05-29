##
## EPITECH PROJECT, 2024
## Epitech-Tek2-YEP-Zappy
## File description:
## Makefile
##

SRC :=	Main.cpp

OBJ := $(SRC:.cpp=.o)

NAME := zappy_ai

CXX := g++
CXXFLAGS := -Wall -Wextra -Werror -I./include -std=c++17

all: $(NAME)
	cd GUI && rm -rf build && mkdir build && cd build && cmake .. && make

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
