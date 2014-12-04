gcc -o search search.c answer10.c -Wall -Wshadow

valgrind --tool=memcheck --leak-check=full --verbose --log-file=memcheck.log ./search

diff test0 test/00.Boston_Cleaners.NV.89135 > result0

diff test1 test/01.Boston_Cleaners.NV > result2

diff test2 test/02.Boston_Cleaners > result3

diff test3 test/03.Boston_Cleaners.89135 > result4

diff test4 test/04.bOsToN_cLeAnErS.89135 > result5

diff test5 test/05.Rubys_Diner.85226 > result6

diff test6 test/06.Capriottis > result7

diff test7 test/07.Subway.AA > result8

diff test8 test/08.Subway.00000 > result9

diff test9 test/09.aaaaaaaaaaa > result10

diff test10 test/10.Simplicity_Laser_Hair_Removal > result11

diff test11 test/11.McDonalds.Burger_King.Wendys.Starbucks > result12

git log > git.log