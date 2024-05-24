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
	left = ((struct GNA_Body *)a)->rank;
	right = ((struct GNA_Body *)b)->rank;
	return right - left;
}

int __gna_sort(struct GNA_Body *pool, int pool_length)
{
	qsort(pool, pool_length, sizeof(pool[0]), __gna_qsort_comparator);
	return 0;
}

int __gna_mutation(struct GNA_Body *child)
{
	int index = 0;
	int loops = child->mutation_rate * child->length;
	for (int i = 0; i < loops; i++)
	{
		index = rand() % child->length;
		child->properties[index] = __gna_rand();
	}
	return 0;
}

int __gna_mate(struct GNA_Body *pool, int parent1, int parent2, int dest)
{
	int separator = 0;
	int mutation_rate_int = 0;
	separator = rand() % pool[parent1].length;
	memcpy(pool[dest].properties, pool[parent1].properties, sizeof(double) * pool[parent1].length);

	// crossover process
	for (int i = 0; i < separator; i++)
	{
		pool[dest].properties[i] = pool[parent2].properties[i];
		__gna_mutation(pool + dest);
	}
	return 0;
}

//int __gna_crossover(struct GNA_Body* pool, double pool_ratio);
double gna_scale(double min, double max, double property)
{
	return min + (max - min) * property;
}

struct GNA_Body *gna_init(int pool_length, int body_length, double mutation_rate, int (*fitness_function)(struct GNA_Body))
{
	srand(time(NULL));
	struct GNA_Body *pool = (struct GNA_Body *)malloc(sizeof(struct GNA_Body) * pool_length);
	for (int i = 0; i < pool_length; i++)
	{
		pool[i].properties = (double *)calloc(sizeof(double), body_length);
		pool[i].rank = 0;
		pool[i].length = body_length;
		pool[i].fitness_function = fitness_function;
		pool[i].mutation_rate = mutation_rate;

		for (int j = 0; j < body_length; j++)
		{
			pool[i].properties[j] = __gna_rand();
		}
	}
	return pool;
}

int gna_destroy(struct GNA_Body *pool)
{
	for (int i = 0; i < pool->length; i++)
	{
		free(pool[i].properties);
		pool[i].properties = NULL;
		pool[i].fitness_function = NULL;
	}
	free(pool);
	pool = NULL;
	return 0;
}

int gna_evolve(struct GNA_Body *pool, int pool_length, double parent_child_ratio)
{
	int parent_size = 0;
	int parent1 = 0;
	int parent2 = 0;
	int child = 0;
	int loops = 0;
	parent_size = parent_child_ratio * pool_length;

	// selection/fitness calculation
	for (int i = 0; i < pool_length; i++)
	{
		pool[i].rank = pool[i].fitness_function(pool[i]);
	}
	// sort
	__gna_sort(pool, pool_length);
	// mate + mutate
	loops = pool_length - parent_size;
	for (int i = 0; i < loops; i++)
	{
		parent1 = __gna_rand_decimal(parent_size);
		parent2 = __gna_rand_decimal(parent_size);
		child = i + parent_size;
		__gna_mate(pool, parent1, parent2, child);
	}
	return 0;
}

/*
int target[4] = {5, 4, 1, 4};
int score(struct GNA_Body chromosome)
{
	int a = (int)abs((int)gna_scale(1, 10, chromosome.properties[0]) - target[0]);
	int b = (int)abs((int)gna_scale(1, 10, chromosome.properties[1]) - target[1]);
	int c = (int)abs((int)gna_scale(1, 10, chromosome.properties[2]) - target[2]);
	int d = (int)abs((int)gna_scale(1, 10, chromosome.properties[3]) - target[3]);
	return 1000 - a - b - c - d;
}


int main(int argc, char *argv[])
{
	struct GNA_Body *pool = gna_init(2000, 4, 0.1, score);
	printf("target: %d, %d, %d, %d\n", target[0], target[1], target[2], target[3]);
	printf("init genes: %1.1f, %1.1f, %1.1f, %1.1f\n",
		   gna_scale(1, 10, pool[0].properties[0]),
		   gna_scale(1, 10, pool[0].properties[1]),
		   gna_scale(1, 10, pool[0].properties[2]),
		   gna_scale(1, 10, pool[0].properties[3]));
	for (int i = 0; i < 20; i++)
	{
		gna_evolve(pool, 2000, 0.5);
		printf("[%d] genes: %1.1f, %1.1f, %1.1f, %1.1f \n",
			   i,
			   gna_scale(1, 10, pool[0].properties[0]),
			   gna_scale(1, 10, pool[0].properties[1]),
			   gna_scale(1, 10, pool[0].properties[2]),
			   gna_scale(1, 10, pool[0].properties[3]));
	}
	gna_destroy(pool);
	return 0;
}
*/