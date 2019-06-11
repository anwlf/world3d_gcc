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
/*   Facet ROTATION shapes implementation                                   */
/*   A. Volkov, 1991                                                        */
/****************************************************************************/

#include "obfrsh.h"
#include "eventcon.h"

void rotation_shape::set_shape(int koeff, int line_point_c, location* p, int Up,int Down) {
    basis self;
    framework = new shape_framework(koeff*line_point_c);
    int i,j;
    for (i=0; i<koeff; i++) {
	_EVENT_H;
	for (j=0; j<line_point_c; j++) (*framework)[i*line_point_c+j] = self(p[j]);
	self%=vector(0,2*M_PI/koeff,0);
    };
    for (i=0; i<koeff; i++)
	for (j=0; j<(line_point_c-1); j++) {
	    _EVENT_H;
	    add_facet(contour(5,i*line_point_c+j,(i*line_point_c+j+1),
				((i+1)*line_point_c+j+1)%(koeff*line_point_c),
				((i+1)*line_point_c+j)%(koeff*line_point_c),
				i*line_point_c+j));
    };
    /* Up facet */
    if (Up) {
	int *up_p_n = new int[koeff];
	for (i=0; i<koeff; i++) up_p_n[koeff-i-1] = (i*line_point_c+line_point_c-1)%(koeff*line_point_c);
        add_facet(contour(koeff,up_p_n));
    };
    /* Down facet */
    if (Down) {
	int *down_p_n = new int[koeff];
	for (i=0; i<koeff; i++)
	down_p_n[i] = (i*line_point_c)%(koeff*line_point_c);
	add_facet(contour(koeff,down_p_n));
    };
}

rotation_shape::rotation_shape(int koeff, int line_point_c, location* p) {
    set_shape(koeff,line_point_c,p,1,1);
}

cube::cube(REAL_TYPE h) {
    location c_l[2];
    c_l[0]=location(h,-h,h);
    c_l[1]=location(h, h,h);
    set_shape(4,2,c_l,1,1);
}

cylinder::cylinder(int r_k, REAL_TYPE h,REAL_TYPE r) {
    location c_l[2];
    c_l[0]=location(r,-h,0);
    c_l[1]=location(r, h,0);
    set_shape(r_k,2,c_l,1,1);
}

//added 12.30.2010
ring::ring(int r_k, REAL_TYPE h,REAL_TYPE R, REAL_TYPE r) {
    location c_l[4];
    c_l[0]=location(r,-h,0);
    c_l[1]=location(R,-h,0);
    c_l[2]=location(R, h,0);
    c_l[3]=location(r,-h,0);
    set_shape(r_k,4,c_l,0,0);
}

cone::cone(int r_k, REAL_TYPE h,REAL_TYPE r) {
    location c_l[2];
    c_l[0]=location(r,-h,0);
    c_l[1]=location(0, h,0);
    set_shape(r_k,2,c_l,0,1);
}

sphere::sphere(int r_k, REAL_TYPE r) {
    basis self;
    location *c_l = new location[r_k+1];
    for (int i=0; i<=r_k; i++) {
	c_l[i]=self(location(0.001,-r,0));
	self%=vector(0,0,M_PI/r_k);
    }
    set_shape(r_k,r_k+1,c_l,0,0);
    delete c_l;
}

//added 12.30.2010
ellipsoid::ellipsoid(int r_k, REAL_TYPE r1, REAL_TYPE r2) {
    location *c_l = new location[r_k];
    for (int i=1; i<=r_k; i++) {
	c_l[i-1]=vector(r1*-sin(i*M_PI/(r_k+1)),r2*-cos(i*M_PI/(r_k+1)));
    }
    set_shape(r_k,r_k,c_l,1,1);
    delete c_l;
}

torus::torus(int r_k, REAL_TYPE r, REAL_TYPE R) {
    basis self;
    location *c_l = new location[r_k+1];
    for (int i=0; i<=r_k; i++) {
	c_l[i]=self(location(-r,0,0))+vector(-R,0,0);
	self%=vector(0,0,2*M_PI/r_k);
    };
    set_shape(r_k,r_k+1,c_l,0,0);
    delete c_l;
}
