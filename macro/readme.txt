             ------------------------------------------
             Data Object Library - directory orgc/macro
             ------------------------------------------

Most of the files in these directory are macros/documentation packaged
in individual files. File zzmaster contains the master table which
controls the entire library. When making any modifications or additions to
the library, this file must be updated. The master table contains the list
of functions that are used for individual organizations, and the list of
internal (transparent) pointers that represent the data structures.

zzmerge.c allows to merge two libraries (typically the standard
          library form Code Farms, with a privately developed additions)

zzselect.c allows to select a subset of organizations and create
          a smaller library.

Programs ZZMERGE.C and ZZSELECT.C are only for the advanced use of
the library, and you do not have to re-compile them until you eventually
need them. Script files to recompile ZZMERGE and ZZSELECT:

    jsmake   - UNIX (SUN, HP, ..)
    make.bat - Borland C/C++
    mmake.bat - Microsoft C/C++
    jmmake - MAC
    wtmake.bat - WATCOM 9.5

The registry file is needed when 'zzprep' generates file layout.inp
which is needed for the UML diagram (it is the input of the 'layout' program).
Each line of the registry file has the following fields:
  (1) The name of the DOL data structure after the ZZ_HYPER_ flag,
      for example AGGREGATE1 after ZZ_HYPER_AGGREGATE1 has been declared.
  (2) The name which should appear as the association type in the UML
      diagram, use * if the same name should be used, use ? if this
      organization should NOT be displayed in the UML diagram.
      (Warning: 'Name' must be used for 'NAME' for proper display of names
      in the UML diagram).
  (3) Multiplicity code as used in the 'incode' system -- the meaning is
      intutitive, for examples look at file 'registry' in this directory,
      or at incode/alib/lib/registry.
      Multiplicity u1-0 has the meaning of attribute(s) (e.g. name, property)
      Multiplicity u1=1 means operation on the same (single) type, e.g. ring.
  (4) Order in which the participating classes should be listed -- use
      "0" if the order is the same as in the ZZ_HYPER statement. For most
      data organizations the order is the same, typical example is
      ZZ_HYPER_M_TO_N(id,class1,class2,class3) which, for the 'layout'
      program, must be converted to: class2 class1 class3.
      This is represented by the string of indexes, 
      
