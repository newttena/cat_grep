WWW = -Werror -Wextra -Wall
G = gcc

all : s21_grep
	$(G) $(WWW) s21_grep.c s21_grep.h -o s21_grep

check: 
	clang-format -style=google -n *.c *.h

clean:
	rm -rf s21_grep s21_cat