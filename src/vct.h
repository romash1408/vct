#ifndef VCT_H
#define VCT_H

#include <stdlib.h>

#define VCT_THROW($BOOL, $ERR, $RET) \
if($BOOL){ \
	*_err = $ERR; \
	return $RET; \
}

typedef enum{
	VCT_OK = 0,
	VCT_OUT_OF_MEMORY,
	VCT_BAD_SIZE,
	VCT_BAD_LENGTH
} VCT_ERR;

typedef struct{
	char* begin;
	int size, len, cap;
} Vct;

Vct* vct_new(int _size, int _len, VCT_ERR *_err);
void vct_free(Vct** _vct);
Vct* vct_copy(Vct* _src, VCT_ERR *_err);

#endif