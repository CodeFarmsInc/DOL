set ORGCPATH=C:\orgc
copy network.h temp
type main.cpp >> temp
%ORGCPATH%\zzprep temp zzincl.h
cl /Zi main.cpp network.cpp %ORGCPATH%\lib\mllib.lib
set LAYOUTPATH=C:\layout
%LAYOUTPATH%\layout -s param.txt layout.inp
