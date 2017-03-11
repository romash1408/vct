#ifndef VCT_H
#define VCT_H

#include <stdlib.h>

#define VCT_THROW($BOOL, $ERR, $RET) \
if($BOOL){ \
	*_err = $ERR; \
	return $RET; \
}

#define VCT_AT($VCT, $OFFSET, $TYPE, $ERR) (($TYPE *)vct_at(($VCT), ($OFFSET), ($ERR)))

typedef enum{
	VCT_CAP_ROOT = 3,
} VCT_CONST;

typedef enum{
	VCT_OK = 0,
	VCT_OUT_OF_MEMORY = 1,
	VCT_BAD_SIZE = 2,
	VCT_OUT_OF_RANGE = 3,
} VCT_ERR;

typedef struct{
	char* begin;
	size_t size, len, cap;
} Vct;

Vct* vct_new(const size_t _len, const size_t _size, VCT_ERR *_err);
void vct_free(Vct* _vct);
Vct* vct_copy(const Vct* _src, VCT_ERR *_err);
void* vct_at(const Vct* _vct, int _offset, VCT_ERR *_err);
size_t vct_length(const Vct* _vct);

#endif