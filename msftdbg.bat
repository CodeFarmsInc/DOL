copy lib\envmsft.h environ.h
cd lib
copy envmsft.h environ.h
echo.
cl /Zi /c util.c msgs.c time.c
cd ..
cl /Zi zzprep.c zzutil.c lib\util.obj lib\msgs.obj lib\time.obj
cl /Zi zzcomb.c zzutil.c lib\util.obj lib\msgs.obj lib\time.obj
cl /Zi zzsplit.c
zzcomb
rem orgc compiled
cd lib
msftdbg
cd ..
rem lib compiled
rem finished
