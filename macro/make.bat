cd ..\lib
copy env0cla.h environ.h
bcc -c -ml -Lc:\tc\lib -Ic:\tc\include util.c msgs.c time.c
cd ..
copy lib\env0cla.h environ.h
bcc -c -ml -Lc:\tc\lib -Ic:\tc\include  zzutil.c
cd macro
copy ..\lib\env0cla.h environ.h
bcc -ml -Lc:\tc\lib -Ic:\tc\include  zzmerge.c ..\zzutil.obj ..\lib\time.obj ..\lib\util.obj ..\lib\msgs.obj
bcc -ml  -Lc:\tc\lib -Ic:\tc\include  zzselect.c ..\zzutil.obj ..\lib\time.obj ..\lib\util.obj ..\lib\msgs.obj
