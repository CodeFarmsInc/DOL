REM ----- test60a
del tile.odb
copy test60a.c tmp.cpp
..\zzprep tmp.cpp
cl tmp.cpp ..\lib\mllib.lib
tmp>res60a
diff res60a out60
REM ----- test60b
del tile.odb
copy test60b.c tmp.cpp
..\zzprep tmp.cpp
cl tmp.cpp ..\lib\mllib.lib
tmp>res60b
diff res60b out60
REM ----- test60c
del tile.odb
copy test60c.c tmp.cpp
..\zzprep tmp.cpp
cl tmp.cpp ..\lib\mllib.lib
tmp>res60c
diff res60c out60
REM ----- test60d
del tile.odb
copy test60d.c tmp.cpp
..\zzprep tmp.cpp
cl tmp.cpp ..\lib\mllib.lib
tmp>res60d
diff res60d out60
