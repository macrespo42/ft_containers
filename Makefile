
all:
	clang++ -I ./src/ -Wall -Wextra -Werror -std=c++98 main.cpp

fclean:
	rm a.out

re: fclean all