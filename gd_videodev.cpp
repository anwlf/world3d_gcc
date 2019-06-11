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
/*   Video device gd implementation                                         */
/*   A. Volkov 12/2012                                                      */
/****************************************************************************/

//#include <gd.h>
#include "gd_videodev.h"
#include <stdlib.h>

/****************************************************************************/
/* gd draw_poly method implementation                                       */
/****************************************************************************/

void gd_video_system::draw_poly(int num_points,int *poly_points,int color,REAL_TYPE fill) {
    
    int r = ((color&0xFF0000)>>16)*fill;
    int g = ((color&0x00FF00)>>8)*fill;
    int b = ((color&0x0000FF))*fill;
    int c = gdImageColorResolve(im, r, g, b);
    if (num_points > 1) {
	// Allocates temporary array for points
	gdPoint* points = new gdPoint[num_points];
	for (int i=0; i<num_points; i++) {
    	    points[i].x=poly_points[i*2];
    	    points[i].y=poly_points[(i*2)+1];
	}
	gdImageFilledPolygon(im, points, num_points, c);
	// Releases memory
	delete points;
    } else {
	//gdImageSetPixel(im, poly_points[0], poly_points[1], c);
	int d = rand()%4 + 1;
	gdImageFilledEllipse(im, poly_points[0], poly_points[1], d, d, c);
    }
}


