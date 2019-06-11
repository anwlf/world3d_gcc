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
/*   FAR OBJECTS  implementation                                                */
/*   A. Volkov, 2012                                                        */
/****************************************************************************/

#include "far_object.h"
//#include "videodev.h"

far_object::far_object(void) : basis() {
    //object_shape = NULL;
    //facets_colors = NULL;
    color = 0;
    object_size = 0;
}

far_object::far_object(basis o_b, int c, int size) : basis(o_b) {
    //object_shape = &sh;
    //facets_colors = new int[object_shape->count()];
    //for (int i=0; i<object_shape->count(); i++) facets_colors[i]=color;
    color = c;
    //((location)*this)*=100000;
    object_size = size;
}

/*
image* object::create_image(basis& v_b, vector& l_v, video_params* v_p) {
    if (object_shape!=NULL) return object_shape->create_image(facets_colors, object_size, (*this)(v_b), (*this)(l_v), v_p);
    else return NULL;
}
*/

void far_object::draw_image(basis& v_b, video_system* v_s) {
    //if (object_shape!=NULL) return object_shape->create_image(facets_colors, object_size, (*this)(v_b), (*this)(l_v), v_p);
    //else return NULL;
    /*
    location vrtx=(*vertexs[i])*size;
    vrtx=v_b(vrtx);
    REAL_TYPE d=abs(vrtx); //vrtx[2]
    if (d!=0) {                                 // ?????
        v_projections[i][0]=v_p->max_x/2+v_p->scale*(vrtx[0]/d);
	v_projections[i][1]=v_p->max_y/2-v_p->scale*v_p->aspect_ratio*(vrtx[1]/d);
    };
    */
    //int points[8];
    int points[2];
    //location l = v_b(loc(*this)+loc(v_b));
    location l = v_b(*this + loc(v_b));
    REAL_TYPE d=abs(l); //vrtx[2]
    if (d!=0) {
	l[0] = v_s->max_x/2+v_s->scale*(l[0]/d);
	l[1] = v_s->max_y/2-v_s->scale*v_s->aspect_ratio*(l[1]/d);
	points[0] = l[0];
	points[1] = l[1];
	/*
	points[2] = l[0]+1;
	points[3] = l[1];
	points[4] = l[0]+1;
	points[5] = l[1]+1;
	points[6] = l[0];
	points[7] = l[1];
	*/
	v_s->draw_poly(1,points,color,1);
    }
}
