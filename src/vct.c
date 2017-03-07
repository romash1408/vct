#include "vct.h"

Vct* vct_create(int _size, int _len, VCT_ERR *_err)
{
	
	VCT_THROW(_size <= 0, VCT_BAD_SIZE, 0);
	VCT_THROW(_len <= 0, VCT_BAD_SIZE, 0);
	
	Vct* ret = malloc(sizeof(*ret));
	VCT_THROW(!ret, VCT_OUT_OF_MEMORY, 0);
	
	*ret = (Vct){.size = _size, .len = _len, .cap = 3};
	while(ret->cap < ret->len)
	{
		ret->cap *= 3;
	}
	
	ret->begin = malloc(ret->cap * ret->size);
	VCT_THROW(ret->begin, VCT_OUT_OF_MEMORY, 0);
	
	return ret;
}

void vct_delete(Vct** _vct)
{
	free((*_vct)->begin);
	free(*_vct);
	*_vct = 0;
}