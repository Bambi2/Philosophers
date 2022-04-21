#include "../philo.h"

void	print(t_philo *philo, char *message)
{
	pthread_mutex_lock(philo->data->is_dead_mutex);
	if (!philo->data->death_flag)
	{
		pthread_mutex_lock(philo->printing_mutex);
		printf(message, get_current_time(philo->data->start_time), philo->num);
		pthread_mutex_unlock(philo->printing_mutex);
	}
	pthread_mutex_unlock(philo->data->is_dead_mutex);
}

void	free_all(t_philo *philos, pthread_mutex_t *mutexes)
{
	destroy_mutexes(mutexes, (philos->data->num_of_philos * 2) + 2);
	free(mutexes);
	free(philos->data);
	free(philos);
}

int	join_threads(t_philo *philos, pthread_mutex_t *mutexes)
{
	int	i;

	i = 0;
	while (i < philos->data->num_of_philos)
	{
		if (pthread_join(philos[i].th, NULL) != 0)
		{
			pthread_mutex_lock(philos->printing_mutex);
			printf("Couldn't join the threads\n");
			pthread_mutex_unlock(philos->printing_mutex);
			free_all(philos, mutexes);
			return (0);
		}
		i++;
	}
	return (1);
}
