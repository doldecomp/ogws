#include "ef_emform.h"
#include "ef_emitterform.h"
#include "ef_disc.h"
#include "ef_line.h"
#include "ef_cylinder.h"
#include "ef_sphere.h"
#include "ef_torus.h"
#include "ef_cube.h"
#include "ef_point.h"

namespace nw4r
{
	namespace ef
	{
		static EmitterFormDisc gEmitterFormDisc;
		static EmitterFormLine gEmitterFormLine;
		static EmitterFormCylinder gEmitterFormCylinder;
		static EmitterFormSphere gEmitterFormSphere;
		static EmitterFormTorus gEmitterFormTorus;
		static EmitterFormCube gEmitterFormCube;
		static EmitterFormPoint gEmitterFormPoint;
		
		EmitterForm * EmitFormBuilder::Create(EmitFormType formType)
		{
			switch (formType)
			{
				case EmitForm_Disc:
					return &gEmitterFormDisc;
				case EmitForm_Line:
					return &gEmitterFormLine;
				case EmitForm_Cylinder:
					return &gEmitterFormCylinder;
				case EmitForm_Sphere:
					return &gEmitterFormSphere;
				case EmitForm_Torus:
					return &gEmitterFormTorus;
				case EmitForm_Cube:
					return &gEmitterFormCube;
				case EmitForm_Point:
					return &gEmitterFormPoint;
			}
			
			return NULL;
		}
	}
}