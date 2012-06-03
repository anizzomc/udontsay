/* io.h */

#ifndef __ARCH_IO_H_
#define __ARCH_IO_H_

#include "types.h"

void	_out(dword port, dword value);
dword	_in(dword port);

#endif
