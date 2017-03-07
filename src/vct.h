#ifndef VCT_H
#define VCT_H

#include <stdlib.h>

#define VCT_THROW($BOOL, $ERR, $RET) \
if($BOOL){ \
	*err = $ERR; \
	return $RET; \
}

typedef enum{
	VCT_OK: 0,
	VCT_OUT_OF_MEMORY: 1
} VCT_ERR;

typedef struct{
	char* begin;
	int size, len, cap;
} Vct;

Vct* vct_create(int _size, int _len, VctErr *_err);
void vct_delete(Vct** _vct);

#endif