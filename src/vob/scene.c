
#include <stdlib.h>

#include "vob/scene.h"
#include "vob/coords.h"
#include "vob/matcher.h"
#include "util/dbg.h"
#include "util/regions.h"



Scene *vob_scene_create()
{
	Scene *ret = malloc(sizeof(Scene));
	ret->matcher = vob_matcher(ret->reg);

	ret->reg = util_regs_create("scene");


	ret->rootCS = (Coordsys*) vob_coords_root(ret);
	ret->vobs_arr = util_fastarr_create(sizeof(void *));
	ret->coords_arr = util_fastarr_create(sizeof(void *));

	ret->anim_set = g_hash_table_new_full(
		g_direct_hash,g_direct_equal,NULL,NULL);

	return ret;
}

void vob_scene_dump(Scene *vs)
{
	int i;
	printf("Scene dump: %d\n", vs->vobs_arr->index);
	for (i=0; i<vs->vobs_arr->index; i++) {
		Vob *v = util_fastarr_get(vs->vobs_arr, i);
		
		switch (v->type) {
		case VOB0:
			printf("vob0\n");
			break;
		case VOB1: {
			printf("vob1 %s %p\n", v->id, v);
			Coordsys *cs = util_fastarr_get(vs->coords_arr, i);
			printf("cs %p\n", cs);
			vob_coords_dump(cs);
			break;
		}
		case VOB2:
		default:
			printf("Vob type not implemented.\n");
			break;
		}
	}
}

void vob_scene_clear(Scene *sc) 
{
	util_regs_clear(sc->reg);

	util_fastarr_clear(sc->vobs_arr);
	util_fastarr_clear(sc->coords_arr);

	g_hash_table_remove_all(sc->anim_set);

	vob_matcher_clear(sc->matcher);

	sc->previous = NULL;
}

void vob_scene_put0(Scene *vs, Vob0 *v)
{
	util_fastarr_add(vs->vobs_arr, v);
	util_fastarr_add(vs->coords_arr, NULL);
}
void vob_scene_put1(Scene *vs, Vob1 *v, Coordsys *cs)
{
	util_fastarr_add(vs->vobs_arr, v);
	util_fastarr_add(vs->coords_arr, cs);
	//printf("vob_scene_put1 %p %d %d\n", cs, vs->vobs_arr->index, vs->coords_arr->index);
	/*Coordsys *css = */
	util_fastarr_get(vs->coords_arr, vs->coords_arr->index-1);
	//printf("cs %p\n", css);

}

struct cs_pair {
	Coordsys *cs1, *cs2;
};

void vob_scene_put2(Scene *vs, Vob2 *v, Coordsys *cs1, Coordsys *cs2)
{
	static char *id = "vob.scene.CoordsysPair";
	struct cs_pair *pair = (struct cs_pair*)
		util_regs_instantiate(vs->reg, &id, sizeof(struct cs_pair));
	pair->cs1 = cs1;
	pair->cs2 = cs2;

	util_fastarr_add(vs->vobs_arr, v);
	util_fastarr_add(vs->coords_arr, pair);
}

