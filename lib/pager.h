#define zzLIB
#include <stdio.h>
#include "heading.h"
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
#ifdef COHERENT
#include <sys/stat.h>
#else /* COHERENT */
#include <fcntl.h>
#ifndef MAC
#include <sys/types.h>
#endif /* MAC */
#endif
#ifdef SUN
#ifndef MAC
#include <sys/uio.h>
#endif /* MAC */
#endif /* SUN */
#endif /* UNIX */

#ifdef SABERCPLUS
#include <sysent.h>
#endif

#ifdef HP
#include <unistd.h>
#endif

#ifdef __LPI__
#include <sys/stat.h>
#endif

#define ZZimplicit
typedef struct Head Head;
typedef struct Page Page;
struct Head {
    ZZ_EXT_Head
    ZZint numPages;  /* max.number of pages in memory */
    ZZint pageSize;  /* size of one page */
    ZZlong fileFill; /* max.address currently on file */
    ZZint buffFill;  /* next free address available in the buffer */
    ZZint buffSize;  /* size of the paging buffer */
    char *mb;      /* memory buffer for paging */
    ZZint handle;    /* file handle */
    char *ini;     /* to a separate initialized page, NULL no initialization */
};
static Head *hStart=NULL;

struct Page {
    ZZ_EXT_Page
    ZZint pageNo;
    char *where;
};

ZZ_ORG_DOUBLE_RING(zz_heads,Head); /* one Head for each open pager */
ZZ_ORG_HASH(zz_pageHash,Head,Page); /* access to pages by starting index */
ZZ_ORG_DOUBLE_COLLECT(zz_pages,Head,Page); /* used as stack for replacement */
ZZ_ORG_NAME(zz_fileName,Head); /* to avoid duplications, we keep also name */

