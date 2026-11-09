/*
===========================================================================

Doom 3 GPL Source Code
Copyright (C) 1999-2011 id Software LLC, a ZeniMax Media company.

This file is part of the Doom 3 GPL Source Code ("Doom 3 Source Code").

Doom 3 Source Code is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Doom 3 Source Code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Doom 3 Source Code.  If not, see <http://www.gnu.org/licenses/>.

===========================================================================
*/

#ifndef __MATH_SIMD_REVENIR_H__
#define __MATH_SIMD_REVENIR_H__

#include "idlib/math/Simd_Generic.h"

/*
===============================================================================

	revenir's host SIMD.

	Under revenir (IRIX programs as host processes), syssgi's command
	REVENIR_VEC runs vector operations over arrays in the program's
	memory with the host CPU's own SIMD (NEON, SSE, AVX), chosen by
	revenir from what the host has. This processor hands the generic
	code's hot spots to it: plane distances, comparisons, bounds. Short
	arrays, and anything the door does not take, stay generic. Elsewhere
	(real IRIX, another system) Available() is false and it is not used.

===============================================================================
*/

class idSIMD_Revenir : public idSIMD_Generic {
public:
	static bool			Available( void );

	virtual const char * VPCALL GetName( void ) const;

	virtual void VPCALL Dot( float *dst,			const idVec3 &constant,	const idPlane *src,		const int count );
	virtual void VPCALL Dot( float *dst,			const idPlane &constant,const idDrawVert *src,	const int count );

	virtual void VPCALL CmpGT( byte *dst,			const float *src0,		const float constant,	const int count );
	virtual void VPCALL CmpGT( byte *dst,			const byte bitNum,		const float *src0,		const float constant,	const int count );
	virtual void VPCALL CmpGE( byte *dst,			const float *src0,		const float constant,	const int count );
	virtual void VPCALL CmpGE( byte *dst,			const byte bitNum,		const float *src0,		const float constant,	const int count );
	virtual void VPCALL CmpLT( byte *dst,			const float *src0,		const float constant,	const int count );
	virtual void VPCALL CmpLT( byte *dst,			const byte bitNum,		const float *src0,		const float constant,	const int count );
	virtual void VPCALL CmpLE( byte *dst,			const float *src0,		const float constant,	const int count );
	virtual void VPCALL CmpLE( byte *dst,			const byte bitNum,		const float *src0,		const float constant,	const int count );

	virtual void VPCALL MinMax( idVec3 &min,		idVec3 &max,			const idVec3 *src,		const int count );
	virtual	void VPCALL MinMax( idVec3 &min,		idVec3 &max,			const idDrawVert *src,	const int count );
	virtual	void VPCALL MinMax( idVec3 &min,		idVec3 &max,			const idDrawVert *src,	const int *indexes,		const int count );
};

#endif /* !__MATH_SIMD_REVENIR_H__ */
