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
	if(!_vct)
	{
		return;
	}
	
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
	if(_offset < 0)
	{
		_offset += _vct->len;
	}
	VCT_THROW(_offset < 0 || _offset >= _vct->len, VCT_OUT_OF_RANGE, 0);
	*_err = VCT_OK;
	return _vct->begin + _offset * _vct->size;
}

size_t vct_length(const Vct* _vct)
{
	if(!_vct)
	{
		return 0;
	}
	return _vct->len;
}

static unsigned char vct_realloc(Vct* _vct, const size_t _cap, VCT_ERR* _err)
{
	char* tmp = realloc(_vct, _cap * _vct->size);
	VCT_THROW(!tmp, VCT_OUT_OF_MEMORY, 1);
	_vct->begin = tmp;
	_vct->cap = _cap;
	return 0;
}

static unsigned char vct_shrink_to_fit(Vct* _vct, VCT_ERR* _err)
{
	size_t cap = _vct->cap;
	while(cap >= VCT_CAP_ROOT * _vct->len)
	{
		cap /= VCT_CAP_ROOT;
	}
	if(cap == _vct->cap)
	{
		return 0;
	}
	return vct_realloc(_vct, cap, _err);
}

static unsigned char vct_reserve(Vct* _vct, const size_t _cap, VCT_ERR* _err)
{
	if(_cap <= _vct->cap)
	{
		return 0;
	}
	
	size_t cap = _vct->cap;
	while(cap < _cap)
	{
		cap *= VCT_CAP_ROOT;
	}
	return vct_realloc(_vct, cap, _err);
}

Vct* vct_resize(Vct* _vct, const size_t _len, VCT_ERR* _err)
{
	if(_vct->len == _len)
	{
		return _vct;
	}
	
	VCT_THROW(vct_reserve(_vct, _len, _err), *_err, _vct);
	
	for(size_t i = _vct->len * _vct->size; i < _len * _vct->size; ++i)
	{
		_vct->begin[i] = 0;
	}
	_vct->len = _len;
	
	return _vct;
}

Vct* vct_push_back(Vct* _vct, const char *_elem, VCT_ERR* _err)
{
	vct_resize(_vct, _vct->len + 1, _err);
	if(*_err)
	{
		return _vct;
	}
	
	for(size_t i = 0; i < _vct->size; ++i)
	{
		*(_vct->begin + (_vct->len - 1) * _vct->size + i) = *(_elem + i);
	}
	
	return _vct;
}

void vct_pop_back(Vct *_vct, char *_elem, VCT_ERR* _err)
{
	if(_vct->len == 0)
	{
		for(size_t i = 0; i < _vct->size; ++i)
		{
			_elem[i] = 0;
		}
		return;
	}
	_vct->len -= 1;
	for(size_t i = 0; i < _vct->size; ++i)
	{
		_elem[i] = _vct->begin[_vct->len * _vct->size + i];
	}
}


VctIterator* vct_iterator(const Vct* _vct, const VCT_ITERATOR_TYPE _type, VCT_ERR* _err)
{
	VctIterator* ret = malloc(sizeof(*ret));
	VCT_THROW(!ret, VCT_OUT_OF_MEMORY, 0);
	ret->vct = _vct;
	ret->ended = (_vct->len == 0);
	switch(ret->direction = _type)
	{
	case VCT_ITERATE_UP:
		ret->offset = 0;
		break;
	case VCT_ITERATE_DOWN:
		ret->offset = _vct->len - 1;
		break;
	}
	*_err = VCT_OK;
	return ret;
}

void* vct_iterate(VctIterator* _it)
{
	if(_it->ended)
	{
		return 0;
	}
	void* ret = _it->vct->begin + _it->offset * _it->vct->size;
	switch(_it->direction)
	{
	case VCT_ITERATE_UP:
		if(++(_it->offset) >= _it->vct->len)
		{
			_it->ended = 1;
		}
		break;
	case VCT_ITERATE_DOWN:
		if(_it->offset == 0)
		{
			_it->ended = 1;
		}
		else
		{
			--_it->offset;
		}
		break;
	}
	return ret;
}