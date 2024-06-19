##
## EPITECH PROJECT, 2024
## Epitech-Tek2-YEP-Zappy
## File description:
## Makefile
##

SRC = src/main.lua

EXECUTABLE = ../zappy_ai

all:	build

build:
	@cp $(SRC) $(EXECUTABLE)
	@chmod u+x $(EXECUTABLE)

fclean:
	@rm -f $(EXECUTABLE)

re:	fclean all

.PHONY:	all build fclean re
