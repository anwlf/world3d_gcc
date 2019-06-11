/****************************************************************************/
/*    Math3D Library. Performs 3D Vector and matrix calculations.           */
/*    Copyright (C), 1991-2012,  Andrei Volkov                              */
/*                                                                          */
/*    This program is free software: you can redistribute it and/or modify  */
/*    it under the terms of the GNU General Public License as published by  */
/*    the Free Software Foundation, either version 3 of the License, or     */
/*    (at your option) any later version.                                   */
/*                                                                          */
/*    This program is distributed in the hope that it will be useful,       */
/*    but WITHOUT ANY WARRANTY; without even the implied warranty of        */
/*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         */
/*    GNU General Public License for more details.                          */
/*                                                                          */
/*    You should have received a copy of the GNU General Public License     */
/*    along with this program.  If not, see <http://www.gnu.org/licenses/>. */
/****************************************************************************/
/*   OBJECTS header                                                         */
/*   A. Volkov, 1991                                                        */
/****************************************************************************/

#ifndef __OBJECTS_3D
#define __OBJECTS_3D

#include "analytic.h"
#include "obshapes.h"

class object: public basis {
	facet_shape *object_shape;
	int *facets_colors;
	int object_size;
    public:
	object(void);
	object(basis o_b, facet_shape& sh, int color, int size=1);
	
	image* create_image(basis& v_b, vector& l_v, video_params* v_p);
};

#endif
