# gna
simple genetic algorithm

# usage
## Creating & Destroying Population
```c
int pop_size = 2000;
int gene_size = 4;
double mutation_rate = 0.1;

struct GNA_Body *population = gna_init(pop_size, gene_size, mutation_rate, fitness_function); // fitness_function should be overriden by your own function
gna_destroy(population);
```

## Fitness Function Example
You need to override the fitness_function since this is where the logic of the system reside. This funciton should return int value, and the value would be used to rank the best and the worst chromosome. 
The function should follow this form: 
int func_name_you_can_think_of(struct GNA_Body chromosome)

```c
int target[4] = {5, 4, 1, 4};
int min = 1;
int max = 10;
int fitness_function(struct GNA_Body chromosome)
{
	// gna_scale() function is used to scale up the chromosome.properties[x] (0 - 1) value into (1 - 10)
	int a = (int)abs((int)gna_scale(1, 10, chromosome.properties[0]) - target[0]);
	int b = (int)abs((int)gna_scale(1, 10, chromosome.properties[1]) - target[1]);
	int c = (int)abs((int)gna_scale(1, 10, chromosome.properties[2]) - target[2]);
	int d = (int)abs((int)gna_scale(1, 10, chromosome.properties[3]) - target[3]);
	return 1000 - a - b - c - d;
}
```

## Run Genetic Algorithm
```c
for (int generation = 0; generation<20; generation++)
{
	gna_evolve(population, pop_size, 0.5);
	// 0.5 is parent/child ratio
	// example: if you have population of 10 and parent/child ratio of 3/7. It means 3 parents will be crossovered
	// to generate new children replacing 7 children
}
```

## Get The Hyperparameters
The Population always ordered descending. First element should be a chromosome with the best fitness value.

```c
double* params = population[0].properties;
```
