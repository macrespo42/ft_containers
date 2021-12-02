FT_NAME = ft_bin

STD_NAME = std_bin 

CC = clang++

CLFAGS = -I src/ -Wall -Wextra -Werror -std=c++98

TEST_FILES = vector_test.cpp stack_test.cpp map_test.cpp

SRC = $(addsuffix .cpp, $(TEST_FILES))

all: $(STD_NAME) $(FT_NAME)

$(STD_NAME):
	$(CC) $(CLFAGS) -o $(STD_NAME) $(TEST_FILES) main.cpp

$(FT_NAME):
	$(CC) -DFT $(CLFAGS) -o $(FT_NAME) $(TEST_FILES) main.cpp

clean:
	rm -rf $(FT_NAME) $(STD_NAME) diff

fclean: clean

re: fclean all