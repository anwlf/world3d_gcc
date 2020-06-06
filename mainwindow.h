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
/***********************************************************/
/*   World 3D svg, World3DTread, MainWidow header           */
/*   A. Volkov 12/2012                                        */
/***********************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include <QtGui/QMainWindow>
//#include <QThread>
//#include <QMutex>
#include "./math3d/World3D.h"
#include "gd_videodev.h"

#include "./math3d/far_object.h"

namespace Ui
{
    class MainWindow;
}

// Just for fun, to switch view points
class base {
protected:
    object *_obj;
    vector _speed;
    vector _rotation;
//    QString _name;
public:
    basis* Base() { return _obj; }
    vector* Speed() { return &_speed; }
    vector* Rot() { return &_rotation; }
//    QString& Name() { return _name; }
    base(object* obj=NULL, vector spd = vector(), vector rot=vector()/*, QString n=""*/) { _obj=obj; _speed=spd; _rotation=rot; /*_name=n;*/ }
    void step_of_life() { *_obj%=_rotation; *_obj>>=_speed; }
    void fprint_(FILE* f) {
	fprintf(f,"o(l(%f,%f,%f):r((%f,%f,%f),(%f,%f,%f),(%f,%f,%f))):s(%f,%f,%f):r(%f,%f,%f)\n",
		loc(*_obj)[0],loc(*_obj)[1],loc(*_obj)[2],
		orts(*_obj)[0][0],orts(*_obj)[0][1],orts(*_obj)[0][2],
		orts(*_obj)[1][0],orts(*_obj)[1][1],orts(*_obj)[1][2],
		orts(*_obj)[2][0],orts(*_obj)[2][1],orts(*_obj)[2][2],
		_speed[0],_speed[1],_speed[2],
		_rotation[0],_rotation[1],_rotation[2]);
    }
    void fscan_(FILE* f) {
	fscanf(f,"o(l(%f,%f,%f):r((%f,%f,%f),(%f,%f,%f),(%f,%f,%f)):s(%f,%f,%f):r(%f,%f,%f)\n",
		&loc(*_obj)[0],&loc(*_obj)[1],&loc(*_obj)[2],
		/*
		&orts(*_obj)[0][0],&orts(*_obj)[0][1],&orts(*_obj)[0][2],
		&orts(*_obj)[1][0],&orts(*_obj)[1][1],&orts(*_obj)[1][2],
		&orts(*_obj)[2][0],&orts(*_obj)[2][1],&orts(*_obj)[2][2],
		*/
		&orts(*_obj).m(0,0),&orts(*_obj).m(0,1),&orts(*_obj).m(0,2),
		&orts(*_obj).m(1,0),&orts(*_obj).m(1,1),&orts(*_obj).m(1,2),
		&orts(*_obj).m(2,0),&orts(*_obj).m(2,1),&orts(*_obj).m(2,2),
		//
		&_speed[0],&_speed[1],&_speed[2],
		&_rotation[0],&_rotation[1],&_rotation[2]);
    }
    void fprint(FILE* f) {
    	fprintf(f,"s(%f,%f,%f):r(%f,%f,%f)\n",
		_speed[0],_speed[1],_speed[2],
		_rotation[0],_rotation[1],_rotation[2]);
    }
    void fscan(FILE* f) {
	fscanf(f,"s(%f,%f,%f):r(%f,%f,%f)\n",
		&_speed[0],&_speed[1],&_speed[2],
		&_rotation[0],&_rotation[1],&_rotation[2]);
    }
    char* speed_sprint(char* buf) {
	sprintf(buf,"S:(%f,%f,%f)",_speed[0],_speed[1],_speed[2]);
	return buf;
    }
    char* rot_sprint(char* buf) {
	sprintf(buf,"R:(%f,%f,%f)",_rotation[0],_rotation[1],_rotation[2]);
	return buf;
    }
};

class World3DThread : /*public QThread, public QMutex,*/ public World3D
{
    //Q_OBJECT

    public: gd_video_system* video_system;

public:
    int far_objects_count;
    far_object* far_objects;
    World3DThread();
    ~World3DThread() {/*this->unlock(); quit();*/ delete bases; }
    int step_interval_ms;
    int lost_cadres;
    base* bases;
    int base_count, base_num;
    void SwitchBase();
    void fprint(FILE* f) {
	for (int i=0; i<Ob_count; i++) {
	    bool base = false;
	    for (int b=0; b<base_count; b++) {
	//	base |= (&Objects[i] == bases[b].Base());
	    }
	    if (!base) {
		fprintf(f,"o(l(%f,%f,%f):r((%f,%f,%f),(%f,%f,%f),(%f,%f,%f)))\n",
		    loc(Objects[i])[0],loc(Objects[i])[1],loc(Objects[i])[2],
		    orts(Objects[i])[0][0],orts(Objects[i])[0][1],orts(Objects[i])[0][2],
		    orts(Objects[i])[1][0],orts(Objects[i])[1][1],orts(Objects[i])[1][2],
		    orts(Objects[i])[2][0],orts(Objects[i])[2][1],orts(Objects[i])[2][2]);
	    }
	}
    }
    int fscan(FILE* f) {
	for (int i=0; i<Ob_count; i++) {
	    bool base = false;
	    for (int b=0; b<base_count; b++) {
	//	base |= (&Objects[i] == bases[b].Base());
	    }
	    if (!base) {
		return fscanf(f,"o(l(%f,%f,%f):r((%f,%f,%f),(%f,%f,%f),(%f,%f,%f)))\n",
		    &loc(Objects[i])[0],&loc(Objects[i])[1],&loc(Objects[i])[2],
		    &orts(Objects[i])[0][0],&orts(Objects[i])[0][1],&orts(Objects[i])[0][2],
		    &orts(Objects[i])[1][0],&orts(Objects[i])[1][1],&orts(Objects[i])[1][2],
		    &orts(Objects[i])[2][0],&orts(Objects[i])[2][1],&orts(Objects[i])[2][2]);
	    }
	}
	return 0;
    }
//signals:
    // "world_thread" has finished calculations  and emits signal
    //void step_finished(qint64 step_time);
    void draw_far_objects();
protected:
    // "World3D" virtual functions
    virtual void Build(basis* b=NULL);
    virtual void Step_of_life();
    //
    //virtual void run ();
};

/*
class MainWindow : public QMainWindow
{
    Q_OBJECT

    qt_video_system* vs;
    World3DThread* world_thread;
    image* im;
    Ui::MainWindow *ui;
    qint64 step_time,image_time,pixmap_time,gdi_time;

public:

    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    virtual void paintEvent(QPaintEvent * event);
    virtual void keyPressEvent(QKeyEvent * event);
    virtual void closeEvent(QCloseEvent * event);
    // Displays simple help dialog
    void help();
public slots:
    // "world_thread" has finished calculations and emitted signal to this slot
    void step_event(qint64 step_time);
    // Shows info about times
    void update_status();
    // Menu actions
    void on_action_Background();
    void on_action_Step_Interval();
    void on_action_Exit();
    void on_action_Keys();
    void on_action_About();
};
*/
#endif // MAINWINDOW_H
