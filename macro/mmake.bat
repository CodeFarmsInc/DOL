cd ..\lib
copy envl.m6 environ.h
cl /Od /c /AL /F 4000 util.c msgs.c time.c
cd ..
copy lib\envl.m6 environ.h
cl /Od /c /AL /F 4000 zzutil.c
cd macro
copy ..\lib\envl.m6 environ.h
cl /Od /AL /F 4000 zzmerge.c ..\zzutil.obj ..\lib\util.obj ..\lib\msgs.obj ..\lib\time.obj
cl /Od /AL /F 4000 zzselect.c ..\zzutil.obj ..\lib\util.obj ..\lib\msgs.obj ..\lib\time.obj
