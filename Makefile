
all:
	clang++ -I ./src/ main.cpp

# %.o: %.c
# 	clang++ -I ./src/ -c main.cpp

clean:
	rm main.o

fclean:
	rm a.out

re: fclean all