#include "mini.h"

int	ft_strlen_till(char *str, char c)
{
	int len;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	return (len);
}
