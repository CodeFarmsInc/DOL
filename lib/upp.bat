copy envupp.h environ.h
echo.
del *.obj
del *.o
del mllib.lib
del mllib.a
..\zzprep pager.hpp pager.k zzmaster pager.g
copy bind.cc bind.cpp
copy pager.cc pager.cpp
copy sweap.c sweap.cpp
copy array.c array.cpp
copy property.c property.cpp
copy sortRing.c sortRing.cpp
copy time.c time.cpp
copy util.c util.cpp
copy msgs.c msgs.cpp
copy blast.c blast.cpp
copy virtarr.c virtarr.cpp
d:\upp\mingw\bin\g++ -c virtarr.cpp pager.cpp bind.cpp util.cpp sweap.cpp array.cpp
d:\upp\mingw\bin\g++ -c blast.cpp time.cpp msgs.cpp property.cpp sortRing.cpp 
del *.cpp
lib /OUT:glib.a pager.o time.o property.o bind.o sortring.o util.o array.o sweap.o msgs.o blast.o virtarr.o
REM ar cr glib.a *.o
REM ranlib glib.a
