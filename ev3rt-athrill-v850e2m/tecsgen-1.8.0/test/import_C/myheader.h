#ifdef DEFINE
typedef unsigned char  C_CHAR;
typedef unsigned char  char_t;
//typedef short          int16_t;
// typedef long           int32_t;
typedef signed char    int8_t;
typedef unsigned char  uint8_t;
struct tag_dummy { int32_t m_dummy; };
typedef void  (*fp_t)( struct tag_dummy );
#endif /* DEFINE */

#ifdef ERROR
#error "import_C error  myheader.h line 4"
#endif

__inline__ char_t func( void )
{
	int32_t  a;
	int32_t  *b;
}

_inline char_t func1( void )
{
	int32_t  a;
	a = b * c;
    a = a;
    a = (int32_t)b;
    a = (int32_t *)b;
	*(int32_t)&a = b;
}

extern char_t func2( int32_t );

__inline__ char_t func2( int32_t b )
{
    void (*volatile fp)(void) = software_term_hook;

    return a * 2;

	func( a );
    a * 2;
	a = b * c;

	z = q >> 3;
	y = r << 3;
	a >>= 3;
	a <<= 3;
	a += 3;
	a -= 3;
	a *= 3;
	a /= 3;
	a %= 3;
	a &= 3;
 	a |= 3;
 	a ^= 3;
 	a >= 3;
 	a <= 3;
 	a > 3;
 	a < 3;
	a == 3;

	signed int a;
	*((volatile unsigned int *)(0xFFFFFF00)) = 10;
	*((volatile unsigned int *)(0xFFFFFF04)) = 1;


//	volatile signed int  a  = 100;
//	const volatile signed int  a  = 100;
//	volatile const signed int a = 100;
//	int signed volatile a = 1000;


	while(1){
	}
	while(1)
		;
}

/*------ begin #978  ------*/
static inline void __NOP(void)
{
    __asm volatile ("nop");
}

Inline void
usart_low_init(void) {
    return;
}
/*------ end #978  ------*/

/*------ begin #980  ------*/
static inline void test1(void)
{
	test2("abc" "xyz");
}
/*------ end #980  ------*/


///////// const /////////
typedef const int const_int;

///////// attr /////////
typedef int tag_attr_int;

typedef struct tag_attr {
    tag_attr_int attr;
} st_attr;

///////// var /////////
typedef int tag_var_int;

typedef struct tag_var {
    tag_var_int var;
} st_var;

///////// param /////////
typedef int tag_param_int;

typedef struct tag_param {
    tag_param_int param;
} st_param;

///////// return /////////
typedef int tag_return_int;

typedef struct tag_return {
    tag_return_int Return;
} st_return;

///////// member /////////
typedef int tag_member_int;

typedef struct tag_member {
    tag_member_int member;
} st_member;

///////// type /////////
typedef int tag_type_int;

typedef struct tag_type {
    tag_type_int type;
} st_type;
