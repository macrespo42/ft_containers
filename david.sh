clang++ main.cpp -I src/ -DFT && ./a.out > ft
clang++ main.cpp -I src && ./a.out > std
diff ft std
