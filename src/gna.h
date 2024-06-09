#include "stdlib.h"
#include "time.h"
#include "string.h" //memcpy

struct Gna_Chromosome
{
	double *genes;
	int size;
	int rank;
	double mutation_rate;
	int (*fitness_function)(struct Gna_Chromosome);
};

double __gna_rand();
int __gna_rand_decimal(int max);
int __gna_qsort_comparator(const void *a, const void *b);
int __gna_sort(struct Gna_Chromosome *pool, int pool_size);
int __gna_mutation(struct Gna_Chromosome *child);
int __gna_mate(struct Gna_Chromosome *pool, int parent1, int parent2, int dest);
double gna_denorm(double a_gene, double min, double max);
struct Gna_Chromosome *gna_create(int pool_size, int genes_size, double mutation_rate, int (*fitness_function)(struct Gna_Chromosome));
int gna_destroy(struct Gna_Chromosome *pool);
int gna_evolve(struct Gna_Chromosome *pool, int pool_size, double parent_child_ratio);