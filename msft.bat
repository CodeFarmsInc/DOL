copy lib\envmsft.h environ.h
cd lib
copy envmsft.h environ.h
echo.
cl /c util.c msgs.c time.c
cd ..
cl zzprep.c zzutil.c lib\util.obj lib\msgs.obj lib\time.obj
cl zzcomb.c zzutil.c lib\util.obj lib\msgs.obj lib\time.obj
cl zzsplit.c
zzcomb
rem orgc compiled
cd lib
msft
rem lib compiled
rem finished
