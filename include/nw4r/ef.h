#ifndef NW4R_PUBLIC_EF_H
#define NW4R_PUBLIC_EF_H

#include <nw4r/ef/ef_drawinfo.h>
#include <nw4r/ef/ef_drawstrategy.h>
#include <nw4r/ef/ef_effect.h>
#include <nw4r/ef/ef_effectsystem.h>
#include <nw4r/ef/ef_emitter.h>
#include <nw4r/ef/ef_emitterform.h>
#include <nw4r/ef/ef_handle.h>
#include <nw4r/ef/ef_memorymanager.h>
#include <nw4r/ef/ef_particle.h>
#include <nw4r/ef/ef_particlemanager.h>
#include <nw4r/ef/ef_res_animcurve.h>
#include <nw4r/ef/ef_res_emitter.h>
#include <nw4r/ef/ef_res_texture.h>
#include <nw4r/ef/ef_resource.h>
#include <nw4r/ef/ef_util.h>

/******************************************************************************
 *
 * Emitter forms
 *
 ******************************************************************************/

#include <nw4r/ef/emform/ef_cube.h>
#include <nw4r/ef/emform/ef_cylinder.h>
#include <nw4r/ef/emform/ef_disc.h>
#include <nw4r/ef/emform/ef_emform.h>
#include <nw4r/ef/emform/ef_line.h>
#include <nw4r/ef/emform/ef_point.h>
#include <nw4r/ef/emform/ef_sphere.h>
#include <nw4r/ef/emform/ef_torus.h>

/******************************************************************************
 *
 * Draw strategies
 *
 ******************************************************************************/

#include <nw4r/ef/drawstrategy/ef_drawbillboardstrategy.h>
#include <nw4r/ef/drawstrategy/ef_drawdirectionalstrategy.h>
#include <nw4r/ef/drawstrategy/ef_drawfreestrategy.h>
#include <nw4r/ef/drawstrategy/ef_drawlinestrategy.h>
#include <nw4r/ef/drawstrategy/ef_drawpointstrategy.h>
#include <nw4r/ef/drawstrategy/ef_drawsmoothstripestrategy.h>
#include <nw4r/ef/drawstrategy/ef_drawstrategybuilder.h>
#include <nw4r/ef/drawstrategy/ef_drawstrategyimpl.h>
#include <nw4r/ef/drawstrategy/ef_drawstripestrategy.h>

#endif
