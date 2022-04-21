#include "../philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

long	ft_atoi(const char *str)
{
	int		i;
	long	result;
	int		sign;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 011 && str[i] <= 015))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10 + str[i++] - '0';
	return (result * sign);
}

static int	is_positive_integer(char *arg)
{
	int		i;
	long	temp;
	int		len;

	len = ft_strlen(arg);
	if (len > 10)
		return (0);
	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	temp = ft_atoi(arg);
	if (temp > 2147483647)
		return (0);
	return (1);
}

int	arg_check(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc == 5 || argc == 6)
	{
		while (i < argc)
		{
			if (!is_positive_integer(argv[i]))
			{
				printf("Arguments must be positive integers\n");
				return (0);
			}
			i++;
		}
		return (1);
	}
	printf("Wrong number of arguments\n");
	return (0);
}
