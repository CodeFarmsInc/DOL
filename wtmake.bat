copy lib\env0wt.h environ.h
cd lib
copy env0wt.h environ.h
wcl386 -c util.c msgs.c time.c
cd ..
wcl386 zzprep.c zzutil.c lib\util.obj lib\msgs.obj lib\time.obj
wcl386 zzcomb.c zzutil.obj lib\util.obj lib\msgs.obj lib\time.obj
wcl386 zzhelp.c zzutil.obj lib\util.obj lib\msgs.obj lib\time.obj
wcl386 zzsplit.c
wcl386 zzroff.c 
zzcomb
rem finished
