#include "philo.h"

void	init_philo(t_philosopher *philosophers,  pthread_mutex_t *left_fork, pthread_mutex_t *right_fork)
{
	philosophers->last_meal_time = get_current_timestamp();
	philosophers->meals_eaten = 0;
	philosophers->left_fork = left_fork;
	philosophers->right_fork = right_fork;
}

void	initialize_philo(t_philosopher *philosophers, t_simulation *sim)
{
	int	i;

	i = 0;
	if (!philosophers)
	{
		printf("Error: NULL pointer detected in initialize_philo\n");
		return;
	}
	while (i < sim->number_of_philosophers)
	{
		philosophers[i].sim = sim;
		philosophers[i].id  = i + 1;
		init_philo(&philosophers[i], &sim->forks[i], &sim->forks[(i + 1) % sim->number_of_philosophers]);
		i++;
	}
}

void	init_sim(t_simulation *sim, char *number_of_philosophers, char *time_to_die, char *time_to_eat, char *time_to_sleep, char *meal_limit)
{
	int	i;

	i = 0;
	if (!sim)
	{
    	printf("Error: sim is NULL\n");
    	return ;
	}
	sim->number_of_philosophers = ft_safe_atoi(number_of_philosophers);
	sim->time_to_die = ft_safe_atoi(time_to_die);
	sim->time_to_eat = ft_safe_atoi(time_to_eat);
	sim->time_to_sleep = ft_safe_atoi(time_to_sleep);
	sim->meal_limit = ft_safe_atoi(meal_limit);
	sim->all_meals_completed = 0;
	sim->philosopher_died = 0;
	pthread_mutex_init(&sim->mutex, NULL);
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->number_of_philosophers);
	if(!sim->forks)
		return ;
	sim->threads = malloc(sizeof(pthread_t) * sim->number_of_philosophers);
	if(!sim->threads)
		return (free(sim->forks));
	while (i < sim->number_of_philosophers)
		pthread_mutex_init(&sim->forks[i++], NULL);
}

void *monitor_death(void *arg)
{
	t_philosopher *philosophers;
	long	current_time;
	int		i;
	int all_meals_completed;

	philosophers = (t_philosopher *)arg;
	if (!philosophers || !philosophers->sim)
		return (printf("Error: philosophers or sim is NULL\n"), NULL);
	while(1)
	{
		i = 0;
		current_time = get_current_timestamp();
		all_meals_completed = 1;
		while(i < philosophers->sim->number_of_philosophers)
		{
			if (current_time - philosophers[i].last_meal_time > philosophers->sim->time_to_die)
			{
				printf("%ld Philosopher %d is dead\n", current_time, philosophers->id);
				philosophers[i].sim->philosopher_died = 1;
				pthread_mutex_unlock(&philosophers->sim->mutex);
                return (NULL);
			}
            if (philosophers->sim->meal_limit > 0 && philosophers[i].meals_eaten < philosophers->sim->meal_limit)
				all_meals_completed = 0;
			i++;
			pthread_mutex_unlock(&philosophers->sim->mutex);
		}
		if (philosophers->sim->meal_limit > 0 && all_meals_completed)
		{
            printf("All philosophers have completed their meals\n");
            philosophers->sim->philosopher_died = 1;
			pthread_mutex_unlock(&philosophers->sim->mutex);
            return (NULL);
        }
		usleep(1000);
	}
	return(NULL);
}
