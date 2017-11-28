
#include "mini.h"

char	*ft_strnew_e(size_t size)
{
	char *str;

	if (!(str = ft_strnew(size)))
		ft_error("malloc failed");
	return (str);
}
