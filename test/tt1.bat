del tmp.*
copy ..\lib\envmsft.h environ.h
type testmp.h >> environ.h
copy test27.h tmp
type test27a.h >> tmp
..\zzprep tmp zzincl_a.h zzmaster zzfunc_a.c
copy test27c.c tmp2.cpp
cl /c tmp2.cpp 
