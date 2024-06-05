SRC = src/main.lua

EXECUTABLE = ../zappy_ai

DIST_FOLDER = ../..

all: build

build:
	cp $(SRC) $(EXECUTABLE)
	chmod u+x $(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)

fclean: clean
	rm -f $(DIST_FOLDER)/$(EXECUTABLE)

re: fclean all

.PHONY: all build clean fclean re