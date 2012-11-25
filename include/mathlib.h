/*
Copyright (C) 1996-1997 Id Software, Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#ifndef MATHLIB_H
#define MATHLIB_H

#include <limits.h>

// mathlib.h

typedef float vec_t;
typedef vec_t vec3_t[3];
typedef vec_t vec5_t[5];

typedef int fixed4_t;
typedef int fixed8_t;
typedef int fixed16_t;
#define FIXED16_MAX INT_MAX;

/* min and max macros with type checking */
#define qmax(a,b) ({       \
    typeof(a) a_ = (a);   \
    typeof(b) b_ = (b);   \
    (void)(&a_ == &b_);   \
    (a_ > b_) ? a_ : b_;  \
})
#define qmin(a,b) ({       \
    typeof(a) a_ = (a);   \
    typeof(b) b_ = (b);   \
    (void)(&a_ == &b_);   \
    (a_ < b_) ? a_ : b_;  \
})

/* clamp macro with type checking */
#define qclamp(var,min,max) qmax(qmin(var,max),min)

#ifndef M_PI
#define M_PI 3.14159265358979323846	// matches value in gcc v2 math.h
#endif

struct mplane_s;

extern vec3_t vec3_origin;
extern int nanmask;

#define	IS_NAN(x) ({ \
	int tmp;			\
	memcpy(&tmp, &x, sizeof(int));	\
	((tmp & nanmask) == nanmask);	\
})

#define DotProduct(x,y) (x[0]*y[0]+x[1]*y[1]+x[2]*y[2])
#define VectorSubtract(a,b,c) {c[0]=a[0]-b[0];c[1]=a[1]-b[1];c[2]=a[2]-b[2];}
#define VectorAdd(a,b,c) {c[0]=a[0]+b[0];c[1]=a[1]+b[1];c[2]=a[2]+b[2];}
#define VectorCopy(a,b) {b[0]=a[0];b[1]=a[1];b[2]=a[2];}

void VectorMA(const vec3_t veca, const float scale, const vec3_t vecb,
	      vec3_t vecc);

vec_t _DotProduct(vec3_t v1, vec3_t v2);
void _VectorSubtract(vec3_t veca, vec3_t vecb, vec3_t out);
void _VectorAdd(vec3_t veca, vec3_t vecb, vec3_t out);
void _VectorCopy(vec3_t in, vec3_t out);

int VectorCompare(vec3_t v1, vec3_t v2);
vec_t Length(vec3_t v);
void CrossProduct(const vec3_t v1, const vec3_t v2, vec3_t cross);
float VectorNormalize(vec3_t v);	// returns vector length
void VectorInverse(vec3_t v);
void VectorScale(const vec3_t in, const vec_t scale, vec3_t out);
int Q_log2(int val);

void R_ConcatRotations(float in1[3][3], float in2[3][3], float out[3][3]);
void R_ConcatTransforms(float in1[3][4], float in2[3][4], float out[3][4]);

void FloorDivMod(double numer, double denom, int *quotient, int *rem);
fixed16_t Invert24To16(fixed16_t val);
int GreatestCommonDivisor(int i1, int i2);

void AngleVectors(const vec3_t angles, vec3_t forward, vec3_t right, vec3_t up);
int BoxOnPlaneSide(vec3_t emins, vec3_t emaxs, struct mplane_s *plane);
float anglemod(float a);

#define BOX_ON_PLANE_SIDE(emins, emaxs, p)			\
	(((p)->type < 3)?					\
	(							\
		((p)->dist <= (emins)[(p)->type])?		\
			1					\
		:						\
		(						\
			((p)->dist >= (emaxs)[(p)->type])?	\
				2				\
			:					\
				3				\
		)						\
	)							\
	:							\
		BoxOnPlaneSide( (emins), (emaxs), (p)))

#ifdef QW_HACK
fixed16_t Mul16_30(fixed16_t multiplier, fixed16_t multiplicand);
#endif
void RotatePointAroundVector(vec3_t dst, const vec3_t dir,
			     const vec3_t point, float degrees);



#endif /* MATHLIB_H */
