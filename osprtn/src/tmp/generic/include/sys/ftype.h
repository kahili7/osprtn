#ifndef GENERIC_SYS_FTYPE_H
#define GENERIC_SYS_FTYPE_H

enum _file_type {
    _FTYPE_MATCHED = -1,
    _FTYPE_ALL = -1,
    _FTYPE_ANY = 0,
    _FTYPE_FILE,
    _FTYPE_LINK,
    _FTYPE_SYMLINK,
    _FTYPE_PIPE,
    _FTYPE_SHMEM,
    _FTYPE_MQUEUE,
    _FTYPE_SOCKET,
    _FTYPE_SEM,
    _FTYPE_PHOTON,
    _FTYPE_DUMPER,
    _FTYPE_MOUNT,
    _FTYPE_NAME,
    _FTYPE_TYMEM
};

#define _MAJOR_PATHMGR		"pathmgr"	/* Use by path manager only */
#define _MAJOR_DEV			"dev"		/* Devices in /dev with only one instance (/dev/tty) */
#define _MAJOR_BLK_PREFIX	"blk-"		/* All block devices (/dev/hd[0-9]* would be "blk-hd") */
#define _MAJOR_CHAR_PREFIX	"char-"		/* All char devices (/dev/ser[0-9]* would be "char-ser") */
#define _MAJOR_FSYS			"fsys"		/* All filesystems */

#endif /* GENERIC_SYS_FTYPE_H */
