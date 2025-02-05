#include "philo.h"

void	philo_died(t_philosopher *philo, long time)
{
	printf("%ld Philosopher %d died\n", time, philo->id);
	philo->sim->philosopher_died = 1;
	pthread_mutex_unlock(&philo->sim->mutex);
}

void	philo_all_completed(t_philosopher *philo)
{
	printf("All philosophers have completed their meals\n");
	philo->sim->all_meals_completed = 1;
	pthread_mutex_unlock(&philo->sim->mutex);
}
