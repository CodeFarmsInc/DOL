#include "environ.h"
#include "types.h"

#ifdef __VMS
#include <unixio.h>
#include <types.h>
#include <stat.h>
#include <file.h>
#endif

#define zzLIB
#include <stdio.h>
#include <stdlib.h>
#define ZZlocal
#include "pager.k"

#ifdef TURBOC
#include <sys\stat.h>
#include <fcntl.h>
#include <io.h>
#endif

#ifdef MICROSOFT
#include <fcntl.h>
#include <sys\types.h>
#include <sys\stat.h>
#include <io.h>
#endif

#ifdef UNIX
#include <fcntl.h>
#ifndef MAC
#include <sys/stat.h>
#include <sys/types.h>
#endif
#ifdef SUN
#ifdef UPP
#include <io.h>
#else
#ifndef MAC
#include <sys/uio.h>
#endif
#endif
#endif
#endif
#ifdef HP
#include <unistd.h>
#endif

#ifdef SABERCPLUS
#include <sysent.h>
#endif


class zzHead {
    ZZ_EXT_zzHead
public:
    zzHead ();
    ~zzHead ();
    ZZint numPages;  /* max.number of pages in memory */
    ZZint pageSize;  /* size of one page */
    ZZlong fileFill; /* max.address currently on file */
    ZZint buffFill;  /* next free address available in the buffer */
    ZZint buffSize;  /* size of the paging buffer */
    char *mb;      /* memory buffer for paging */
    ZZint handle;    /* file handle */
    char *ini;     /* to a separate initialized page, NULL no initialization */
    ZZlong hwm;    /* highest valid character recorded */
};
static zzHead *hStart=NULL;

class Page {
    ZZ_EXT_Page
public:
    Page();
    ~Page();
    ZZint pageNo;
    char *where;
    ZZint dirty;
};

ZZ_HYPER_DOUBLE_RING(zz_heads,zzHead); /* one zzHead for each open pager */
ZZ_HYPER_HASH(zz_pageHash,zzHead,Page); /* access to pages by starting index */
ZZ_HYPER_DOUBLE_COLLECT(zz_pages,zzHead,Page); /* used as stack for replacement */
ZZ_HYPER_NAME(zz_fileName,zzHead); /* to avoid duplications, we keep also name */
ZZ_HYPER_UTILITIES(zz_util);

