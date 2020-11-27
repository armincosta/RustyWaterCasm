
/** RustyWaterCasm.dll

   This library can be used freely to render water effects efficiently

   Author: Armin Costa
   e-mail: armincosta@hotmail.com
   
#   
# Copyright (C) 2005, 2008 Armin Costa
# This file is part of RustyWaterCasm
#
# RustyWaterCasm is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Kent_display_serial_protocol_25016 is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License version 3
*/
#include <iostream.h>
#include <stdlib.h>
#include <stdio.h>
#include <dos.h>
#include <Math.h>

#ifdef RUSTYWATERCASM_EXPORTS
#define RUSTYWATERCASM_API __declspec(dllexport)
#else
#define RUSTYWATERCASM_API __declspec(dllimport)
#endif

// This class is exported from the RustyWaterCasm.dll
class RUSTYWATERCASM_API CRustyWaterCasm {
public:
	CRustyWaterCasm(void);
	// TODO: add your methods here.
};

extern RUSTYWATERCASM_API int nRustyWaterCasm;



RUSTYWATERCASM_API void filterMap(int, int);
RUSTYWATERCASM_API void genTexture();
int controlCol(int);
RUSTYWATERCASM_API void addBlob(int, int, int, int);
RUSTYWATERCASM_API void addDrop(int,int,int);
RUSTYWATERCASM_API int fnRustyWaterCasm(void);

