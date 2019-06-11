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
/*   IMAGES header                                                          */
/*   A. Volkov, 1991                                                        */
/****************************************************************************/

#ifndef __O_IMAGES
#define __O_IMAGES

#include <stddef.h>
#include "videodev.h"
#include "analytic.h"

class video_system;

typedef int point_projection[2];

class poly_image {
    public:
	int color, num_points;
	int* poly_points;
	poly_image* next;
	REAL_TYPE distance, fill;

	poly_image(int c, int n_p, int* p_p,  poly_image* _next, REAL_TYPE d, REAL_TYPE f) {
	    color=c; num_points=n_p; poly_points=p_p; next=_next;
	    distance=d; fill=f;
	}
	void draw(video_system* v_s);
};

class image {
	poly_image* image_elements;
    public:
	image() {image_elements = NULL;}
	~image();

	void draw(video_system* v_s);
	void clear();
	image& operator +=(poly_image* p_i);
	image& operator +=(image* p_i);
};

#endif
