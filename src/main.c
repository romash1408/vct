#include <stdio.h>
#include "vct.h"

#define VCT_ERR_VERIFY(err_code) \
	if((err_code)) \
	{ \
		fprintf(stderr, "Vct error code %d when create\n", (err_code)); \
		return (err_code); \
	} 

int main()
{
	const int n = 10;
	
	//----------TEST1----------
	printf("TEST1: testing vct_new, vct_length, vct_at and vct_copy: ");
	
	VCT_ERR vct_err;
	Vct *v = vct_new(n, sizeof(int), &vct_err);
	VCT_ERR_VERIFY(vct_err);
	for(size_t i = 0; i < vct_length(v); ++i)
	{
		*VCT_AT(v, i, int, &vct_err) = n - i;
		VCT_ERR_VERIFY(vct_err);
	}
	*VCT_AT(v, -1, int, &vct_err) = 11;
	VCT_ERR_VERIFY(vct_err);
	*VCT_AT(v, -n, int, &vct_err) = -11;
	VCT_ERR_VERIFY(vct_err);
	
	Vct *v2 = vct_copy(v, &vct_err);
	VCT_ERR_VERIFY(vct_err);
	
	for(size_t i = vct_length(v2); i-- > 0;)
	{
		printf("%d ", *VCT_AT(v2, i, int, &vct_err));
		VCT_ERR_VERIFY(vct_err);
	}
	printf("TEST1 OK!\n");
	
	vct_free(v); v = 0;
	vct_free(v2); v2 = 0;
	
	//----------TEST2----------
	printf("\nTEST2: testing vct_iterator and vct_iterate: ");
	v = vct_new(n, sizeof(float), &vct_err);
	VCT_ERR_VERIFY(vct_err);
	
	VctIterator *v_i = vct_iterator(v, VCT_ITERATE_UP, &vct_err);
	VCT_ERR_VERIFY(vct_err);
	
	float *next = 0;
	int i = 0;
	while((next = vct_iterate(v_i)))
	{
		*next = 1.0 / ++i; 
	}
	free(v_i);
	
	v_i = vct_iterator(v, VCT_ITERATE_DOWN, &vct_err);
	VCT_ERR_VERIFY(vct_err);
	
	while((next = vct_iterate(v_i)))
	{
		printf("%.3f ", *next);
	}
	free(v_i);
	printf("TEST2 OK!\n");
	
	//----------TEST3----------
	printf("\nTEST3: testing vct_push_back and vct_pop_back: ");
	v_i = vct_iterator(v, VCT_ITERATE_DOWN, &vct_err);
	VCT_ERR_VERIFY(vct_err);
	
	while((next = vct_iterate(v_i)))
	{
		vct_push_back(v, (const char*)next, &vct_err);
		VCT_ERR_VERIFY(vct_err);
	}
	free(v_i);
	
	next = malloc(sizeof(*next));
	while(vct_length(v))
	{
		vct_pop_back(v, (char*)next, &vct_err);
		VCT_ERR_VERIFY(vct_err);
		printf("%.3f ", *next);
	}
	
	*next = 1.0f/3.0f;
	vct_push_back(v, (const char*)next, &vct_err);
	VCT_ERR_VERIFY(vct_err);
	free(next);
	
	printf("\n");
	vct_resize(v, 3, &vct_err);
	VCT_ERR_VERIFY(vct_err);
	for(size_t i = 0; i < vct_length(v); ++i)
	{
		next = VCT_AT(v, i, float, &vct_err);
		VCT_ERR_VERIFY(vct_err);
		printf("%.3f ", *next);
	}
	vct_free(v);
	printf("\nTEST3 OK!\n");
	return 0;
}