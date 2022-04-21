#include "../philo.h"

static t_data	*init_data(int argc, char **argv)
{
	t_data	*data;

	data = (t_data *) malloc(sizeof(t_data));
	if (!data)
	{
		printf("Couldn't allocate memory\n");
		return (NULL);
	}
	data->num_of_philos = ft_atoi(argv[1]);
	if (data->num_of_philos == 0)
	{
		free(data);
		printf("There must be at least 1 philosopher\n");
		return (NULL);
	}
	data->die_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	data->death_flag = 0;
	data->num_of_eaten = 0;
	if (argc == 6)
		data->num_of_meals = ft_atoi(argv[5]);
	else
		data->num_of_meals = -1;
	return (data);
}

t_philo	*create_philos(int argc, char **argv)
{
	t_philo			*philos;
	int				i;
	t_data			*data;

	data = init_data(argc, argv);
	if (!data)
		return (NULL);
	philos = (t_philo *) malloc(sizeof(t_philo) * data->num_of_philos);
	if (!philos)
	{
		printf("Couldn't allocate memory\n");
		free(data);
		return (NULL);
	}
	i = 0;
	while (i < data->num_of_philos)
	{
		philos[i].data = data;
		philos[i].num = i + 1;
		philos[i].last_time_ate = 0;
		philos[i].num_of_meals = data->num_of_meals;
		i++;
	}
	return (philos);
}
