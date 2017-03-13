#include <stdio.h>
#include "vct.h"

int main()
{
	const int n = 10;
	VCT_ERR vct_err;
	Vct *v = vct_new(n, sizeof(int), &vct_err);
	if(vct_err)
	{
		fprintf(stderr, "Vct error code %d when create\n", vct_err);
		return vct_err;
	}
	
	printf("TEST1: testing vct_new, vct_length, vct_at and vct_copy: ");
	for(size_t i = 0; i < vct_length(v); ++i)
	{
		*VCT_AT(v, i, int, &vct_err) = n - i;
	}
	
	Vct *v2 = vct_copy(v, &vct_err);
	if(vct_err)
	{
		fprintf(stderr, "Vct error code %d when copy\n", vct_err);
		return vct_err;
	}
	
	for(size_t i = vct_length(v); i-- > 0;)
	{
		printf("%d ", *VCT_AT(v, i, int, &vct_err));
	}
	printf("TEST1 OK!\n");
	
	vct_free(v); v = 0;
	vct_free(v2); v2 = 0;
	
	printf("\nTEST2: testing vct_iterator and vct_iterate: ");
	v = vct_new(n, sizeof(float), &vct_err);
	if(vct_err)
	{
		fprintf(stderr, "Vct error code %d when create-2\n", vct_err);
		return vct_err;
	}
	
	VctIterator *v_i = vct_iterator(v, VCT_ITERATE_UP);
	float *next = 0;
	int i = 0;
	while(next = vct_iterate(v_i))
	{
		*next = 1.0 / ++i; 
	}
	free(v_i);
	
	v_i = vct_iterator(v, VCT_ETARATE_DOWN);
	while(next = vct_iterate(v_i))
	{
		printf("%.3f ", *next);
	}
	free(v_i);
	printf("TEST2 OK!\n");
	return 0;
}