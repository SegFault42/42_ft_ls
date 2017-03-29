#include "./includes/libft.h"

void	ft_strxcat(char *dest, char *src, int x)
{
	while (x > 0)
	{
		ft_strcat(dest, src);
		--x;
	}
}
