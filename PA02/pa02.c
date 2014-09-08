
#include <stdio.h>
#include <string.h>

#include "answer02.h"

#define BUFFER_LEN 1024

int main(int argc, char * * argv)
{
    printf("Welcome to PA02.\n"
	   "\n"
	   "You are encouraged to edit this file in order to test\n"
	   "the behavior of the functions you write in answer02.c\n"
	   "\n"
	   "This file will not be marked, and should not be\n"
	   "submitted.\n"
	   "\n"
	   "Don't forget to post questions on blackboard, and ask\n"
	   "the TAs and your classmates for help.\n"
	   "\n");

    const char * s1 = "Hello World!";
    const char * s2 = "";
    const char * s3 = "foo";
	const char * s4 = "........................................";
	const char * s5 = "Zippy!";

	char * s = "Hello World!";

	printf("Printing Eric's string: %s\n", s);
	printf("Printing Eric's string: %p\n", s);
	printf("Printing Eric's string: %p\n", s + 1200);
	printf("Printing Eric's string: %p\n", s + 1200);

    // -- my_strlen, should be: 12, 0, and 3
    printf("my_strlen(\"%s\") = %d\n", s1, (int) my_strlen(s1));
    printf("my_strlen(\"%s\") = %d\n", s2, (int) my_strlen(s2));
    printf("my_strlen(\"%s\") = %d\n", s3, (int) my_strlen(s3));

    // -- my_countchar, should be: 3, 0, 2, and 40
    printf("my_countchar(\"%s\", 'l') = %d\n", s1, (int) my_countchar(s1, 'l'));
    printf("my_countchar(\"%s\", 'o') = %d\n", s2, (int) my_countchar(s2, 'o'));
    printf("my_countchar(\"%s\", 'o') = %d\n", s3, (int) my_countchar(s3, 'o'));
	printf("my_countchar(\"%s\", '.') = %d\n", s4, (int)my_countchar(s4, '.'));

    // -- my_strchr, should be: "llo World!", "(null)", "", and "......................................."
    printf("my_strchr(\"%s\", 'l') = %s\n", s1, my_strchr(s1, 'l'));
    printf("my_strchr(\"%s\", 'o') = %s\n", s2, my_strchr(s2, 'o'));
    printf("my_strchr(\"%s\", '\\0') = %s\n", s3, my_strchr(s3, '\0'));
	printf("my_strchr(\"%s\", '.') = %s\n", s4, my_strchr(s4, '.'));

	// -- my_strrchr, should be: "ld!", "(null)", "", and "."
	printf("my_strrchr(\"%s\", 'l') = %s\n", s1, my_strrchr(s1, 'l'));
	printf("my_strrchr(\"%s\", 'o') = %s\n", s2, my_strrchr(s2, 'o'));
	printf("my_strrchr(\"%s\", '\\0') = %s\n", s3, my_strrchr(s3, '\0'));
	printf("my_strrchr(\"%s\", '.') = %s\n", s4, my_strrchr(s4, '.'));

    // -- my_strstr, should be: "World!", "Hello World!", "(null)"
    printf("my_strstr(\"%s\", \"World\") = %s\n", s1, my_strstr(s1, "World"));
    printf("my_strstr(\"%s\", \"\") = %s\n", s1, my_strstr(s1, ""));
    printf("my_strstr(\"%s\", \"hello\") = %s\n", s1, my_strstr(s1, "hello"));

    // -- my_strcpy. For this function you need a buffer where you
    // copy the string to. 
    char buffer[BUFFER_LEN];
    my_strcpy(buffer, s1);
    printf("my_strcpy(buffer, \"%s\"), buffer = \"%s\"\n", s1, buffer);
    my_strcpy(buffer, s2);
    printf("my_strcpy(buffer, \"%s\"), buffer = \"%s\"\n", s2, buffer);
    my_strcpy(buffer, s3);
    printf("my_strcpy(buffer, \"%s\"), buffer = \"%s\"\n", s3, buffer);

    // -- my_strcat
	my_strcpy(buffer, "Hello ");
	printf("my_strcat(buffer, \"%s\"), buffer = \"%s\"\n", s5, my_strcat(buffer, s5)); // prints "Hello Zippy!"

    // -- my_isspace
	if (my_isspace(' ') == 0)
	{
		printf("my_isspace(%c) = 0 --- FAIL \n", ' ');
	}
	if (my_isspace('\f') == 0)
	{
		printf("my_isspace(\\f) = 0 --- FAIL \n");
	}
	if (my_isspace('\n') == 0)
	{
		printf("my_isspace(\\n) = 0 --- FAIL \n");
	}
	if (my_isspace('\r') == 0)
	{
		printf("my_isspace(\\r) = 0 --- FAIL \n");
	}
	if (my_isspace('\t') == 0)
	{
		printf("my_isspace(\\t) = 0 --- FAIL \n");
	}
	if (my_isspace('\v') == 0)
	{
		printf("my_isspace(\\v) = 0 --- FAIL \n");
	}
	char ch;
	for (ch = 'A'; ch <= 'Z'; ch++)
	{
		if (my_isspace(ch) != 0) // always 0
		{
			printf("my_isspace(%c) = 1 --- FAIL \n", ch);
		}
	}

    // -- my_atoi
	printf("my_atoi(\"%s\") = \"%d\"\n", "0", my_atoi("0"));
	printf("my_atoi(\"%s\") = \"%d\"\n", "-12", my_atoi("-12"));
	printf("my_atoi(\"%s\") = \"%d\"\n", "15th of March would be the ides.", my_atoi("15th of March would be the ides."));
	printf("my_atoi(\"%s\") = \"%d\"\n", "4 months to Summer.", my_atoi("4 months to Summer."));
	printf("my_atoi(\"%s\") = \"%d\"\n", "\n\f\t\v\r 6 white space characters handled correctly.",
		my_atoi("\n\f\t\v\r 6 white space characters handled correctly."));
	printf("my_atoi(\"%s\") = \"%d\"\n", "garbage, instead of a number like 73 for example, should yield a zero",
		my_atoi("garbage, instead of a number like 73 for example, should yield a zero"));

    return EXIT_SUCCESS;
}


