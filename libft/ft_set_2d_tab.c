#include "./includes/libft.h"

void	ft_set_2d_tab(char **tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		tab[i] = NULL;
		++i;
	}
}
