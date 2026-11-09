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

#include "sys/platform.h"
#include "idlib/geometry/DrawVert.h"
#include "idlib/math/Plane.h"

#include "idlib/math/Simd_Revenir.h"

#ifdef __sgi
#include <sys/syssgi.h>

// revenir's math door (its vecmath.rs): syssgi( REVENIR_VEC, op, ... ).
#define REVENIR_VEC				0x72766563
#define RV_PROBE				0
#define RV_DOT_PLANE			1
#define RV_DOT_POINT_PLANES		2
#define RV_CMP					3
#define RV_MINMAX				4
#define RV_LT					0
#define RV_LE					1
#define RV_GT					2
#define RV_GE					3
#define RV_OR_BIT				( 1 << 8 )
#define RV_NEED					( ( 1 << RV_DOT_PLANE ) | ( 1 << RV_DOT_POINT_PLANES ) | ( 1 << RV_CMP ) | ( 1 << RV_MINMAX ) )

// Below this many elements a call costs more than the generic loop saves.
#define RV_MIN					16

#define RV( ... )				( syssgi( REVENIR_VEC, __VA_ARGS__ ) != -1 )
#endif

/*
============
idSIMD_Revenir::Available

  The door there, with every operation used here.
============
*/
bool idSIMD_Revenir::Available( void ) {
#ifdef __sgi
	long probe = (long)syssgi( REVENIR_VEC, RV_PROBE );
	return probe != -1 && ( probe & RV_NEED ) == RV_NEED;
#else
	return false;
#endif
}

const char * idSIMD_Revenir::GetName( void ) const {
	return "revenir host SIMD";
}

#ifdef __sgi

void VPCALL idSIMD_Revenir::Dot( float *dst, const idVec3 &constant, const idPlane *src, const int count ) {
	if ( count < RV_MIN || !RV( RV_DOT_POINT_PLANES, dst, &constant, src, (int)sizeof( idPlane ), count ) ) {
		idSIMD_Generic::Dot( dst, constant, src, count );
	}
}

void VPCALL idSIMD_Revenir::Dot( float *dst, const idPlane &constant, const idDrawVert *src, const int count ) {
	if ( count < RV_MIN || !RV( RV_DOT_PLANE, dst, &constant, src, (int)sizeof( idDrawVert ), count ) ) {
		idSIMD_Generic::Dot( dst, constant, src, count );
	}
}

#define RV_CMP_SET( NAME, HOW ) \
void VPCALL idSIMD_Revenir::NAME( byte *dst, const float *src0, const float constant, const int count ) { \
	if ( count < RV_MIN || !RV( RV_CMP, dst, src0, &constant, count, HOW ) ) { \
		idSIMD_Generic::NAME( dst, src0, constant, count ); \
	} \
} \
void VPCALL idSIMD_Revenir::NAME( byte *dst, const byte bitNum, const float *src0, const float constant, const int count ) { \
	if ( count < RV_MIN || bitNum > 7 || !RV( RV_CMP, dst, src0, &constant, count, HOW | RV_OR_BIT | ( bitNum << 16 ) ) ) { \
		idSIMD_Generic::NAME( dst, bitNum, src0, constant, count ); \
	} \
}

RV_CMP_SET( CmpGT, RV_GT )
RV_CMP_SET( CmpGE, RV_GE )
RV_CMP_SET( CmpLT, RV_LT )
RV_CMP_SET( CmpLE, RV_LE )

/*
============
idSIMD_Revenir::MinMax

  The door starts from +/- infinity where the generic code starts from
  +/- idMath::INFINITY; with RV_MIN or more finite elements the answer is
  the same.
============
*/
static bool RV_MinMax( idVec3 &min, idVec3 &max, const void *src, int stride, const int *indexes, const int count ) {
	float out[6];

	if ( count < RV_MIN || !RV( RV_MINMAX, out, src, stride, indexes, count ) ) {
		return false;
	}
	min.Set( out[0], out[1], out[2] );
	max.Set( out[3], out[4], out[5] );
	return true;
}

void VPCALL idSIMD_Revenir::MinMax( idVec3 &min, idVec3 &max, const idVec3 *src, const int count ) {
	if ( !RV_MinMax( min, max, src, (int)sizeof( idVec3 ), NULL, count ) ) {
		idSIMD_Generic::MinMax( min, max, src, count );
	}
}

void VPCALL idSIMD_Revenir::MinMax( idVec3 &min, idVec3 &max, const idDrawVert *src, const int count ) {
	if ( !RV_MinMax( min, max, src, (int)sizeof( idDrawVert ), NULL, count ) ) {
		idSIMD_Generic::MinMax( min, max, src, count );
	}
}

void VPCALL idSIMD_Revenir::MinMax( idVec3 &min, idVec3 &max, const idDrawVert *src, const int *indexes, const int count ) {
	if ( !RV_MinMax( min, max, src, (int)sizeof( idDrawVert ), indexes, count ) ) {
		idSIMD_Generic::MinMax( min, max, src, indexes, count );
	}
}

#else

// Not IRIX: never chosen (Available() is false); the generic code throughout.
void VPCALL idSIMD_Revenir::Dot( float *dst, const idVec3 &constant, const idPlane *src, const int count ) { idSIMD_Generic::Dot( dst, constant, src, count ); }
void VPCALL idSIMD_Revenir::Dot( float *dst, const idPlane &constant, const idDrawVert *src, const int count ) { idSIMD_Generic::Dot( dst, constant, src, count ); }
void VPCALL idSIMD_Revenir::CmpGT( byte *dst, const float *src0, const float constant, const int count ) { idSIMD_Generic::CmpGT( dst, src0, constant, count ); }
void VPCALL idSIMD_Revenir::CmpGT( byte *dst, const byte bitNum, const float *src0, const float constant, const int count ) { idSIMD_Generic::CmpGT( dst, bitNum, src0, constant, count ); }
void VPCALL idSIMD_Revenir::CmpGE( byte *dst, const float *src0, const float constant, const int count ) { idSIMD_Generic::CmpGE( dst, src0, constant, count ); }
void VPCALL idSIMD_Revenir::CmpGE( byte *dst, const byte bitNum, const float *src0, const float constant, const int count ) { idSIMD_Generic::CmpGE( dst, bitNum, src0, constant, count ); }
void VPCALL idSIMD_Revenir::CmpLT( byte *dst, const float *src0, const float constant, const int count ) { idSIMD_Generic::CmpLT( dst, src0, constant, count ); }
void VPCALL idSIMD_Revenir::CmpLT( byte *dst, const byte bitNum, const float *src0, const float constant, const int count ) { idSIMD_Generic::CmpLT( dst, bitNum, src0, constant, count ); }
void VPCALL idSIMD_Revenir::CmpLE( byte *dst, const float *src0, const float constant, const int count ) { idSIMD_Generic::CmpLE( dst, src0, constant, count ); }
void VPCALL idSIMD_Revenir::CmpLE( byte *dst, const byte bitNum, const float *src0, const float constant, const int count ) { idSIMD_Generic::CmpLE( dst, bitNum, src0, constant, count ); }
void VPCALL idSIMD_Revenir::MinMax( idVec3 &min, idVec3 &max, const idVec3 *src, const int count ) { idSIMD_Generic::MinMax( min, max, src, count ); }
void VPCALL idSIMD_Revenir::MinMax( idVec3 &min, idVec3 &max, const idDrawVert *src, const int count ) { idSIMD_Generic::MinMax( min, max, src, count ); }
void VPCALL idSIMD_Revenir::MinMax( idVec3 &min, idVec3 &max, const idDrawVert *src, const int *indexes, const int count ) { idSIMD_Generic::MinMax( min, max, src, indexes, count ); }

#endif
