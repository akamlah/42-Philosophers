#include "../header/philosophers.h"

size_t	ft_strlen (const char *s)
{
	size_t	slen;

	slen = 0;
	while (s[slen] != '\0')
		slen++;
	return (slen);
}