#include "stdlib.h"
#include "time.h"
#include "string.h" //memcpy

struct GNA_Body
{
	double *properties;
	int length;
	int rank;
	double mutation_rate;
	int (*fitness_function)(struct GNA_Body);
};

double __gna_rand();
int __gna_rand_decimal(int max);
int __gna_qsort_comparator(const void *a, const void *b);
int __gna_sort(struct GNA_Body *pool, int pool_length);
int __gna_mutation(struct GNA_Body *child);
int __gna_mate(struct GNA_Body *pool, int parent1, int parent2, int dest);
double gna_scale(double min, double max, double property);
struct GNA_Body *gna_init(int pool_length, int body_length, double mutation_rate, int (*fitness_function)(struct GNA_Body));
int gna_destroy(struct GNA_Body *pool);
int gna_evolve(struct GNA_Body *pool, int pool_length, double parent_child_ratio);