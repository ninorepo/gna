double __gna_rand()
{
	return (double)rand() / (double)RAND_MAX;
}

int __gna_rand_decimal(int max)
{
	return rand() % max;
}

int __gna_qsort_comparator(const void *a, const void *b)
{
	// sort descending
	int left, right;
	left = ((struct Gna_Chromosome *)a)->rank;
	right = ((struct Gna_Chromosome *)b)->rank;
	return right - left;
}

int __gna_sort(struct Gna_Chromosome *pool, int pool_size)
{
	qsort(pool, pool_size, sizeof(pool[0]), __gna_qsort_comparator);
	return 0;
}

int __gna_mutation(struct Gna_Chromosome *child)
{
	int index = 0;
	int loops = child->mutation_rate * child->size;
	for (int i = 0; i < loops; i++)
	{
		index = rand() % child->size;
		child->genes[index] = __gna_rand();
	}
	return 0;
}

int __gna_mate(struct Gna_Chromosome *pool, int parent1, int parent2, int dest)
{
	int separator = 0;
	int mutation_rate_int = 0;
	separator = rand() % pool[parent1].size;
	memcpy(pool[dest].genes, pool[parent1].genes, sizeof(double) * pool[parent1].size);

	// crossover process
	for (int i = 0; i < separator; i++)
	{
		pool[dest].genes[i] = pool[parent2].genes[i];
		__gna_mutation(pool + dest);
	}
	return 0;
}

//int __gna_crossover(struct Gna_Chromosome* pool, double pool_ratio);
double gna_denorm(double a_gene, double min, double max)
{
	return min + (max - min) * a_gene;
}

struct Gna_Chromosome *gna_create(int pool_size, int genes_size, double mutation_rate, int (*fitness_function)(struct Gna_Chromosome))
{
	srand(time(NULL));
	struct Gna_Chromosome *pool = (struct Gna_Chromosome *)malloc(sizeof(struct Gna_Chromosome) * pool_size);
	// error checking
	if(!pool) return NULL;
	
	for (int i = 0; i < pool_size; i++)
	{
		pool[i].genes = (double *)calloc(sizeof(double), genes_size);
		pool[i].rank = 0;
		pool[i].size = genes_size;
		pool[i].fitness_function = fitness_function;
		pool[i].mutation_rate = mutation_rate;
		//error checking
		if(!pool[i].genes)
		{
			gna_destroy(pool);
			return NULL;
		}

		for (int j = 0; j < genes_size; j++)
		{
			pool[i].genes[j] = __gna_rand();
		}
	}
	return pool;
}

int gna_destroy(struct Gna_Chromosome *pool)
{
	for (int i = 0; i < pool->size; i++)
	{
		free(pool[i].genes);
		pool[i].genes = NULL;
		pool[i].fitness_function = NULL;
	}
	free(pool);
	pool = NULL;
	return 0;
}

int gna_evolve(struct Gna_Chromosome *pool, int pool_size, double parent_child_ratio)
{
	int parent_size = 0;
	int parent1 = 0;
	int parent2 = 0;
	int child = 0;
	int loops = 0;
	parent_size = parent_child_ratio * pool_size;

	// selection/fitness calculation
	for (int i = 0; i < pool_size; i++)
	{
		pool[i].rank = pool[i].fitness_function(pool[i]);
	}
	// sort
	__gna_sort(pool, pool_size);
	// mate + mutate
	loops = pool_size - parent_size;
	for (int i = 0; i < loops; i++)
	{
		parent1 = __gna_rand_decimal(parent_size);
		parent2 = __gna_rand_decimal(parent_size);
		child = i + parent_size;
		__gna_mate(pool, parent1, parent2, child);
	}
	return 0;
}

//Example
/*
int target[4] = {5, 5, 5, 4};
int score(struct Gna_Chromosome chromosome)
{
	int a = (int)abs((int)gna_denorm(chromosome.genes[0], 1, 10) - target[0]);
	int b = (int)abs((int)gna_denorm(chromosome.genes[1], 1, 10) - target[1]);
	int c = (int)abs((int)gna_denorm(chromosome.genes[2], 1, 10) - target[2]);
	int d = (int)abs((int)gna_denorm(chromosome.genes[3], 1, 10) - target[3]);
	return 1000 - a - b - c - d;
}

int main(int argc, char *argv[])
{
	struct Gna_Chromosome *pool = gna_create(2000, 4, 0.1, score);
	printf("target: %d, %d, %d, %d\n", target[0], target[1], target[2], target[3]);
	printf("init genes: %1.1f, %1.1f, %1.1f, %1.1f\n",gna_denorm(pool[0].genes[0], 1, 10),gna_denorm( pool[0].genes[1], 1, 10),gna_denorm(pool[0].genes[2], 1, 10), gna_denorm(pool[0].genes[3], 1, 10));
		   
		   
	for (int i = 0; i < 1000; i++)
	{
		gna_evolve(pool, 2000, 0.5);
		printf("[%d] genes: %1.1f, %1.1f, %1.1f, %1.1f \n",
			   i,
			   gna_denorm(pool[0].genes[0], 1, 10),
			   gna_denorm(pool[0].genes[1], 1, 10),
			   gna_denorm(pool[0].genes[2], 1, 10),
			   gna_denorm(pool[0].genes[3], 1, 10));
	}
	gna_destroy(pool);
	return 0;
}
*/