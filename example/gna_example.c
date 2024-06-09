/**
* What this program do is to try to replicate the content of "target[4] = {5, 5, 5, 4};" using genetic algorithm 
**/

#include "gna.h"

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