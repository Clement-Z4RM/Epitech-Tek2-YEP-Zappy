##
## EPITECH PROJECT, 2024
## Epitech-Tek2-YEP-Zappy
## File description:
## Makefile
##

AI_NAME = zappy_ai

SRC = src/main.lua
EXECUTABLE = ../$(AI_NAME)
DIST_FOLDER = ../..

all: $(AI_NAME)

$(AI_NAME):
	@mkdir -p $(DIST_FOLDER)
	@cp $(SRC) $(EXECUTABLE)
	@chmod u+x $(EXECUTABLE)

clean:
	@rm -f $(EXECUTABLE)

fclean: clean
	@rm -rf $(DIST_FOLDER)/$(EXECUTABLE)

re: fclean all

.PHONY: all $(AI_NAME) clean fclean re
