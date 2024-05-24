#include "gna.h"

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