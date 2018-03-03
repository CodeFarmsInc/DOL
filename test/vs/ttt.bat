del tmp.*
copy test34a.c tmp.cpp
..\zzprep incl34.h zzincl.h
cl tmp.cpp ..\lib\mllib.lib
tmp > res34a
diff res34a out34
del tmp.*
copy test34b.c tmp.cpp
..\zzprep incl34.h zzincl.h
cl tmp.cpp ..\lib\mllib.lib
tmp > res34b
diff res34b out34
del tmp.*
copy test34c.c tmp.cpp
..\zzprep incl34.h zzincl.h
cl tmp.cpp ..\lib\mllib.lib
tmp > res34c
diff res34c out34
del tmp.*
copy test34d.c tmp.cpp
..\zzprep incl34.h zzincl.h
cl tmp.cpp ..\lib\mllib.lib
tmp > res34a
diff res34d out34
del tmp.*
copy test34e.c tmp.cpp
..\zzprep incl34.h zzincl.h
cl tmp.cpp ..\lib\mllib.lib
tmp > res34e
diff res34e out34
del tmp.*
copy test34f.c tmp.cpp
..\zzprep incl34.f zzincl.h
cl tmp.cpp ..\lib\mllib.lib
tmp > res34f
diff res34f out34
