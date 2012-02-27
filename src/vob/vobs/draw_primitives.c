
#include "lob/api.h"
#include "lob/components/drawing_primitives.h"
#include "vob/vobs.h"
#include "vob/coords.h"


// -------------------------------------------
// Color
// -------------------------------------------

VobColor *vob_color(Region *reg, float r, float g, float b)
{
	VobColor *ret = REGION(reg, "vob.primitive.Color", VobColor);
	ret->r = r;
	ret->g = g;
	ret->b = b;
	printf("col %f %f %f\n", ret->r, ret->g, ret->b);
	return ret;
}

// -------------------------------------------
// Shade
// -------------------------------------------

VobShade *vob_shade(Region *reg, enum SHADE_TYPE type, float angle) 
{
	VobShade *ret = REGION(reg, "vob.primitive.Shade", VobShade);
	ret->type = type;
	ret->angle = angle;
	ret->steps = util_arr_create(reg);
	ret->colors = util_arr_create(reg);
	return ret;
}
VobShade *vob_shade_add(Region *reg, VobShade *shade, float step, VobColor *c)
{
	void **ptr = &step;
	
	util_arr_add(reg, shade->steps, *ptr);
	util_arr_add(reg, shade->colors, c);
}


