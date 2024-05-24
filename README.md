# gna
simple genetic algorithm

# usage
## Creating & Destroying Population
```
int pop_size = 2000;
int gene_size = 4;
double mutation_rate = 0.1;

struct GNA_Body *population = gna_init(pop_size, 4, 0.1, fitness_function); // fitness_function should be overiden by your own function
gna_destroy(population);
```

## Fitness Funciton Example
```
int target[4] = {5, 4, 1, 4};
int score(struct GNA_Body chromosome)
{
	int a = (int)abs((int)gna_scale(1, 10, chromosome.properties[0]) - target[0]);
	int b = (int)abs((int)gna_scale(1, 10, chromosome.properties[1]) - target[1]);
	int c = (int)abs((int)gna_scale(1, 10, chromosome.properties[2]) - target[2]);
	int d = (int)abs((int)gna_scale(1, 10, chromosome.properties[3]) - target[3]);
	return 1000 - a - b - c - d;
}
```

## Run Genetic Algorithm
```
for (int generation = 0; generation<20; generation++)
{
	gna_evolve(pool, 2000, 0.5);
}
```

## Get The Hyperparameters
```
double* params = population[0].properties;
```
