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
	return 0;
}