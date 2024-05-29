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

all:
	@ $(ECHO) $(MAGEN_C) "Making GUI" $(DEFAULT)
	cd GUI && mkdir -p ./build/ && cd ./build/ && cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release && cmake --build . ; cd ..
	mv GUI/zappy_gui .
	@ $(ECHO) $(GREEN_C) $(BOLD_T)"GUI is make" $(DEFAULT)

clean:
	cd GUI/build && make clean

fclean: clean
	cd GUI/build && make clean

re: fclean all
