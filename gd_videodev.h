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
/*    Video device for gd, header                                           */
/*    A. Volkov 12/2012                                                     */
/****************************************************************************/
#ifndef GD_VIDEODEV_H
#define GD_VIDEODEV_H

#define	 _White          0xffffff
#define	 _Black          0x000000
#define	 _Red            0xff0000
#define	 _Dark_red       0x800000
#define	 _Green          0x00ff00
#define	 _Dark_green     0x008000
#define	 _Blue           0x0000ff
#define	 _Dark_blue      0x000080
#define	 _Cyan           0x00ffff
#define	 _Dark_cyan      0x008080
#define	 _Magenta        0xff00ff
#define	 _Dark_magenta   0x800080
#define	 _Yellow         0xffff00
#define	 _Dark_yellow    0x808000
#define	 _Gray           0xa0a0a4
#define	 _Dark_gray      0x808080
#define	 _Light_gray     0xc0c0c0

#include "./math3d/videodev.h"
#include <gd.h>
using namespace std;

class gd_video_system : public video_system
{
 public: gdImagePtr im;
 public:
  gd_video_system(int w, int h) : video_system() {
      im = gdImageCreateTrueColor(w, h);
      set_video_params(im->sy,im->sx,im->sy,1);
      int bg = gdImageColorAllocate(im, 155, 155, 155);
      gdImageColorTransparent(im, bg);
      gdImageFill(im,0,0,bg);
  }
  ~gd_video_system() {
    gdImageDestroy(im);
  }
  virtual void draw_poly(int num_points,int *poly_points,int color, REAL_TYPE fill);
};

#endif // GD_VIDEODEV_H
