gcc -o pa11 pa11.c answer11.c -Wall -Wshadow

valgrind --tool=memcheck --leak-check=full --verbose --log-file=memcheck.log ./pa11
