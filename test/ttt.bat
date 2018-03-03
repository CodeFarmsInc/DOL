del tmp.*
copy test63.c tmp.cpp
..\zzprep tmp.cpp
cl tmp.cpp ..\lib\mllib.lib
tmp > res63
diff res63 out63
