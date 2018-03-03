copy lib\envupp.h environ.h
cd lib
copy envupp.h environ.h
echo.
d:\upp\mingw\bin\g++ -c util.c msgs.c time.c
cd ..
copy zzprep.c zzprep.cpp
copy zzcomb.c zzcomb.cpp
copy zzsplit.c zzsplit.cpp
copy zzutil.c zzutil.cpp
d:\upp\mingw\bin\g++ zzprep.c zzutil.c lib\util.o lib\msgs.o lib\time.o
REM d:\upp\mingw\bin\g++ zzcomb.c zzutil.c lib\util.o lib\msgs.o lib\time.o
REM d:\upp\mingw\bin\g++ zzsplit.c
del *.cpp
REM zzcomb
REM orgc compiled
REM cd lib
REM upp
REM cd ..
rem lib compiled
rem finished
