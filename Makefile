############################################################################
#    Math3D Library. Performs 3D Vector and matrix calculations.           #
#    Copyright (C), 1991-2012,  Andrei Volkov                              #
#                                                                          #
#    This program is free software: you can redistribute it and/or modify  #
#    it under the terms of the GNU General Public License as published by  #
#    the Free Software Foundation, either version 3 of the License, or     #
#    (at your option) any later version.                                   #
#                                                                          #
#    This program is distributed in the hope that it will be useful,       #
#    but WITHOUT ANY WARRANTY; without even the implied warranty of        #
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         #
#    GNU General Public License for more details.                          #
#                                                                          #
#    You should have received a copy of the GNU General Public License     #
#    along with this program.  If not, see <http://www.gnu.org/licenses/>. #
############################################################################


CC=g++
# CFLAGS=-L. -lftd2xx -Wl,-rpath /usr/local/lib
CFLAGS=-g
LFLAGS=-L.
##-lm

##INCLUDE=/usr/local/include
##LIB=/usr/local/lib

prefix=/usr/local
exec_prefix=${prefix}

INCLUDE=${prefix}/include
LIB=${exec_prefix}/lib

##CC=gcc

M3D = math3d

# MAIN = svg_videodev mainwindow main
# MATH = analytic obshapes object3D obimages obfrsh eventcon World3D videodev

# SRC=*.cpp ${MATH3D}/*.cpp
# SRC = ${MAIN}.cpp ${MATH3D}/${MATH}.cpp

# OBJS=*.o
# OBJS = ${MAIN}.o ${MATH}.o
M3DOBJS = ${M3D}/far_object.o ${M3D}/analytic.o ${M3D}/obshapes.o ${M3D}/object3D.o ${M3D}/obimages.o ${M3D}/obfrsh.o ${M3D}/eventcon.o ${M3D}/World3D.o ${M3D}/videodev.o
OBJS = gd_videodev.o mainwindow.o main.o

APP=world3d

all:lib ${APP}

lib:
	cd ./${M3D}; make; cd ..;
	
${APP}:${OBJS}
	$(CC) -o $(APP) ${LFLAGS} ${OBJS} ${M3DOBJS} -L${LIB} -lgd

## -lpng -lz -ljpeg -lfreetype -lm

clean_lib:
	cd ./${M3D}; make clean; cd ..;
clean: clean_lib
	rm -f *.o ; rm -f $(APP) ;
	
distclean: clean
	rm ./${M3D}/Makefile; rm Makefile; rm config.h; rm config.log; rm config.status;

.cpp.o:
	${CC} -I${INCLUDE} ${CFLAGS} -c $< 
