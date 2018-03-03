del tmp.*
copy test63.c tmp.cpp
..\zzprep tmp.cpp
cl /Zi tmp.cpp ..\lib\mllib.lib
tmp > res63
diff res63 out63
