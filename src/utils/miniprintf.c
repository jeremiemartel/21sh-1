#include <stdarg.h>
#include "../../libft/libft.h"

/*char	*types(char *str)
{
	int		i = 0;;
	char	*dst;

	dst = malloc(sizeof(char) * ft_strlen(str));
	while (str[i])
	{
		if (str[i] = 
	}

}*/

void	func(char *str, ...)
{
	va_list ap;

	char *t;
	int i = 0;
	int	j = 1;
	va_start(ap, str);
	t = va_arg(ap, char *);
	while (t)
	{
	//	ft_putendl(t);
		if (str[i] == 's')
		{
			t = va_arg(ap, char *);
			write(2, t, ft_strlen(t));
		}
		else if (str[i] == 'd')
		{
			t = va_arg(ap, int);
			ft_putnbr(t);
		}
	//	j++;
	//	i++;
	}
	va_end(ap);
}

int		main(void)
{
	func("sd", "coucou", "toi");
	return (0);
}
