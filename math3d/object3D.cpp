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
/*   OBJECTS  implementation                                                */
/*   A. Volkov, 1991                                                        */
/****************************************************************************/

#include "object3D.h"

object::object(void) : basis() {
    object_shape = NULL;
    facets_colors = NULL;
    object_size = 0;
}

object::object(basis o_b, facet_shape& sh, int color, int size) : basis(o_b) {
    object_shape = &sh;
    facets_colors = new int[object_shape->count()];
    for (int i=0; i<object_shape->count(); i++) facets_colors[i]=color;
    object_size = size;
}

image* object::create_image(basis& v_b, vector& l_v, video_params* v_p) {
    if (object_shape!=NULL) return object_shape->create_image(facets_colors, object_size, (*this)(v_b), (*this)(l_v), v_p);
    else return NULL;
}

