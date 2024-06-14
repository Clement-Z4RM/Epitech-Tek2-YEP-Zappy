##
## EPITECH PROJECT, 2024
## Epitech-Tek2-YEP-Zappy
## File description:
## Makefile
##
ECHO=/bin/echo -e
DEFAULT="\e[0m"
BOLD_T="\e[1m"
DIM_T="\e[2m"
UNDLN_T="\e[4m"
BLACK_C="\e[30m"
RED_C="\e[31m"
GREEN_C="\e[32m"
LIGHT_BLUE="\e[33m"
LIGHT_BLUE="\e[34m"
MAGEN_C="\e[35m"
CYAN_C="\e[36m"
LIGHT_BLUE="\e[97m"
DEFAULT_C="\e[39m"
LIGHT_GREY="\e[37m"
DARK_GREY="\e[90m"
LIGHT_RED="\e[91m"
LIGHT_GREEN="\e[92m"
LIGHT_YELLO="\e[93m"
LIGHT_BLUE="\e[94m"
LIGHT_MAGEN="\e[95m"
LIGHT_CYAN="\e[96m"

.ONESHELL:

BUILD_TYPE	=	Release

SERVER_DIR	=	server
SERVER_NAME	=	zappy_server

GUI_DIR		=	gui
GUI_NAME	=	zappy_gui

all: $(SERVER_NAME) $(GUI_NAME)

$(SERVER_NAME):
	@mkdir -p $(SERVER_DIR)/build
	@cd $(SERVER_DIR)/build
	@cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)
	@cmake --build .
	@cd ../..
	@mv $(SERVER_DIR)/$(SERVER_NAME) .

$(GUI_NAME):
	@mkdir -p $(GUI_DIR)/build
	@cd $(GUI_DIR)/build
	@cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)
	@cmake --build .
	@cd ../..
	@mv $(GUI_DIR)/$(GUI_NAME) .

debug:
	@$(MAKE) -s BUILD_TYPE=Debug

tests_run:
	@echo "There is actually no tests to run for this project"

robot: all
	@cat ./robot.txt | lolcat

.PHONY:	all $(SERVER_NAME) $(GUI_NAME) debug tests_run
