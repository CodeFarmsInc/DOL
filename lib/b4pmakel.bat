copy env3cla.h environ.h
del *.obj
del bllib.lib
..\zzprep pager.hpp pager.k zzmaster pager.g
copy pager.cc pager.cpp
copy sweap.c sweap.cpp
copy array.c array.cpp
copy property.c property.cpp
copy bind.cc bind.cpp
copy sortRing.c sortRing.cpp
copy time.c time.cpp
copy util.c util.cpp
copy msgs.c msgs.cpp
copy blast.c blast.cpp
copy virtarr.c virtarr.cpp
bcc -ml -c virtarr.cpp
bcc -ml -c pager.cpp bind.cpp util.cpp sweap.cpp array.cpp property.cpp 
bcc -ml -c sortRing.cpp time.cpp msgs.cpp blast.cpp
del *.cpp
tlib bllib /C +pager +time +property +bind +sortring +util +array +sweap +msgs +blast +virtarr
