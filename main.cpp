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

#include "mainwindow.h"

#include <gd.h>
#include <gdfonts.h>
//Sleep - usleep(usec)
#include <unistd.h>
//atoi
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

#define Key_Escape	0
#define Key_Home	1
#define Key_PageUp	2
#define Key_PageDown	3
#define Key_Left	4
#define Key_Up		5
#define Key_Right	6
#define Key_Down	7
#define Key_Insert	8
#define Key_Delete	9
#define Key_Plus	10
#define Key_Minus	11
#define Key_Tab		12
#define Key_Backspace	13

#define world_fn "./world.txt"
#define base_fn "/usr/home/avolkov/www/var/base%i.txt"

int main(int argc, char *argv[])
{
    World3DThread w;
    basis* bases_def = new basis[w.base_count];
    for (int i=0; i<w.base_count; i++) {
	memcpy(&bases_def[i],w.bases[i].Base(),sizeof(basis));
    }
    long int step=0;
    FILE* f = fopen (world_fn,"r");
    if (f!=NULL) {
	w.fscan(f);
	fclose(f);
    }
    for (int i=0; i<w.base_count; i++) {
	char buf [50];
	sprintf(buf,base_fn,i);
	if (argc>1) {
	    struct stat statbuf;
	    stat(buf, &statbuf);
	    time_t now = time(&now);
	    if (difftime(now,statbuf.st_mtime)>60) {
		unlink(buf);
	    }
	}
	f = fopen(buf,"r"); 
	if (f!=NULL) {
	    w.bases[i].fscan(f);
	    fclose(f);
	    w.bases[i].step_of_life();
	}
    }
    int b = -1;
    if (argc>1) {
	b = atoi(argv[1]);
	if (b>=0) {
	    w.base_num = b;
	    w.SetBase(w.bases[w.base_num].Base());
	    if (argc>2) {
		int key = atoi(argv[2]);
		
		switch (key)
		{
		    case Key_Escape     : {
			//Returns base location to default and resets speeds
			memcpy(w.bases[w.base_num].Base(),&bases_def[w.base_num],sizeof(basis));
			*w.bases[w.base_num].Rot()=vector(0,0,0);
			*w.bases[w.base_num].Speed()=vector(0,0,0);
			/*
	        	//resets to default base
	    		b=basis();
	        	world_thread->base_num=-1;
	        	world_thread->SetBase(&b);
	        	world_thread->Rot=vector(0,0,0);
	        	world_thread->Speed=vector(0,0,0);
	        	//base_name="";
	        	*/
	    	    } break;
	    	    /*
		    case Key_Home       : {
	        	*r=*s=vector(0,0,0);
	        	*_b=basis();
	    	    } break;
	    	    */
		    case Key_PageUp     : *w.bases[w.base_num].Rot()-=vector(0,0,0.1); break;
	    	    case Key_PageDown   : *w.bases[w.base_num].Rot()+=vector(0,0,0.1); break;
	    	    case Key_Left       : *w.bases[w.base_num].Rot()-=vector(0,0.1,0); break;
	    	    case Key_Up         : *w.bases[w.base_num].Rot()+=vector(0.1,0,0); break;
	    	    case Key_Right      : *w.bases[w.base_num].Rot()+=vector(0,0.1,0); break;
		    case Key_Down       : *w.bases[w.base_num].Rot()-=vector(0.1,0,0); break;
		    case Key_Insert     : *w.bases[w.base_num].Speed()+=vector(0,0,0.1); break;
	    	    case Key_Delete     : *w.bases[w.base_num].Speed()-=vector(0,0,0.1); break;
	    	    //case Key_Plus       : *w.Base>>=vector(0,0,10); break;
	    	    //case Key_Minus      : *w.Base<<=vector(0,0,10); break;
	    	    //case Key_Plus       : *w.Base<<=vector(0,0,10); break;
	    	    //case Key_Minus      : *w.Base>>=vector(0,0,10); break;
	    	    //case Key_Tab        : world_thread->SwitchBase(); break;
	    	    //case Key_F1         : help(); break;
		    //case Key_Backspace  : sync_on=!sync_on; break;
		    default : {
	        //	*r=*s=vector(0,0,0);
	    	    }
		}
	    }
	    char buf [50];
	    sprintf(buf,base_fn,b);
	    f = fopen(buf,"w");
	    w.bases[w.base_num].fprint(f);
	    fclose(f);
	}
	gd_video_system* gd = new gd_video_system(800,600);
//	gd_video_system* gd = new gd_video_system(1280,1024);
//	gd_video_system* gd = new gd_video_system(2560,2048);
	w.video_system=gd;
	//01.09.2012 Far Objects
	w.draw_far_objects();
	image* im = w.create_image(gd);
	gd->cadre(*im);
	delete im;
	if (b>=0) {
	    char buf[50];
	    w.bases[w.base_num].speed_sprint(buf);
	    int c =  gdImageColorResolve(gd->im, 255, 255, 255);
	    gdImageString(gd->im, gdFontGetSmall(), 10, 10, (unsigned char*)buf, c);
	    w.bases[w.base_num].rot_sprint(buf);
	    gdImageString(gd->im, gdFontGetSmall(), 10, 20, (unsigned char*)buf, c);
	}
	gdImagePng(gd->im, stdout);
    } else {
	while (true) {
	    for (int i=0; i<w.base_count; i++) {
		char buf [50];
		sprintf(buf,base_fn,i);
		f = fopen(buf,"r"); 
		if (f!=NULL) {
		    w.bases[i].fscan(f);
		    fclose(f);
		} else {
		    memcpy(w.bases[i].Base(),&bases_def[i],sizeof(basis));
		    *w.bases[i].Rot()=vector(0,0,0);
		    *w.bases[i].Speed()=vector(0,0,0);
		}
	    }
	    w.Step();
	    f = fopen(world_fn,"w");
	    w.fprint(f);
	    fclose(f);
//		usleep(100000);
	    usleep(500000);
//	    printf("step %lu\r\n",step++);
	}
    }
    delete bases_def;
    return 0;
}
