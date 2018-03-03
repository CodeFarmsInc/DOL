This directory demonstrates schema migration on listings 6.1 and 6.4 
from Chap.6. For some of these listings there is only a reference 
in the text, they may not appear in the text.

List6_1.cpp creates test data and saves it to file1, in ASCII.
It giex us the starting ASCII file.
To compile and run this, use rr3.bat.

List6_2.cpp is the original program to which we added everything we want to 
add. However, the members, association and other features we want to remove
are still there. We open file1 in ASCII using the old formats, and save it
to file2 in the binary mode. We do this because DOL does not allow us to read
and write in different formats within the same program run.
Between the open and save, we have both the old data and the new data in memory.
This is the time to do any conversion if we want to reformat the old data.
To compile and run this, use rr2.bat.

List6_3.cpp reads file4 in binary and saves to file3 in ASCII with NEW format.
We still both the old data and the new data in memory.
To compile and run this, use rr3.bat.

List6_4.cpp has all the unwanted members and associations removed. This
the final, converted soruce.  It reads file3 in ASCII with the new formatstatements, and can create the final version of the data in any format.
Here is saves it to file4 in ASCII mode. Note that file4 is slightly smaller
than file5, because file3 still contained some old, now unused numbers,
which are not in file6.
To compile and run this, use rr6.bat.
-----------------
NOTE the file size:
file3 7,223 bytes  original ASCII
file4 5,620 bytes  includes both old and new stuff; small because it is binary
file5 7,474 bytes  same but in ASCII, significantly bigger
file6 7,281 bytes  slightly smaller after the old stuff was removed
