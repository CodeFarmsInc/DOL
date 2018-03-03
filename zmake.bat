copy lib\env0zl.h environ.h
cd lib
copy env0zl.h environ.h
ztc -c -b -ml util.c msgs.c time.c
cd ..
ztc -ml  -b zzprep.c zzutil.c lib\util.obj lib\msgs.obj lib\time.obj
ztc -ml  -b zzcomb.c zzutil.obj lib\util.obj lib\msgs.obj lib\time.obj
ztc -ml  -b zzhelp.c zzutil.obj lib\util.obj lib\msgs.obj lib\time.obj
ztc -ml  -b zzsplit.c
ztc -ml  -b zzroff.c 
zzcomb
rem finished
