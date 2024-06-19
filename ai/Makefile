##
## EPITECH PROJECT, 2024
## Epitech-Tek2-YEP-Zappy
## File description:
## Makefile
##

AI_NAME = zappy_ai

SRC = src/main.lua
EXECUTABLE = ../$(AI_NAME)

all:	build

build:
	@cp $(SRC) $(EXECUTABLE)
	@chmod u+x $(EXECUTABLE)

fclean:
	@rm -f $(EXECUTABLE)

re:	fclean all

.PHONY:	all build fclean re
