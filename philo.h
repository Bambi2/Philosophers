#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

# define EATING "%ld %d is eating\n"
# define FORK "%ld %d has taken a fork\n"
# define SLEEPING "%ld %d is sleeping\n"
# define THINKING "%ld %d is thinking\n"

//in microseconds
typedef struct s_data
{
	int				num_of_philos;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				num_of_meals;
	int				death_flag;
	int				num_of_eaten;
	pthread_mutex_t	*is_dead_mutex;
	pthread_mutex_t	*eaten_mutex;
	struct timeval	start_time;
}	t_data;

typedef struct s_philo
{
	int				num;
	int				num_of_meals;
	t_data			*data;
	pthread_t		th;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	pthread_mutex_t	*printing_mutex;
	pthread_mutex_t	*last_ate_mutex;
	int				last_time_ate;
}	t_philo;

int					philo(int argc, char **argv);

t_philo				*create_philos(int argc, char **argv);

//mutexes
pthread_mutex_t		*set_mutexes(t_philo *philos);
void				destroy_mutexes(pthread_mutex_t	*mutexes, int count);
void				unlock_mutexes(pthread_mutex_t	*mutexes, int count);

//simulation
void				*start_sim(void *arg);

//time
long int			get_current_time(struct timeval start_time);
void				custom_usleep(int milliesec, t_philo *philo);

//utils
void				print(t_philo *philo, char *message);
void				free_all(t_philo *philos, pthread_mutex_t *mutexes);
int					join_threads(t_philo *philos, pthread_mutex_t *mutexes);

int					arg_check(int argc, char **argv);

long				ft_atoi(const char *str);

#endif