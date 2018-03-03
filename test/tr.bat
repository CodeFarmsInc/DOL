copy test0m.c tmp.cpp
..\zzprep tmp.cpp zzincl.h
cl tmp.cpp ..\lib\mllib.lib
tmp inp0 res0m
diff res0m out0mu
