copy lib\env0cla.h environ.h
cd lib
copy env0cla.h environ.h
bcc32 -c -Lc:\cb4\lib -Ic:\cb4\include util.c msgs.c time.c
cd ..
bcc32  -Lc:\cb4\lib -Ic:\cb4\include  zzprep.c zzutil.c lib\util.obj
lib\msgs.obj lib\time.obj
pause
bcc32  -Lc:\cb4\lib -Ic:\cb4\include  zzcomb.c zzutil.obj lib\util.obj
lib\msgs.obj lib\time.obj
pause
bcc32  -Lc:\cb4\lib -Ic:\cb4\include  zzhelp.c zzutil.obj lib\util.obj
lib\msgs.obj lib\time.obj
pause
bcc32  -Lc:\cb4\lib -Ic:\cb4\include  zzsplit.c
pause
bcc32  -Lc:\cb4\lib -Ic:\cb4\include  zzroff.c
pause
echo going to zzcomb
pause
zzcomb
rem finished
