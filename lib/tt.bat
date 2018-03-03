cd lib
copy envmsft.h environ.h
copy envmsft.h ..\environ.h
echo.
cl /c util.c msgs.c time.c
cd ..
cl zzprep.c zzutil.c lib\util.obj lib\msgs.obj lib\time.obj
