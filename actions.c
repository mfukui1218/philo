#include "philo.h"

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (!philo || !philo->sim)
	{
        printf("Error: Philosopher or sim is NULL\n");
        return (NULL);
    }
	while (!philo->sim->philosopher_died && philo->meals_eaten < philo->sim->meal_limit)
	{
		ft_eat(philo);
		ft_sleep(philo);
	}
	return (NULL);
}

void	ft_eat(t_philosopher *philo)
{
	long	time;

	time = get_current_timestamp();
	take_forks(philo);
	philo->last_meal_time = time;
	philo->meals_eaten++;
	printf("%ld Philosopher %d is eating\n", time, philo->id);
	usleep(philo->sim->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	printf("%ld Philosopher %d is putting down left fork\n", time, philo->id);
	pthread_mutex_unlock(philo->right_fork);
	printf("%ld Philosopher %d is putting down right fork\n", time, philo->id);
}

void	ft_sleep(t_philosopher *philo)
{
	long	time;

	time = get_current_timestamp();
	printf("%ld Philosopher %d is sleeping\n", time, philo->id);
	usleep(philo->sim->time_to_sleep * 1000);
	time = get_current_timestamp();
	printf("%ld Philosopher %d is waking up\n", time, philo->id);
	printf("%ld Philosopher %d is thinking\n", time, philo->id);
}

void	take_forks(t_philosopher *philo)
{
	long	time;

	time = get_current_timestamp();
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		printf("%ld Philosopher %d is taking left fork\n", time, philo->id);
		pthread_mutex_lock(philo->right_fork);
		printf("%ld Philosopher %d is taking right fork\n", time, philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		printf("%ld Philosopher %d is taking right fork\n", time, philo->id);
		pthread_mutex_lock(philo->left_fork);
		printf("%ld Philosopher %d is taking left fork\n", time, philo->id);
	}
}
