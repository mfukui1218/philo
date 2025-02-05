#include "philo.h"

int	init_all(t_simulation *sim, t_philosopher *philo, int paramc, char **param)
{
	sim->forks = malloc(sizeof(pthread_mutex_t) * safe_atoi(param[1]));
	if (!sim->forks)
	{
		free(philo);
		return (error_sel(ALLOCTAE_ERROR), 0);
	}
	sim->threads = malloc(sizeof(pthread_t) * safe_atoi(param[1]));
	if (!sim->threads)
	{
		free(philo);
		free(sim->forks);
		return (error_sel(ALLOCTAE_ERROR), 0);
	}
	init_sim(sim, paramc, param);
	init_philo(philo, sim);
	return (1);
}

void	init_sim(t_simulation *sim, int paramc, char **param)
{
	size_t	i;

	i = 0;
	if (!sim)
		return ((void)printf("Error: sim is NULL\n"));
	sim->number_of_philosophers = (size_t)safe_atoi(param[1]);
	sim->time_to_die = (long)safe_atoi(param[2]);
	sim->time_to_eat = (long)safe_atoi(param[3]);
	sim->time_to_sleep = (long)safe_atoi(param[4]);
	if (paramc == 6)
		sim->meal_limit = (size_t)safe_atoi(param[5]);
	sim->all_meals_completed = 0;
	sim->philosopher_died = 0;
	pthread_mutex_init(&sim->mutex, NULL);
	while (i < sim->number_of_philosophers)
		pthread_mutex_init(&sim->forks[i++], NULL);
}

void	init_philo(t_philosopher *philo, t_simulation *sim)
{
	size_t	i;

	i = 0;
	if (!philo)
		return ((void)printf("Error: NULL pointer detected in philo\n"));
	while (i < sim->number_of_philosophers)
	{
		philo[i].sim = sim;
		philo[i].id  = i + 1;
		philo[i].last_meal_time = get_current_timestamp();
		philo[i].meals_eaten = 0;
		philo[i].left_fork = &sim->forks[i];
		philo[i].right_fork = &sim->forks[(i + 1) % sim->number_of_philosophers];
		i++;
	}
}
