all:
	clang++ -I ./src/ -Wall -Wextra -Werror -std=c++98 -o ft_bin vector_test.cpp stack_test.cpp main.cpp -D NAMESPACE=ft

test: all
	clang++ -I ./src/ -Wall -Wextra -Werror -std=c++98 -o std_bin vector_test.cpp stack_test.cpp main.cpp -D NAMESPACE=std
	@./std_bin > std_res
	@./ft_bin > ft_res
	@diff std_res ft_res > diff
	@./test.sh

clean:
	rm -f std_res ft_res diff

fclean: clean
	rm -f std_bin ft_bin

re: fclean all