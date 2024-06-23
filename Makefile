##
## EPITECH PROJECT, 2024
## Epitech-Tek2-YEP-Zappy
## File description:
## Makefile
##

.ONESHELL:

BUILD_TYPE	=	Release

SERVER_DIR	=	server
SERVER_NAME	=	zappy_server

AI_DIR	=	ai
AI_NAME	=	zappy_ai

GUI_DIR		=	gui
GUI_NAME	=	zappy_gui

all:	$(SERVER_NAME) $(GUI_NAME) $(AI_NAME)

server:	$(SERVER_NAME)
$(SERVER_NAME):
	@mkdir -p $(SERVER_DIR)/build
	@cd $(SERVER_DIR)/build
	@cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)
	@cmake --build .
	@cd ../..
	@mv $(SERVER_DIR)/$(SERVER_NAME) .

gui:	$(GUI_NAME)
$(GUI_NAME):
	@mkdir -p $(GUI_DIR)/build
	@cd $(GUI_DIR)/build
	@cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)
	@cmake --build .
	@cd ../..
	@mv $(GUI_DIR)/$(GUI_NAME) .

$(AI_NAME):
	@$(MAKE) -sC $(AI_DIR)/

debug:
	@$(MAKE) -s BUILD_TYPE=Debug

clean:
	@rm -rf $(SERVER_DIR)/build
	@rm -rf $(GUI_DIR)/build

fclean:	clean
	@rm -f $(SERVER_NAME)
	@rm -f $(GUI_NAME)
	@$(MAKE) -sC $(AI_DIR)/ fclean

tests_run:
	@echo "There is actually no tests to run for this project"

re:	fclean all

robot: all
	@lolcat ./robot.txt

.PHONY:	all $(SERVER_NAME) $(GUI_NAME) $(AI_NAME) \
		debug clean fclean tests_run re robot
