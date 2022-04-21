#include "../philo.h"

static pthread_mutex_t	*init_mutexes(int count)
{
	pthread_mutex_t	*mutexes;
	int				i;

	mutexes = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * count);
	if (!mutexes)
	{
		printf("Couldn't allocate memory\n");
		return (NULL);
	}
	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init(mutexes + i, NULL) != 0)
		{
			printf("Couldn't initialize mutexes\n");
			destroy_mutexes(mutexes, i);
			free(mutexes);
			return (NULL);
		}
		i++;
	}
	return (mutexes);
}

void	destroy_mutexes(pthread_mutex_t	*mutexes, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pthread_mutex_destroy(mutexes + i) != 0)
		{
			printf("Couldn't destroy mutexes\n");
			break ;
		}
		i++;
	}
}

void	unlock_mutexes(pthread_mutex_t	*mutexes, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_unlock(mutexes + i);
		i++;
	}
}

void	set_last_ate_mutex(t_philo *philos, pthread_mutex_t	*mutexes, int count)
{
	int	i;

	i = 0;
	while (i < philos->data->num_of_philos)
	{
		philos[i].last_ate_mutex = mutexes + count - 4 - i;
		i++;
	}
}

pthread_mutex_t	*set_mutexes(t_philo *philos)
{
	pthread_mutex_t	*mutexes;
	int				i;
	int				count;

	count = (philos->data->num_of_philos * 2) + 3;
	mutexes = init_mutexes(count);
	if (!mutexes)
		return (NULL);
	set_last_ate_mutex(philos, mutexes, count);
	philos->data->is_dead_mutex = mutexes + count - 2;
	philos->data->eaten_mutex = mutexes + count - 3;
	i = 1;
	while (i < philos->data->num_of_philos)
	{
		philos[i].first_fork = mutexes + i - 1;
		philos[i].second_fork = mutexes + i;
		philos[i].printing_mutex = mutexes + count - 1;
		i++;
	}
	philos[0].first_fork = mutexes;
	philos[0].second_fork = mutexes + i - 1;
	if (philos->data->num_of_philos == 1)
		philos[0].second_fork = NULL;
	philos[0].printing_mutex = mutexes + count - 1;
	return (mutexes);
}
