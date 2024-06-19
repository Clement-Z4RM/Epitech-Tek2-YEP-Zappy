##
## EPITECH PROJECT, 2024
## Epitech-Tek2-YEP-Zappy
## File description:
## Makefile
##

.ONESHELL:

SERVER_NAME	=	zappy_server

AI_DIR  =	ai
AI_NAME =	zappy_ai

all: $(SERVER_NAME) $(AI_NAME)

$(SERVER_NAME):
	@mkdir -p server/build
	@cd server/build
	@cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
	@cmake --build .
	@cd ../..

$(AI_NAME):
    @make -C $(AI_DIR)/

tests_run:
	@echo "There is actually no tests to run for this project"

.PHONY:	$(SERVER_NAME) $(AI_NAME) tests_run
