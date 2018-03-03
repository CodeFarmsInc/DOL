del tmp.*
copy test0n.c tmp.cpp
..\zzprep tmp.cpp
cl /Zi tmp.cpp ..\lib\mllib.lib
tmp inp0 res0n
diff res0n out0nu
