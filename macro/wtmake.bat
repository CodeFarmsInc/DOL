cd ..\lib
copy env0wt.h environ.h
wcl386 -c util.c msgs.c time.c
cd ..
copy lib\env0wt.h environ.h
wcl386 -c zzutil.c
cd macro
copy ..\lib\env0wt.h environ.h
wcl386 zzmerge.c ..\zzutil.obj ..\lib\util.obj ..\lib\msgs.obj ..\lib\time.obj
wcl386 zzselect.c ..\zzutil.obj ..\lib\util.obj ..\lib\msgs.obj ..\lib\time.obj
