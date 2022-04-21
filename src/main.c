#include "../philo.h"

int	main(int argc, char **argv)
{
	if (arg_check(argc, argv))
	{
		if (!philo(argc, argv))
			return (1);
	}
	else
		return (1);
	return (0);
}
