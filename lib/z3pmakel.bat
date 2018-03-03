copy env3zl.h environ.h
del zllib.lib
..\zzprep pager.hpp pager.k zzmaster pager.g
copy virtarr.c virtarr.cpp
ztc -mL -c -b virtarr.cpp
copy pager.cc pager.cpp
ztc -mL -c -b pager.cpp
copy bind.cc bind.cpp
ztc -mL -c -b bind.cpp
copy blast.c blast.cpp
ztc -mL -c -b blast.cpp
copy msgs.c msgs.cpp
ztc -mL -c -b msgs.cpp
copy array.c array.cpp
ztc -mL -c -b array.cpp
copy property.c property.cpp
ztc -mL -c -b property.cpp
copy sweap.c sweap.cpp
ztc -mL -c -b sweap.cpp
copy sortRing.c sortRing.cpp
ztc -mL -c -b sortRing.cpp
copy util.c util.cpp
ztc -mL -c -b util.cpp
copy time.c time.cpp
ztc -mL -c -b time.cpp
copy sweap.c sweap.cpp
ztc -mL -c -b sweap.cpp
zorlib @zllib.rsp
del *.cpp
