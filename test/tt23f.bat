copy ..\lib\envmsft.h environ.h
..\zzprep test23f.c
copy test23f.c tmp.cpp
del tmp.exe
cl tmp.cpp ..\lib\mllib.lib
tmp > res23f
diff res23f out23f
