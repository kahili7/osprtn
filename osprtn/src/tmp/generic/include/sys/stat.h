#ifndef GENERIC_SYS_STATES_H
#define GENERIC_SYS_STATES_H

struct stat {
#if _FILE_OFFSET_BITS - 0 == 64
	ino_t			st_ino;			/* File serial number.					*/
	off_t			st_size;
#elif !defined(_FILE_OFFSET_BITS) || _FILE_OFFSET_BITS == 32
#if defined(__LITTLEENDIAN__)
	ino_t			st_ino;			/* File serial number.					*/
	ino_t			st_ino_hi;
	off_t			st_size;
	off_t			st_size_hi;
#elif defined(__BIGENDIAN__)
	ino_t			st_ino_hi;
	ino_t			st_ino;			/* File serial number.					*/
	off_t			st_size_hi;
	off_t			st_size;
#else
 #error endian not configured for system
#endif
#else
 #error _FILE_OFFSET_BITS value is unsupported
#endif
	_CSTD dev_t		st_dev;			/* ID of device containing file.		*/
	_CSTD dev_t		st_rdev;		/* Device ID, for inode that is device	*/
	uid_t			st_uid;
	gid_t			st_gid;
	_CSTD time_t	st_mtime;		/* Time of last data modification		*/
	_CSTD time_t	st_atime;		/* Time last accessed					*/
	_CSTD time_t	st_ctime;		/* Time of last status change			*/
	_CSTD mode_t	st_mode;		/* see below							*/
	nlink_t			st_nlink;
	blksize_t		st_blocksize;	/* Size of a block used by st_nblocks   */
	_Int32t			st_nblocks;		/* Number of blocks st_blocksize blocks */
	blksize_t		st_blksize;		/* Prefered I/O block size for object   */
#if _FILE_OFFSET_BITS - 0 == 64
	blkcnt_t		st_blocks;		/* Number of 512 byte blocks			*/
#elif !defined(_FILE_OFFSET_BITS) || _FILE_OFFSET_BITS == 32
#if defined(__LITTLEENDIAN__)
	blkcnt_t		st_blocks;
	blkcnt_t		st_blocks_hi;
#elif defined(__BIGENDIAN__)
	blkcnt_t		st_blocks_hi;
	blkcnt_t		st_blocks;
#else
 #error endian not configured for system
#endif
#else
 #error _FILE_OFFSET_BITS value is unsupported
#endif
};

#if _LARGEFILE64_SOURCE - 0 > 0
struct stat64 {
	ino64_t			st_ino;			/* File serial number.					*/
	off64_t			st_size;
	_CSTD dev_t		st_dev;			/* ID of device containing file.		*/
	_CSTD dev_t		st_rdev;		/* Device ID, for inode that is device	*/
	uid_t			st_uid;
	gid_t			st_gid;
	_CSTD time_t	st_mtime;		/* Time of last data modification		*/
	_CSTD time_t	st_atime;		/* Time last accessed					*/
	_CSTD time_t	st_ctime;		/* Time of last status change			*/
	_CSTD mode_t	st_mode;		/* see below							*/
	nlink_t			st_nlink;
	blksize_t		st_blocksize;	/* Size of a block used by st_nblocks   */
	_Int32t			st_nblocks;		/* Number of blocks st_blocksize blocks */
	blksize_t		st_blksize;		/* Prefered I/O block size for object   */
	blkcnt64_t		st_blocks;		/* Number of 512 byte blocks			*/
};
#endif

#define _S_IFMT     0xF000              /*  Type of file                    */
#define _S_IFIFO    0x1000              /*  FIFO                            */
#define _S_IFCHR    0x2000              /*  Character special               */
#define _S_IFDIR    0x4000              /*  Directory                       */
#define _S_IFNAM    0x5000              /*  Special named file              */
#define _S_IFBLK    0x6000              /*  Block special                   */
#define _S_IFREG    0x8000              /*  Regular                         */
#define _S_IFLNK    0xA000              /*  Symbolic link                   */
#define _S_IFSOCK   0xC000              /*  Socket                          */

#define S_ISFIFO(m) (((m)&_S_IFMT)==_S_IFIFO) /* Test for FIFO.             */
#define S_ISCHR(m)  (((m)&_S_IFMT)==_S_IFCHR) /* Test for char special file.*/
#define S_ISDIR(m)  (((m)&_S_IFMT)==_S_IFDIR) /* Test for directory file.   */
#define S_ISBLK(m)  (((m)&_S_IFMT)==_S_IFBLK) /* Test for block specl file. */
#define S_ISREG(m)  (((m)&_S_IFMT)==_S_IFREG) /* Test for regular file.     */

#define S_ISLNK(m)  (((m)&_S_IFMT)==_S_IFLNK) /* Test for symbolic link.    */
#define S_ISNAM(m)  (((m)&_S_IFMT)==_S_IFNAM) /* Test for special named file*/
#define S_ISSOCK(m) (((m)&_S_IFMT)==_S_IFSOCK)/* Test for socket.           */


#define S_TYPEISMQ(buf)     (S_ISNAM((buf)->st_mode)&&((buf)->st_rdev==_S_INMQ))
#define S_TYPEISSEM(buf)    (S_ISNAM((buf)->st_mode)&&((buf)->st_rdev==_S_INSEM))
#define S_TYPEISSHM(buf)    (S_ISNAM((buf)->st_mode)&&((buf)->st_rdev==_S_INSHD))
#define S_TYPEISTMO(buf)    (S_ISNAM((buf)->st_mode)&&((buf)->st_rdev==_S_INTMO))


/*
 *  For special named files (IFNAM), the subtype is encoded in st_rdev.
 *  The subtypes are:
 */
#define _S_INSEM        00001           /*  semaphore subtype               */
#define _S_INSHD        00002           /*  shared data subtype             */
#define _S_INMQ         00003           /*  message queue subtype           */
#define _S_INTMO        00004           /*  Typed memory object             */
#define _S_QNX_SPECIAL  040000          /*  QNX special type                */

#if defined(_POSIX_SOURCE) || !defined(NO_EXT_KEYS)
/*
 *  Common filetype macros
 */
#define S_IFMT      _S_IFMT             /*  Type of file                    */
#define S_IFIFO     _S_IFIFO            /*  FIFO                            */
#define S_IFCHR     _S_IFCHR            /*  Character special               */
#define S_IFDIR     _S_IFDIR            /*  Directory                       */
#define S_IFNAM     _S_IFNAM            /*  Special named file              */
#define S_IFBLK     _S_IFBLK            /*  Block special                   */
#define S_IFREG     _S_IFREG            /*  Regular                         */
#define S_IFLNK     _S_IFLNK            /*  Symbolic link                   */
#define S_IFSOCK    _S_IFSOCK           /*  Socket                          */
#endif

#if defined(__EXT_QNX)
#define S_INSEM     _S_INSEM            /*  Semaphore                       */
#define S_INSHD     _S_INSHD            /*  Shared Memory                   */
#define S_INMQ      _S_INMQ             /*  Message Queue                   */
#define S_INTMO     _S_INTMO            /*  Typed memory object             */

#define S_IPERMS    000777              /*  Permission mask                 */
#endif

#define S_ISUID     004000              /* set user id on execution         */
#define S_ISGID     002000              /* set group id on execution        */
#define S_ISVTX     001000              /* sticky bit                       */
#define S_ENFMT     002000              /* enforcement mode locking         */

/*
 *  Owner permissions
 */
#define S_IRWXU     000700              /*  Read, write, execute/search     */
#define S_IRUSR     000400              /*  Read permission                 */
#define S_IWUSR     000200              /*  Write permission                */
#define S_IXUSR     000100              /*  Execute/search permission       */
#define S_IREAD     S_IRUSR             /*  Read permission                 */
#define S_IWRITE    S_IWUSR             /*  Write permission                */
#define S_IEXEC     S_IXUSR             /*  Execute/search permission       */

/*
 *  Group permissions
 */
#define S_IRWXG     000070              /*  Read, write, execute/search     */
#define S_IRGRP     000040              /*  Read permission                 */
#define S_IWGRP     000020              /*  Write permission                */
#define S_IXGRP     000010              /*  Execute/search permission       */

/*
 *  Other permissions
 */
#define S_IRWXO     000007              /*  Read, write, execute/search     */
#define S_IROTH     000004              /*  Read permission                 */
#define S_IWOTH     000002              /*  Write permission                */
#define S_IXOTH     000001              /*  Execute/search permission       */

__BEGIN_DECLS
/*
 *  POSIX 1003.1 Prototypes.
 */

#if _LARGEFILE64_SOURCE - 0 > 0
extern int stat64(const char *__path, struct stat64 *__buf);
extern int lstat64(const char *__path, struct stat64 *__buf);
extern int fstat64(int __fildes, struct stat64 *__buf);
#endif

#if defined(__EXT_POSIX1_198808)
extern int stat(const char *__path, struct stat *__buf) __ALIAS64("stat64");
extern int lstat(const char *__path, struct stat *__buf) __ALIAS64("lstat64");
extern int fstat(int __fildes, struct stat *__buf) __ALIAS64("fstat64");
#endif

#if _FILE_OFFSET_BITS - 0 == 64
#if defined(__GNUC__)
/* Use __ALIAS64 define */
#elif defined(__WATCOMC__)
#pragma aux stat "stat64";
#pragma aux lstat "lstat64";
#pragma aux fstat "fstat64";
#elif defined(_PRAGMA_REDEFINE_EXTNAME)
#pragma redefine_extname stat stat64
#pragma redefine_extname lstat lstat64
#pragma redefine_extname fstat fstat64
#else
#define stat stat64
#define lstat lstat64
#define fstat fstat64
#endif
#endif

extern int chmod(const char *__path, _CSTD mode_t __mode);
extern int fchmod(int __fildes, _CSTD mode_t __mode);
#if defined(__EXT_QNX)	/* POSIX 1003.1g draft */
extern int isfdtype(int __fildes, int __fdtype);
#endif
extern int mkdir(const char *__path, _CSTD mode_t __mode);
extern int mkfifo(const char *__path, _CSTD mode_t __mode);
extern int mknod(const char *__path, _CSTD mode_t __mode, _CSTD dev_t __dev);
extern int _mknod_extra(const char *__path, _CSTD mode_t __mode, _CSTD dev_t __dev,
            unsigned __extra_type, unsigned __extra_len, void *__extra);
extern _CSTD mode_t umask(_CSTD mode_t __cmask);

#if defined(__EXT_QNX)
extern _CSTD mode_t _umask(pid_t __pid, _CSTD mode_t __cmask);
#endif

#endif /* GENERIC_SYS_STATES_H */
