#include "libft.h"

void	print_nbr(int n, int fd)
{
	char	c;

	if (n == 0)
		return ;
	print_nbr(n / 10, fd);
	c = n % 10 + '0';
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (fd < 0)
		return ;
	if (n == 0)
		write(fd, "0", 1);
	else if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n < 0)
	{
		write(fd, "-", 1);
		print_nbr(n * -1, fd);
	}
	else
		print_nbr(n, fd);
}
