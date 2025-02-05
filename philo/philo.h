#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ALLOCTAE_ERROR 1

typedef struct s_philosopher {
	int					id;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	long				last_meal_time;
	size_t				meals_eaten;
	struct s_simulation	*sim;
}	t_philosopher;

typedef struct s_simulation {
	size_t			number_of_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	size_t			meal_limit;
	int				all_meals_completed;
	int				philosopher_died;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*forks;
	pthread_t		*threads;
}	t_simulation;

//action
void	*philo_routine(void *arg);
void	philo_eat(t_philosopher *philo);
void	philo_sleep(t_philosopher *philo);
void	philo_take_forks(t_philosopher *philo);
void	philo_put_forks(t_philosopher *philo);
void	philo_died(t_philosopher *philo, long time);
void	philo_all_completed(t_philosopher *philo);

//init
int		init_all(t_simulation *sim, t_philosopher *philo,\
 int paramc, char **param);
void	init_philo(t_philosopher *philo, t_simulation *sim);
void	init_sim(t_simulation *sim, int paramc, char **param);

//monitor
void	*monitor_death_complete(void *arg);
void	loop_for_monitor(t_philosopher *philo, long current_time);
int		died_check_and_died(t_philosopher *philo, long current_time);
int		completed_check(t_philosopher *philo);

//utils
void	pthread_create_all(t_philosopher *philo, t_simulation *sim);
void	pthread_join_all(t_simulation *sim);
long	get_current_timestamp();
int		safe_atoi(char *str);
void	free_all(t_philosopher *philosophers, t_simulation *sim);

//error
void	error_sel(int sign);

#endif
