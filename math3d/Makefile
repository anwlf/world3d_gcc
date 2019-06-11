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
CFLAGS=-g

OBJS = far_object.o analytic.o obshapes.o object3D.o obimages.o obfrsh.o eventcon.o World3D.o videodev.o

all:${OBJS}

clean:
	rm -f *.o

.cpp.o:
	${CC} ${CFLAGS} -c $<
