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
/*   World 3D QT, World3DTread, MainWidow implementation                    */
/*   A. Volkov 2010                                                         */
/****************************************************************************/

#include "mainwindow.h"

//#include "ui_mainwindow.h"
#include <math.h>
#include <memory.h>
#include <stdlib.h>

#include "./math3d/far_object.h"
/*
#include <QTime>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QKeyEvent>
#include <QProcess>

//Just for debug
//#define KEY_DEBUG
//Turns on demo for importance of process syncronization
//#define THREAD_SYNC_ON_OFF
*/

World3DThread::World3DThread() : /*QThread(),*/ World3D()
{
    Build();
    lost_cadres=0;
    step_interval_ms=100;
}

//QString base_name="";

void World3DThread::SwitchBase()
{
    Base = bases[++base_num%base_count].Base();
    //base_name = bases[base_num%base_count].Name();
}

void World3DThread::Build(basis* b)
{
 //
 Sh_count = 8;
 Ob_count = 16;
 Shapes  = new facet_shape[Sh_count];
 Objects = new object[Ob_count];
 //
 base_count = 3;
 bases = new base[base_count];
 base_num=-1;
 // Some basic shapes
 Shapes[0]=cube();
 Shapes[1]=cylinder(8,1.2);
 Shapes[2]=cone(16,0.2);
 Shapes[3]=sphere(32);
 Shapes[4]=sphere(16);
 //
 Shapes[5]=torus(8);
 Shapes[6]=ellipsoid(32,1,0.3);
 Shapes[7]=ring(32,0.001,1,0.6);
 // It is better to use "objects*[]" instead "objects[]" (to use derived classes),
 // but the goal was to verify operator "object=object&"
 Objects[0]=object(basis(location(  0,  0,5000)),Shapes[3],0xffff00,300);   // Sun
 Objects[1]=object(basis(location( -340, 0,5000)),Shapes[4],0xffff0f,20);   // Mercury 0.4AU
 Objects[2]=object(basis(location( -370, 0,5000)),Shapes[4],0xffffff,40);   // Venus 0.7AU
 Objects[3]=object(basis(location( -400,0,5000)),Shapes[4],0x00efff,37);    // Earth 1AU
 Objects[4]=object(basis(location( -450,0,5000)),Shapes[4],0xff0000,30);    // Mars 1.5AU
 //
 Objects[5]=object(basis(location( -920,0,5000)),Shapes[3],0xff9f00,200);   // Jupiter 5.2AU
 //
 Objects[6]=object(basis(location( -1250, 0,5000)),Shapes[3],0xffef05,150); // Saturn 9.5AU
 Objects[7]=object(basis(location( -1250, 0,5000)),Shapes[7],0xffef05,290); // Saturn ring 9.5AU
 Objects[8]=object(basis(location( -2260,0,5000)),Shapes[4],0xf0f0f0,50);   // Uranus 19.6AU
 Objects[9]=object(basis(location( -3300,0,5000)),Shapes[4],0xfffff0,60);   // Neptune 30AU
 Objects[10]=object(basis(location( -4200,0,5000)),Shapes[4],0x0fffff,30);  // Pluto 39AU
 //
 Objects[11]=object(basis(location(0,60,500)),Shapes[5],0xffffff,10); // Spaceship
 Objects[12]=object(basis(location(0,60,500)),Shapes[1],0xffffff,7);
 //
 Objects[13]=object(basis(location(-20,-20, 100)),Shapes[6],0x7f7f7f,10);   // Saucer 1
 //bases[0]=base(&Objects[13],vector(0,0,0),vector(0, 0.01,0)/*,"ellipsoid"*/);
 bases[0]=base(&Objects[13],vector(0,0,0),vector(0,0,0)/*,"ellipsoid"*/);
 //
 Objects[14]=object(basis(location( 0, -20, 100)),Shapes[0],0x7f707f,1);    // Cube
 //bases[1]=base(&Objects[14],vector(0,0,0),vector(0.01,0.01,0.01)/*,"cube"*/);
 bases[1]=base(&Objects[14],vector(0,0,0),vector(0,0,0)/*,"cube"*/);
 //
 Objects[15]=object(basis(location( 20,-20, 100)),Shapes[2],0xffffff,10);   // Saucer 2
 //bases[2]=base(&Objects[15],vector(0,0,0),vector(0, -0.01,0)/*,"cone"*/);
 bases[2]=base(&Objects[15],vector(0,0,0),vector(0,0,0)/*,"cone"*/);
 //01.09.2013 Far Objects
 far_objects_count = 2000;
 far_objects = new far_object[far_objects_count];
 srand(1000);
 unsigned int colors[5] = {0xffffff,0xffff00,0xff00ff,0x00ffff,0xf0f0f0};
 for (int i=0; i<far_objects_count; i++) {
    far_objects[i] = far_object(basis(location((rand()%3000-1500),(rand()%3000-1500),(rand()%3000-1500))),colors[rand()%5],1);
 }
 /*
 far_objects[0] = far_object(basis(location(0,0,1000)),0xffffff,1);
 far_objects[1] = far_object(basis(location(20,20,1000)),0xffffff,1);
 far_objects[2] = far_object(basis(location(30,30,1000)),0xffffff,1);
 far_objects[3] = far_object(basis(location(40,40,1000)),0xffffff,1);
 far_objects[4] = far_object(basis(location(50,50,1000)),0xffffff,1);
 */
 //
 World3D::Build(b);
}

void World3DThread::draw_far_objects() {
    //01.09.2013 Far Objects
    for (int i=0; i<far_objects_count; i++) {
	far_objects[i].draw_image(*(this->Base), video_system);
    }
}

void World3DThread::Step_of_life()
{
 
 //
 float i=(float)step/M_PI;
 Objects[0]%=vector(0.03,0.03,0.03);
 //
 Objects[1]%=vector(0.3,-0.3,0.3);
 Objects[1]+=vector(sin(i*0.25)*34.0,0,cos(i*0.25)*34.0);
 //
 Objects[2]%=vector(0.3,0.1,-0.3);
 Objects[2]+=vector(sin(i*0.24)*37.0,0,cos(i*0.24)*37.0);
 //
 Objects[3]%=vector(0.01,-0.001,-0.003);
 Objects[3]+=vector(sin(i*0.23)*40.0,0,cos(i*0.23)*40.0);
 //
 Objects[4]%=vector(0.1,-0.3,-0.2);
 Objects[4]+=vector(sin(i*0.22)*45.0,0,cos(i*0.22)*45.0);
 //
 Objects[5]%=vector(-0.01,0.03,0.01);
 Objects[5]+=vector(sin(i*0.21)*92.0,0,cos(i*0.21)*92.0);
 //Objects[5]>>=vector(0.3,0,0.3);
 //
 Objects[6]%=vector(-0.01,0.03,0.01);
 Objects[6]+=vector(sin(i*0.20)*125.0,0,cos(i*0.20)*125.0);
 Objects[7]%=vector(-0.01,0.03,0.01);
 Objects[7]+=vector(sin(i*0.20)*125.0,0,cos(i*0.20)*125.0);
 //
 Objects[8]%=vector(0.3,0.3,0.3);
 Objects[8]+=vector(sin(i*0.19)*226.0,0,cos(i*0.19)*226.0);
 //
 Objects[9]%=vector(0,-0.1,0.);
 Objects[9]+=vector(sin(i*0.18)*330.0,0,cos(i*0.18)*330.0);
 //
 Objects[10]%=vector(0.01,-0.001,-0.003);
 Objects[10]+=vector(sin(i*0.17)*420.0,0,cos(i*0.17)*420.0);
 //
 //vector r(-0.01,0.03,0.01);
 vector r(0,10,0);
 //vector s(0,0,-10);
 vector s(0,0,0.00002);
 vector v(/*sin(i*0.05)*10.0*/0,0,-sin(i*0.05)*100.0);
 Objects[11]%=r;
 //Objects[11]+=v;
 //Objects[11]>>=s;
 //
 memcpy(&(object::basis&)Objects[12],&(object::basis&)Objects[11],sizeof(basis));
 /*
 *bases[0].Base()%=vector(0,0,sin(2.0*i)*0.01);
 *bases[2].Base()%=vector(0,0,sin(2.0*i)*0.01);
 */
 for (int i=0; i<base_count; i++) bases[i].step_of_life();
 //if (Base != bases[base_num%base_count].Base())
      World3D::Step_of_life();
 //else step++;
}

/*
#ifdef THREAD_SYNC_ON_OFF
bool sync_on = true;
#endif

void World3DThread::run () {
    QTime time;
    int rest_to_sleep;
    time.start();
    static long int _step = 1;
STEP:
    time.restart();
    if (
#ifdef THREAD_SYNC_ON_OFF
        (!sync_on)||
#endif
        this->tryLock()) {
        while (step!=_step) this->Step_of_life();
        emit step_finished(time.elapsed());
#ifdef THREAD_SYNC_ON_OFF
        if (sync_on)
#endif
        this->unlock();
    } else {
        lost_cadres++;
    }
    _step++;
    if ((rest_to_sleep=(step_interval_ms-time.elapsed()))>0) msleep(rest_to_sleep);
    goto STEP;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->setBackgroundRole(QPalette::ToolTipBase);
    ui->statusBar->addWidget(ui->label);
    ui->label->setText("");
    ui->label->setAutoFillBackground(true);
    //
    connect(ui->action_Background,SIGNAL(triggered()),this,SLOT(on_action_Background()));
    connect(ui->action_Step_Interval,SIGNAL(triggered()),this,SLOT(on_action_Step_Interval()));
    connect(ui->action_Exit,SIGNAL(triggered()),this,SLOT(on_action_Exit()));
    connect(ui->action_Keys,SIGNAL(triggered()),this,SLOT(on_action_Keys()));
    connect(ui->action_About,SIGNAL(triggered()),this,SLOT(on_action_About()));
    //
    world_thread = new World3DThread();
    vs = new qt_video_system(this,new QImage(":pic.jpg"));
    step_time = image_time = gdi_time =  0;
    im=NULL;
    connect(world_thread,SIGNAL(step_finished(qint64)),this,SLOT(step_event(qint64)));
    world_thread->start(QThread::LowestPriority);
}

MainWindow::~MainWindow()
{
    world_thread->quit();
    delete ui;
    delete vs;
    delete world_thread;
}

void MainWindow::step_event(qint64 st_time)
{
    step_time=st_time;
    if (!im) {
        QTime time;
#ifdef THREAD_SYNC_ON_OFF
        if (sync_on) {
#endif
            // Locks thread to prevent changes during projection
            this->world_thread->lock();
            int max_h = this->height()-ui->statusBar->height();
            vs->set_video_params(max_h,this->width(),max_h,1);
            time.start();
            im=world_thread->create_image(vs);
            image_time = time.elapsed();
            time.restart();
            vs->cadre(*im);
            delete im;
            im=NULL;
            pixmap_time = time.elapsed();
            // Unlocks thread
            this->world_thread->unlock();
#ifdef THREAD_SYNC_ON_OFF
        } else {
            int max_h = this->height()-ui->statusBar->height();
            vs->set_video_params(max_h,this->width(),max_h,1);
            time.start();
            im=world_thread->create_image(vs);
            image_time = time.elapsed();
            time.restart();
            vs->cadre(*im);
            delete im;
            im=NULL;
            pixmap_time = time.elapsed();
        }
#endif
        update();
        update_status();
    }
}

#ifdef KEY_DEBUG
int k=0;
#endif

void MainWindow::update_status()
{
    QString n;
    QString info("Step time (ms): ");
    info+=n.setNum(step_time);
    info+=", projection time (ms): ";
    info+=n.setNum(image_time);
    info+=", pixmap time (ms): ";
    info+=n.setNum(pixmap_time);
    info+=", GDI time (ms): ";
    info+=n.setNum(gdi_time);
    info+=", lost cadres: ";
    info+=n.setNum(world_thread->lost_cadres);
#ifdef THREAD_SYNC_ON_OFF
    info+=", process synchronization: ";
    if (sync_on) info+="On";
    else info+="Off";
#endif
#ifdef KEY_DEBUG
    info+=", key: ";
    info+=n.setNum(k);
#endif
    if (base_name!="") {
        info+=", base name: ";
        info+=base_name;
    }
    ui->label->setText(info);
}

void MainWindow::paintEvent(QPaintEvent * event)
{
    QTime time;
    time.start();
    vs->update_display(event->rect());
    gdi_time = time.elapsed();
}

void MainWindow::on_action_Background()
{
    QFileDialog	dialog(this);
    dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg *.bmp)"));
    if (dialog.exec()) vs->setBackground(new QImage(dialog.selectedFiles()[0]));
}

void MainWindow::on_action_Step_Interval()
{
    QInputDialog dialog(this);
    dialog.setInputMode(QInputDialog::IntInput);
    dialog.setIntMaximum(10);
    dialog.setIntMaximum(1000);
    dialog.setIntValue(world_thread->step_interval_ms);
    dialog.setLabelText("Enter step interval 10..1000 (ms)");
    if (dialog.exec()==QDialog::Accepted) {
        world_thread->step_interval_ms = dialog.intValue();
    }
}

void MainWindow::on_action_Exit()
{
    this->close();
}

void MainWindow::closeEvent(QCloseEvent * event)
{
    if (QMessageBox::question(this,"Exit","Do you want to stop applicatrion?",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes) {
        world_thread->terminate();
        event->accept();
    } else event->ignore();
}

void MainWindow::on_action_Keys()
{
    help();
}

void MainWindow::on_action_About()
{
    QMessageBox::about(this,"World 3D Application","Developed by A. Volkov, 2010\r\nMath3d Classes were developed in 1991.\r\nTested with Qt in 2010.");
}

void MainWindow::help()
{
    QMessageBox::about(this,"Word 3D Keys","Rotations X\tup/down\r\nRotations Y\tleft/right\r\nRotations Z\tpg_up/pg_down\r\nSpeed Z\t\tins/del\r\nJumps\t\t+/-\r\nSwitch bases\tTab\r\nReset view\t\tESC\r\nStop moving\tothers"
#ifdef THREAD_SYNC_ON_OFF
                       +"\r\n\r\nProcess sync.\tBackspace"
#endif
                       );
}

void MainWindow::keyPressEvent(QKeyEvent * event)
{
    static basis b;
    vector* r;
    vector* s;
    basis* _b;
    int bn=world_thread->base_num%world_thread->base_count;
    if (world_thread->Base==world_thread->bases[bn].Base()) {
        s=world_thread->bases[bn].Speed();
        r=world_thread->bases[bn].Rot();
        _b=world_thread->bases[bn].Base();
    } else {
        r=&world_thread->Rot;
        s=&world_thread->Speed;
        _b=world_thread->Base;
    }
#ifdef KEY_DEBUG
    k=event->key();
    switch (k)
#else
    switch (event->key())
#endif
    {
    case Qt::Key_Escape     : {
            //resets to default base
            b=basis();
            world_thread->base_num=-1;
            world_thread->SetBase(&b);
            world_thread->Rot=vector(0,0,0);
            world_thread->Speed=vector(0,0,0);
            base_name="";
        } break;
    case Qt::Key_Home       : {
            *r=*s=vector(0,0,0);
            *_b=basis();
        }break;
    case Qt::Key_PageUp     : *r-=vector(0,0,0.01); break;
    case Qt::Key_PageDown   : *r+=vector(0,0,0.01); break;
    case Qt::Key_Left       : *r-=vector(0,0.01,0); break;
    case Qt::Key_Up         : *r+=vector(0.01,0,0); break;
    case Qt::Key_Right      : *r+=vector(0,0.01,0); break;
    case Qt::Key_Down       : *r-=vector(0.01,0,0); break;
    case Qt::Key_Insert     : *s+=vector(0,0,1.0); break;
    case Qt::Key_Delete     : *s-=vector(0,0,1.0); break;
    case Qt::Key_Plus       : *world_thread->Base>>=vector(0,0,10); break;
    case Qt::Key_Minus      : *world_thread->Base<<=vector(0,0,10); break;
    case Qt::Key_Tab        : world_thread->SwitchBase(); break;
    case Qt::Key_F1         : help(); break;
#ifdef THREAD_SYNC_ON_OFF
    case Qt::Key_Backspace  : sync_on=!sync_on; break;
#endif
    default : {
            *r=*s=vector(0,0,0);
        }
    }
}

*/
