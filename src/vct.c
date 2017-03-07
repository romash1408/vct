#include "vct.h"

Vct* vct_new(int _size, int _len, VCT_ERR *_err)
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
	VCT_THROW(ret->begin, VCT_OUT_OF_MEMORY; free(ret), 0);
	
	return ret;
}

void vct_free(Vct** _vct)
{
	free((*_vct)->begin);
	free(*_vct);
	*_vct = 0;
}

Vct* vct_copy(Vct* _src, VCT_ERR *_err)
{
	Vct* ret = malloc(sizeof(*ret));
	VCT_THROW(!ret, VCT_OUT_OF_MEMORY, 0);
	
	*ret = (Vct){.size = _src->size, .len = _src->len, .cap = _src->cap};
	
	ret->begin = malloc(ret->cap * ret->size);
	VCT_THROW(ret->begin, VCT_OUT_OF_MEMORY; free(ret), 0);
	
	for(int i = 0; i < _src->len * _src->size; ++i)
	{
		ret->begin[i] = _src->begin[i];
	}
	
	return ret;
}

void* vct_at(Vct* _vct, int _offset, VCT_ERR *_err)
{
	if(_offset < 0) _offset += _vct;
	VCT_THROW(_offset < 0 || _offset >= _vct->len, VCT_OUT_OF_RANGE, 0);
	return _vct->begin + _offset;
}