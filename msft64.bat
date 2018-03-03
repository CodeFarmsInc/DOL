cd lib
copy envmsft.h environ.h
copy envmsft.h ..\environ.h
echo.
cl /c util.c msgs.c time.c
cd ..
cl zzprep.c zzutil.c lib\util.obj lib\msgs.obj lib\time.obj
cl zzcomb.c zzutil.c lib\util.obj lib\msgs.obj lib\time.obj
cl zzsplit.c
zzcomb
copy lib\envmsft64.h environ.h
rem orgc compiled
cd lib
msft64
rem lib compiled
rem finished
