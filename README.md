# gna
simple genetic algorithm

# usage
## Creating & Destroying Population
```
int pop_size = 2000;
int gene_size = 4;
double mutation_rate = 0.1;

struct GNA_Body *population = gna_init(pop_size, 4, 0.1, score);
gna_destroy(population);
```

## Run Genetic Algorithm
```
for (int generation = 0; generation<20; generation++)
{
	gna_evolve(pool, 2000, 0.5);
}
```

## Get The Hyperparameters
double* params = population[0].properties;

