#!/bin/zsh

echo "Running my main : "
	clang++ main.cpp -o ft_main
	clang++ main.cpp -D NS=std -o std_main
echo "\nTime taken to execute ft::containers : ";
	time ./ft_main > mine.txt
echo "\nTime taken to execute std::containers : ";
	time ./std_main > std.txt
	if diff mine.txt std.txt >/dev/null; then
		echo -e "\e[32mPassed :)\e[0m"
	else
		echo -e "\e[31mFailed :(\e[0m"
	fi

echo "\n--------------------------------------------------------\n"
echo "Running intra's main : "
	clang++ intra_main.cpp -o ft_intra_main
	clang++ intra_main.cpp -D NS=std -o std_intra_main
echo "\nTime taken to execute ft::containers : ";
	time ./ft_intra_main 0 > intra_mine.txt
echo "\nTime taken to execute std::containers : ";
	time ./std_intra_main 1 > intra_std.txt
	if diff intra_mine.txt intra_std.txt >/dev/null; then
		echo -e "\e[32mPassed :)\e[0m"
	else
		echo -e "\e[31mFailed :(\e[0m"
	fi
