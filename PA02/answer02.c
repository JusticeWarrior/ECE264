#include "answer02.h"

size_t my_strlen(const char * str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		i++;
	}

	return i;
}

int my_countchar(const char * str, char ch)
{
	int i;
	int strSize = (int)my_strlen(str);
	int count = 0;

	for (i = 0; i < strSize; i++)
	{
		if (str[i] == ch)
		{
			count++;
		}
	}

	return count;
}

char * my_strchr(const char * str, int ch)
{
	int i;
	int strSize = (int)my_strlen(str);

	for (i = 0; i <= strSize; i++)
	{
		if (str[i] == ch)
		{
			return (char *)(&str[i]);
		}
	}

	return NULL;
}

char * my_strrchr(const char * str, int ch)
{
	int i;
	int strSize = (int)my_strlen(str);

	for (i = strSize; i >= 0; i--)
	{
		if (str[i] == ch)
		{
			return (char *)(&str[i]);
		}
	}

	return NULL;
}

char * my_strstr(const char * haystack, const char * needle)
{
	if (needle[0] == '\0')
		return (char *)haystack;

	int haystackSize = (int)my_strlen(haystack);
	int needleSize = (int)my_strlen(needle);
	int i;
	int j;

	for (i = 0; i + needleSize <= haystackSize; i++)
	{
		for (j = i; j < i + needleSize; j++)
		{
			if (haystack[j] != needle[j - i])
				goto spin;
		}
		
		return (char *)&haystack[i];
		
		spin:;
	}

	return NULL;
}

char * my_strcpy(char * dest, const char * src)
{
	int i;
	int srcSize = (int)my_strlen(src);

	for (i = 0; i <= srcSize; i++)
	{
		dest[i] = src[i];
	}

	return dest;
}

char * my_strcat(char * dest, const char * src)
{
	int i;
	int srcSize = (int)my_strlen(src);
	int destSize = (int)my_strlen(dest);

	for (i = 0; i <= srcSize; i++)
	{
		dest[i + destSize] = src[i];
	}

	return dest;
}

int my_isspace(int ch)
{
	switch (ch)
	{
		case ' ':
			return 1;
		case '\f':
			return 1;
		case '\n':
			return 1;
		case '\r':
			return 1;
		case '\t':
			return 1;
		case '\v':
			return 1;
		default:
			return 0;
	}
}

int my_atoi(const char * str)
{
	int i = 0;
	int strSize = (int)my_strlen(str);
	int ret = 0;
	int negative = 1;

	while (my_isspace(str[i]) == 1 && i < strSize)
	{
		i++;
	}

	if (str[i] == '-')
	{
		negative = -1;
		i++;
	}

	while (i < strSize)
	{
		if ((int)'0' <= (int)str[i] && (int)str[i] <= (int)'9')
		{
			ret *= 10;
			ret += (str[i] - '0');
			i++;
			continue;
		}
		break;
	}

	return ret * negative;
}
