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
/*   SHAPES header                                                          */
/*   A. Volkov, 1991                                                        */
/****************************************************************************/

#ifndef __O_SHAPES
#define __O_SHAPES

#include "analytic.h"
#include "obimages.h"

class shape_framework {
	int vertexs_count;
	location** vertexs;
    public:
	shape_framework(int v_c);
	inline int count() {return vertexs_count;}
	point_projection* project(REAL_TYPE size, basis v_b,video_params* v_p);
	inline point_projection* projection() {return v_projections;}
	location& operator [](int v);
    protected:
	point_projection* v_projections;
};

class contour {
	int vertexs_count;
	int* vertexs_nums;
    public:
	contour() {}
	contour(int v_c, int *v_n);
	contour(int v_c ...);
	inline int count() {
	    return vertexs_count;
	}
	inline int operator[](int n) {
	    return vertexs_nums[n];
	}
	int* projection(point_projection* v_p);
};

class facet {
	contour facet_contour;
	vector facet_normal;
	shape_framework* framework;
    public:
	facet *next;
	facet(shape_framework* s_f, contour f_c) {
	    framework=s_f; 
	    facet_contour = f_c; 
	    next = NULL;
	}
	/* Sets normal according 3 basic points */
	void set_normal(int p1, int p2, int p3);
	/* Sets normal according 3 first points ??? */ 
	void set_normal();
	/* Returns intensivity of facet lit */
	REAL_TYPE light_lit(vector& l_v);
	/* Returns distance to facet's farthest point */
	REAL_TYPE distance(basis v_b);
	/* Returns 0 if is not visible */
	int is_visible(REAL_TYPE size, basis v_b );
	
	int* projection();
	poly_image* create_image(int c, basis v_b, vector l_v) {
	    poly_image* p = new poly_image(c, 	facet_contour.count(),
						projection(),
						NULL,
						distance(v_b),
						light_lit(l_v));
	    return p;
	}
	inline location operator [](int v) {
	    return (*framework)[facet_contour[v]];
	}
 };

class facet_shape {	/* in local world light and videobasis */
                     	/* all videoproections                 */
    protected:
	shape_framework* framework;
	int facets_count;
	facet* facets;
	facet* last_facet;
    public:
	facet_shape() {
	    framework = NULL; 
	    facets_count = 0; 
	    facets = NULL;
	}
	facet_shape(shape_framework& s_f) {
	    framework = &s_f; 
	    facets_count = 0; 
	    facets = NULL;
	}
	int count() {
	    return facets_count;
	}
	void add_facet(contour c);
	/*  int is_visible(REAL_TYPE size, basis v_b, video_params* v_p); ??? */
	image* create_image(int *f_c, REAL_TYPE size, basis v_b, vector l_v, video_params* v_p);
};

#endif
