#define checkmmu(a, b)
#define countpagerefs(a, b)

#include "../port/portfns.h"

extern int led(int, int);
extern void ledexit(int);
extern void delay(int);
extern void _uartputs(char*, int);
extern int _uartprint(char*, ...);
extern void uartkirkwoodconsole(void);
extern void serialputs(char *, int);
extern void serialputc(int c);

#pragma	varargck argpos	_uartprint 1

extern void archreboot(void);
extern void archconfinit(void);
extern void archreset(void);
extern void barriers(void);
extern void cachedinv(void);
extern void cachedinvse(void*, int);
extern void cachedwb(void);
extern void cachedwbinv(void);
extern void cachedwbinvse(void*, int);
extern void cachedwbse(void*, int);
extern void cacheiinv(void);
extern void cacheuwbinv(void);
extern uintptr cankaddr(uintptr pa);
int	cmpswap(long*, long, long);

/*
 * cachedwb seems like overkill, but just calling barriers isn't enough.
 */
#define coherence cachedwb
// #define coherence barriers

extern u32int controlget(void);
extern u32int cpctget(void);
extern u32int cpidget(void);
extern char *cputype2name(char *, int);
extern void cpuidprint(void);
#define cycles(ip) *(ip) = lcycles()
extern u32int dacget(void);
extern void dacput(u32int);
extern void dcflushall(void);
extern u32int farget(void);
extern u32int fsrget(void);
extern void icflushall(void);
extern void l1cachesoff(void);
extern void l1cacheson(void);
extern void l2cachecfgon(void);
extern void l2cacheon(void);
extern void lastresortprint(char *buf, long bp);
extern void mmuinvalidate(void);		/* 'mmu' or 'tlb'? */
extern void mmuinvalidateaddr(u32int);		/* 'mmu' or 'tlb'? */
extern u32int pidget(void);
extern void pidput(u32int);
void	procrestore(Proc *);
void	procsave(Proc*);
void	procsetup(Proc*);
extern void _reset(void);
extern void setr13(int, u32int*);
#define tas _tas
extern int _tas(ulong *);
extern u32int ttbget(void);
extern void ttbput(u32int);

Dev*		devtabget(int, int);
void		devtabinit(void);
void		devtabreset(void);
long		devtabread(Chan*, void*, long, vlong);
void		devtabshutdown(void);

extern void intrclear(int sort, int v);
extern void intrenable(int sort, int v, void (*f)(Ureg*, void*), void *a, char *name);
extern void intrdisable(int sort, int v, void (*f)(Ureg*, void*), void* a, char *name);
extern void vectors(void);
extern void vtable(void);

/*
 * Things called in main.
 */
extern void clockinit(void);
extern void i8250console(void);
extern void links(void);
extern void mmuinit(void);
extern void touser(uintptr);
extern void trapinit(void);

extern int fpiarm(Ureg*);
extern int fpudevprocio(Proc*, void*, long, uintptr, int);
extern void fpuinit(void);
extern void fpunoted(void);
extern void fpunotify(Ureg*);
extern void fpuprocrestore(Proc*);
extern void fpuprocsave(Proc*);
extern void fpusysprocsetup(Proc*);
extern void fpusysrfork(Ureg*);
extern void fpusysrforkchild(Proc*, Proc*);
extern int fpuemu(Ureg*);

/*
 * Miscellaneous machine dependent stuff.
 */
extern char* getenv(char*, char*, int);
char*	getconf(char*);
uintptr mmukmap(uintptr, uintptr, usize);
uintptr mmukunmap(uintptr, uintptr, usize);
extern void* mmuuncache(void*, usize);
extern void* ucalloc(usize);
extern void ucfree(void*);

/*
 * Things called from port.
 */
extern void delay(int);				/* only scheddump() */
extern int islo(void);
extern void microdelay(int);			/* only edf.c */
extern void evenaddr(uintptr);
extern void idlehands(void);
extern void setkernur(Ureg*, Proc*);		/* only devproc.c */
extern void spldone(void);
extern int splfhi(void);
extern int splflo(void);
extern void sysprocsetup(Proc*);

/*
 * PCI
 */
ulong	pcibarsize(Pcidev*, int);
void	pcibussize(Pcidev*, ulong*, ulong*);
int	pcicfgr8(Pcidev*, int);
int	pcicfgr16(Pcidev*, int);
int	pcicfgr32(Pcidev*, int);
void	pcicfgw8(Pcidev*, int, int);
void	pcicfgw16(Pcidev*, int, int);
void	pcicfgw32(Pcidev*, int, int);
void	pciclrbme(Pcidev*);
void	pciclrioe(Pcidev*);
void	pciclrmwi(Pcidev*);
int	pcigetpms(Pcidev*);
void	pcihinv(Pcidev*);
uchar	pciipin(Pcidev*, uchar);
Pcidev* pcimatch(Pcidev*, int, int);
Pcidev* pcimatchtbdf(int);
void	pcireset(void);
int	pciscan(int, Pcidev**);
void	pcisetbme(Pcidev*);
void	pcisetioe(Pcidev*);
void	pcisetmwi(Pcidev*);
int	pcisetpms(Pcidev*, int);
int	cas32(void*, u32int, u32int);
int	tas32(void*);

#define CASU(p, e, n)	cas32((p), (u32int)(e), (u32int)(n))
#define CASV(p, e, n)	cas32((p), (u32int)(e), (u32int)(n))
#define CASW(addr, exp, new)	cas32((addr), (exp), (new))
#define TAS(addr)	tas32(addr)

extern void forkret(void);
extern int userureg(Ureg*);
void*	vmap(uintptr, usize);
void	vunmap(void*, usize);

extern void kexit(Ureg*);

#define	getpgcolor(a)	0
#define	kmapinval()

#define PTR2UINT(p)	((uintptr)(p))
#define UINT2PTR(i)	((void*)(i))

#define	waserror()	(up->nerrlab++, setlabel(&up->errlab[up->nerrlab-1]))

/*
 * These are not good enough.
 */
#define KADDR(pa)	UINT2PTR(KZERO|((uintptr)(pa)))
#define PADDR(va)	PTR2UINT(((uintptr)(va)) & ~KSEGM)