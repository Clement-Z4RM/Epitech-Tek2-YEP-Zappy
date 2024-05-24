##
## EPITECH PROJECT, 2024
## Epitech-Tek2-YEP-Zappy
## File description:
## Makefile
##

.ONESHELL:

SERVER_NAME	=	zappy_server

all: $(SERVER_NAME)

$(SERVER_NAME):
	@mkdir -p server/build
	@cd server/build
	@cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
	@cmake --build .
	@cd ../..
	@mv server/$(SERVER_NAME) .

tests_run:
	@echo "There is actually no tests to run for this project"

.PHONY:	$(SERVER_NAME) tests_run
