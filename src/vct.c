#include "vct.h"

Vct* vct_new(const size_t _len, const size_t _size, VCT_ERR *_err)
{
	VCT_THROW(_size == 0, VCT_BAD_SIZE, 0);
	
	Vct* ret = malloc(sizeof(*ret));
	VCT_THROW(!ret, VCT_OUT_OF_MEMORY, 0);
	
	*ret = (Vct){.size = _size, .len = _len, .cap = VCT_CAP_ROOT};
	while(ret->cap < ret->len)
	{
		ret->cap *= VCT_CAP_ROOT;
	}
	
	ret->begin = malloc(ret->cap * ret->size);
	VCT_THROW(!ret->begin, VCT_OUT_OF_MEMORY; free(ret), 0);
	
	*_err = VCT_OK;
	return ret;
}

void vct_free(Vct* _vct)
{
	if(!_vct) return;
	
	if(_vct->begin) 
	{
		free(_vct->begin);
	}
	free(_vct);
}

Vct* vct_copy(const Vct* _src, VCT_ERR *_err)
{
	Vct* ret = malloc(sizeof(*ret));
	VCT_THROW(!ret, VCT_OUT_OF_MEMORY, 0);
	
	*ret = (Vct){.size = _src->size, .len = _src->len, .cap = _src->cap};
	
	ret->begin = malloc(ret->cap * ret->size);
	VCT_THROW(!ret->begin, VCT_OUT_OF_MEMORY; free(ret), 0);
	
	for(int i = 0; i < _src->len * _src->size; ++i)
	{
		ret->begin[i] = _src->begin[i];
	}
	
	*_err = VCT_OK;
	return ret;
}

void* vct_at(const Vct* _vct, int _offset, VCT_ERR *_err)
{
	if(_offset < 0) _offset += _vct->len;
	VCT_THROW(_offset < 0 || _offset >= _vct->len, VCT_OUT_OF_RANGE, 0);
	*_err = VCT_OK;
	return _vct->begin + _offset * _vct->size;
}

size_t vct_length(const Vct* _vct)
{
	if(!_vct) return 0;
	return _vct->len;
}