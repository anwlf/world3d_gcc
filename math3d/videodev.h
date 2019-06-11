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
/*   VIDEO devices header                                                   */
/*   A. Volkov, 1991                                                        */
/****************************************************************************/

#ifndef __VIDEO_S
#define __VIDEO_S

#include "obimages.h"
#include "analytic.h"

class video_params {
    public:
	int scale,max_x,max_y;
	float aspect_ratio;
	video_params() {
	    scale=1; max_x=80; max_y=25; aspect_ratio=0.5;
	}
	video_params (int s, int m_x, int m_y, float a_r) {
	    scale=s; max_x=m_x; max_y=m_y; aspect_ratio=a_r;
	}
};

class image;

class video_system : public video_params {
    public:
	video_system() {}

	void cadre(image& im);
	virtual void draw_poly(int num_points,int *poly_points,int color,REAL_TYPE fill);
	void set_scale(int s_c)	{
	    scale=s_c;
	}
	void set_video_params (int s, int m_x, int m_y, float a_r) {
	    scale=s; max_x=m_x; max_y=m_y; aspect_ratio=a_r;
	}
    protected:
	virtual void setup_cadre() {}
	virtual void show_cadre()  {}
};

#endif
