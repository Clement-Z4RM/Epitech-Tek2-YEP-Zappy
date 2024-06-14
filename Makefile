##
## EPITECH PROJECT, 2024
## Epitech-Tek2-YEP-Zappy
## File description:
## Makefile
##
.ONESHELL:

.ONESHELL:

BUILD_TYPE	=	Release

SERVER_DIR	=	server
SERVER_NAME	=	zappy_server

all: $(SERVER_NAME)

$(SERVER_NAME):
	@mkdir -p $(SERVER_DIR)/build
	@cd $(SERVER_DIR)/build
	@cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)
	@cmake --build .
	@cd ../..
	@mv $(SERVER_DIR)/$(SERVER_NAME) .

debug:
	@$(MAKE) -s BUILD_TYPE=Debug

tests_run:
	@echo "There is actually no tests to run for this project"

.PHONY:	all $(SERVER_NAME) debug tests_run
