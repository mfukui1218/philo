#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (!philo || !philo->sim)
	{
		printf("Error: Philosopher or sim is NULL\n");
		return (NULL);
	}
	while (!philo->sim->philosopher_died)
	{
		if (philo->sim->meal_limit > 0 && \
		philo->meals_eaten >= philo->sim->meal_limit)
			break ;
		philo_take_forks(philo);
		philo_eat(philo);
		philo_put_forks(philo);
		philo_sleep(philo);
	}
	return (NULL);
}

void	philo_eat(t_philosopher *philo)
{
	long	time;

	time = get_current_timestamp();
	printf("%ld Philosopher %d is eating\n", time, philo->id);
	philo->last_meal_time = time;
	philo->meals_eaten++;
	usleep(philo->sim->time_to_eat * 1000);
}

void	philo_sleep(t_philosopher *philo)
{
	long	time;

	time = get_current_timestamp();
	printf("%ld Philosopher %d is sleeping\n", time, philo->id);
	usleep(philo->sim->time_to_sleep * 1000);
	time = get_current_timestamp();
	printf("%ld Philosopher %d is thinking\n", time, philo->id);
}

void	philo_take_forks(t_philosopher *philo)
{
	long	time;

	time = get_current_timestamp();
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
		printf("%ld Philosopher %d has taken a fork\n", time, philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		printf("%ld Philosopher %d has taken a fork\n", time, philo->id);
	}
}

void	philo_put_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
