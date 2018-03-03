REM Parameters added to the batch file will be added as options
REM to the compiler.


copy env3cl.h environ.h
del *.obj
del zzbcb4.lib
..\zzprep pager.hpp pager.k zzmaster pager.g
copy pager.cc pager.cpp
copy sweap.c sweap.cpp
copy array.c array.cpp
copy property.c property.cpp
copy bind.c bind.cpp
copy sortRing.c sortRing.cpp
copy time.c time.cpp
copy util.c util.cpp
copy msgs.c msgs.cpp
copy blast.c blast.cpp
bcc32  -Vt -c %1 %2 %3 %4 %5 %6 %7 %8 %9 pager.cpp bind.cpp util.cpp
sweap.cpp array.cpp property.cpp sortRing.cpp time.cpp msgs.cpp blast.cpp
del *.cpp
tlib zzbcb4 /C +pager +time +property +bind +sortring +util +array +sweap
+msgs +blast
echo zzbcb4.lib done
