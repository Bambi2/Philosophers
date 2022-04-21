#include "../philo.h"

static int	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	print(philo, FORK);
	if (!philo->second_fork)
		return (0);
	pthread_mutex_lock(philo->second_fork);
	print(philo, FORK);
	print(philo, EATING);
	pthread_mutex_lock(philo->last_ate_mutex);
	philo->last_time_ate = get_current_time(philo->data->start_time);
	pthread_mutex_unlock(philo->last_ate_mutex);
	custom_usleep(philo->data->eat_time, philo);
	pthread_mutex_unlock(philo->second_fork);
	pthread_mutex_unlock(philo->first_fork);
	return (1);
}

static void	sleeping(t_philo *philo)
{
	print(philo, SLEEPING);
	custom_usleep(philo->data->sleep_time, philo);
}

static int	check_num_of_meals(t_philo *philo)
{
	philo->num_of_meals--;
	pthread_mutex_lock(philo->data->eaten_mutex);
	if (philo->num_of_meals == 0)
		philo->data->num_of_eaten += 1;
	if (philo->data->num_of_eaten == philo->data->num_of_philos
		&& philo->data->num_of_meals != -1)
	{
		pthread_mutex_unlock(philo->data->eaten_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->data->eaten_mutex);
	return (0);
}

void	*start_sim(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->num % 2 != 0)
		usleep(100);
	pthread_mutex_lock(philo->data->is_dead_mutex);
	while (!philo->data->death_flag)
	{
		pthread_mutex_unlock(philo->data->is_dead_mutex);
		if (!eating(philo))
		{
			pthread_mutex_unlock(philo->first_fork);
			break ;
		}
		if (check_num_of_meals(philo))
			return (0);
		sleeping(philo);
		print(philo, THINKING);
		pthread_mutex_lock(philo->data->is_dead_mutex);
	}
	pthread_mutex_unlock(philo->data->is_dead_mutex);
	return (0);
}
