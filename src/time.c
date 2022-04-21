#include "../philo.h"

//in millieseconds
long int	get_current_time(struct timeval start_time)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec - start_time.tv_sec) * 1000
		+ (current_time.tv_usec - start_time.tv_usec) / 1000);
}

void	custom_usleep(int milliesec, t_philo *philo)
{
	long int	current;

	pthread_mutex_lock(philo->data->is_dead_mutex);
	if (!philo->data->death_flag)
	{
		pthread_mutex_unlock(philo->data->is_dead_mutex);
		current = get_current_time(philo->data->start_time);
		while (get_current_time(philo->data->start_time) - current < milliesec)
			usleep(10);
	}
	pthread_mutex_unlock(philo->data->is_dead_mutex);
}
