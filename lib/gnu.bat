copy envmsft.h environ.h
del *.o
del mllib.lib
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
gcc -c virtarr.cpp pager.cpp util.cpp bind.cpp sweap.cpp array.cpp
gcc -c blast.cpp time.cpp msgs.cpp property.cpp sortRing.cpp 
del *.cpp
lib /OUT:mllib.lib pager.o time.o property.o util.o bind.o sortring.o array.o sweap.o msgs.o blast.o virtarr.o
