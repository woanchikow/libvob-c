
#ifndef LOB_COMPONENTS_SPATIAL_H
#define LOB_COMPONENTS_SPATIAL_H

#include "lob/api.h"

/** All components that do layouting on spatial (read 2D) space.
 */ 

Lob *lob_left(Lob *l);
Lob *lob_center(Lob *l);
Lob *lob_right(Lob *l);


Lob *lob_glue();
Lob *lob_vglue();
Lob *lob_hglue();




#endif