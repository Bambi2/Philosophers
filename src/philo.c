#include "../philo.h"

static int	is_dead(t_philo *philo)
{
	int	current_time;

	current_time = get_current_time(philo->data->start_time);
	pthread_mutex_lock(philo->last_ate_mutex);
	if ((current_time - philo->last_time_ate) > philo->data->die_time)
	{
		pthread_mutex_lock(philo->data->is_dead_mutex);
		philo->data->death_flag = 1;
		pthread_mutex_unlock(philo->data->is_dead_mutex);
		pthread_mutex_unlock(philo->last_ate_mutex);
		pthread_mutex_lock(philo->printing_mutex);
		printf("%d %d died\n", current_time, philo->num);
		pthread_mutex_unlock(philo->printing_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->last_ate_mutex);
	return (0);
}

static int	init_philos(t_philo **philos, pthread_mutex_t **mutexes,
	int argc, char **argv)
{
	*philos = create_philos(argc, argv);
	if (!*philos)
		return (0);
	*mutexes = set_mutexes(*philos);
	if (!(*mutexes))
	{
		free((*philos)->data);
		free(*philos);
		return (0);
	}
	return (1);
}

static int	run_philos(t_philo *philos)
{
	int	i;

	i = 0;
	gettimeofday(&(philos->data->start_time), NULL);
	while (i < philos->data->num_of_philos)
	{
		if (pthread_create(&(philos[i].th), NULL, start_sim, philos + i) != 0)
		{
			pthread_mutex_lock(philos->printing_mutex);
			printf("Couldn't create threads\n");
			pthread_mutex_unlock(philos->printing_mutex);
			while (i - 1 >= 0)
			{
				pthread_detach(philos[i].th);
				i--;
			}
			philos->data->death_flag = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

static int	watch(t_philo *philos, pthread_mutex_t *mutexes)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < philos->data->num_of_philos)
		{
			if ((philos->data->num_of_eaten == philos->data->num_of_philos
					&& philos->data->num_of_meals != -1) || is_dead(philos + i))
			{
				if (!join_threads(philos, mutexes))
					return (0);
				free_all(philos, mutexes);
				return (1);
			}
			i++;
		}
	}
	return (0);
}

int	philo(int argc, char **argv)
{
	t_philo			*philos;
	pthread_mutex_t	*mutexes;

	if (!init_philos(&philos, &mutexes, argc, argv))
		return (0);
	if (!run_philos(philos))
	{
		free_all(philos, mutexes);
		return (0);
	}
	if (!watch(philos, mutexes))
		return (0);
	return (1);
}
