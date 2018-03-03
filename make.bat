copy lib\env0cla.h environ.h
cd lib
copy env0cla.h environ.h
bcc -c -ml -Lc:\tc\lib -Ic:\tc\include util.c msgs.c time.c
cd ..
bcc -ml  -Lc:\tc\lib -Ic:\tc\include  zzprep.c zzutil.c lib\util.obj lib\msgs.obj lib\time.obj
bcc -ml  -Lc:\tc\lib -Ic:\tc\include  zzcomb.c zzutil.obj lib\util.obj lib\msgs.obj lib\time.obj
bcc -ml  -Lc:\tc\lib -Ic:\tc\include  zzhelp.c zzutil.obj lib\util.obj lib\msgs.obj lib\time.obj
bcc -ml  -Lc:\tc\lib -Ic:\tc\include  zzsplit.c
bcc -ml  -Lc:\tc\lib -Ic:\tc\include  zzroff.c 
zzcomb
rem finished
