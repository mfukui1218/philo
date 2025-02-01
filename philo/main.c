#include "philo.h"

int 	main(int argc, char **argv)
{
	t_philosopher	*philo;
	t_simulation	sim;
	pthread_t		monitor_thread;
	int				i;

	if (argc != 5 && argc != 6)
		return (printf("Usage: ./philo [num_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [meal_limit(optional)]\n"), 1);
	philo = malloc(sizeof(t_philosopher) * atoi(argv[1]));
	if (!philo)
		return (1);
	if(argc == 6)
		init_sim(&sim, argv[1], argv[2], argv[3], argv[4], argv[5]);
	else
		init_sim(&sim, argv[1], argv[2], argv[3], argv[4], NULL);
	initialize_philo(philo, &sim);
	i = 0;
	while (i < sim.number_of_philosophers)
	{
		pthread_create(&sim.threads[i], NULL, philosopher_routine, &philo[i]);
		i++;
	}
	pthread_create(&monitor_thread, NULL, monitor_death, philo);
	i = 0;
	while (i < sim.number_of_philosophers)
		pthread_join(sim.threads[i++], NULL);
	pthread_join(monitor_thread, NULL);
	pthread_mutex_destroy(&sim.mutex);
	free(sim.forks);
	free(sim.threads);
	free(philo);
	return (0);
}