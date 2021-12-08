# ft_containers
Reimplementation of some containers from STL

## MANDATORY PART

- Implementation of std::vector
- Implementation of std::stack (with std::vector as default underlying container)
- Implementation of std::map

## Bonus part

Implement std::set with a redblack tree inside !

## How to use

This project is done for linux comptability but it compile also on mac
neverless on mac vector can have a different capacity than std and map a different max_size

1 use make to compile the mandatory part and make bonus to compile the bonus part
2 Now you have 2 binaries ft_bin and std_bin
3 you can launch test.sh he make the diff between the 2 binaries and stock log in diff file
4 otherwise you can launch the binaries and check the output same test are done one with std containers one with mine
5 if you want to check the tests yourself or add some, for example for the vector check the corresponding file [container_name]_test.cpp
