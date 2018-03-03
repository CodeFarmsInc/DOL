copy lib\envmsft.h environ.h
cd lib
copy envmsft.h environ.h
echo.
gcc -c util.c msgs.c time.c
cd ..
gcc zzprep.c zzutil.c lib\util.o lib\msgs.o lib\time.o
gcc zzcomb.c zzutil.c lib\util.o lib\msgs.o lib\time.o
gcc zzsplit.c
zzcomb
rem orgc compiled
cd lib
gnu
rem lib compiled
rem finished
cd ..
