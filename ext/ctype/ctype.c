/*
   +----------------------------------------------------------------------+
   | PHP version 4.0                                                      |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2001 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 2.02 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available at through the world-wide-web at                           |
   | http://www.php.net/license/2_02.txt.                                 |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Authors: Hartmut Holzgraefe <hartmut@six.de>                         |
   +----------------------------------------------------------------------+
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "php_ctype.h"
#include "SAPI.h"
#include "ext/standard/info.h"

#include <ctype.h>

/* You should tweak config.m4 so this symbol (or some else suitable)
   gets defined.
*/
#if HAVE_CTYPE

/* If you declare any globals in php_ctype.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(ctype)
*/

/* True global resources - no need for thread safety here */
/* static int le_ctype; */

/* {{{ ctype_functions[]
 * Every user visible function must have an entry in ctype_functions[].
 */
function_entry ctype_functions[] = {
	PHP_FE(ctype_alnum,	NULL)
	PHP_FE(ctype_alpha,	NULL)
	PHP_FE(ctype_cntrl,	NULL)
	PHP_FE(ctype_digit,	NULL)
	PHP_FE(ctype_lower,	NULL)
	PHP_FE(ctype_graph,	NULL)
	PHP_FE(ctype_print,	NULL)
	PHP_FE(ctype_punct,	NULL)
	PHP_FE(ctype_space,	NULL)
	PHP_FE(ctype_upper,	NULL)
	PHP_FE(ctype_xdigit,	NULL)
	{NULL, NULL, NULL}	/* Must be the last line in ctype_functions[] */
};
/* }}} */

/* {{{ ctype_mpodule_entry
 */
zend_module_entry ctype_module_entry = {
	STANDARD_MODULE_HEADER,
	"ctype",
	ctype_functions,
	NULL,
	NULL,
	NULL,
	NULL,
	PHP_MINFO(ctype),
    NO_VERSION_YET,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_CTYPE
ZEND_GET_MODULE(ctype)
#endif

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(ctype)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "ctype functions", "enabled (experimental)");
	php_info_print_table_end();
}
/* }}} */

/* {{{ ctype
 */
static int ctype(int (*iswhat)(int), zval **c) 
{
	switch (Z_TYPE_PP(c)) {
	case IS_LONG:
		return iswhat(Z_LVAL_PP(c));
	case IS_STRING:
		{
			char *p;
			int n, len;
			p=Z_STRVAL_PP(c);
			len = Z_STRLEN_PP(c);
			for(n=0;n<len;n++) {
				if(!iswhat(*p++)) return 0;
			}
			return 1;
		}
	default:
		break;
	}
	return 0;
}
/* }}} */

/* {{{ proto bool ctype_alnum(mixed c)
   Checks for alphanumeric character(s) */
PHP_FUNCTION(ctype_alnum)
{
	zval *c;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &c) == FAILURE)
		return;
	
	if(ctype(isalnum, &c)) {
	   RETURN_TRUE;
	}

	RETURN_FALSE;		
}
/* }}} */

/* {{{ proto bool ctype_alpha(mixed c)
   Checks for alphabetic character(s) */
PHP_FUNCTION(ctype_alpha)
{
	zval *c;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &c) == FAILURE)
		return;
	
	if(ctype(isalpha, &c)) {
	   RETURN_TRUE;
	}

	RETURN_FALSE;		
}
/* }}} */

/* {{{ proto bool ctype_cntrl(mixed c)
   Checks for control character(s) */
PHP_FUNCTION(ctype_cntrl)
{
	zval *c;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &c) == FAILURE)
		return;
	
	if(ctype(iscntrl, &c)) {
	   RETURN_TRUE;
	}

	RETURN_FALSE;		
}
/* }}} */

/* {{{ proto bool ctype_digit(mixed c)
   Checks for numeric character(s) */
PHP_FUNCTION(ctype_digit)
{
	zval *c;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &c) == FAILURE)
		return;
	
	if(ctype(isdigit, &c)) {
	   RETURN_TRUE;
	}

	RETURN_FALSE;		
}
/* }}} */

/* {{{ proto bool ctype_lower(mixed c)
   Checks for lowercase character(s)  */
PHP_FUNCTION(ctype_lower)
{
	zval *c;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &c) == FAILURE)
		return;
	
	if(ctype(islower, &c)) {
	   RETURN_TRUE;
	}

	RETURN_FALSE;		
}
/* }}} */

/* {{{ proto bool ctype_graph(mixed c)
   Checks for any printable character(s) except space */
PHP_FUNCTION(ctype_graph)
{
	zval *c;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &c) == FAILURE)
		return;
	
	if(ctype(isgraph, &c)) {
	   RETURN_TRUE;
	}

	RETURN_FALSE;		
}
/* }}} */

/* {{{ proto bool ctype_print(mixed c)
   Checks for printable character(s) */
PHP_FUNCTION(ctype_print)
{
	zval *c;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &c) == FAILURE)
		return;
	
	if(ctype(isprint, &c)) {
	   RETURN_TRUE;
	}

	RETURN_FALSE;		
}
/* }}} */

/* {{{ proto bool ctype_punct(mixed c)
   Checks for any printable character which is not whitespace or an alphanumeric character */
PHP_FUNCTION(ctype_punct)
{
	zval *c;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &c) == FAILURE)
		return;
	
	if(ctype(ispunct, &c)) {
	   RETURN_TRUE;
	}

	RETURN_FALSE;		
}
/* }}} */

/* {{{ proto bool ctype_space(mixed c)
   Checks for whitespace character(s)*/
PHP_FUNCTION(ctype_space)
{
	zval *c;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &c) == FAILURE)
		return;
	
	if(ctype(isspace, &c)) {
	   RETURN_TRUE;
	}

	RETURN_FALSE;		
}
/* }}} */

/* {{{ proto bool ctype_upper(mixed c)
   Checks for uppercase character(s) */
PHP_FUNCTION(ctype_upper)
{
	zval *c;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &c) == FAILURE)
		return;
	
	if(ctype(isupper, &c)) {
	   RETURN_TRUE;
	}

	RETURN_FALSE;		
}
/* }}} */

/* {{{ proto bool ctype_xdigit(mixed c)
   Checks for character(s) representing a hexadecimal digit */
PHP_FUNCTION(ctype_xdigit)
{
	zval *c;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &c) == FAILURE)
		return;
	
	if(ctype(isxdigit, &c)) {
	   RETURN_TRUE;
	}

	RETURN_FALSE;		
}
/* }}} */

#endif	/* HAVE_CTYPE */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: sw=4 ts=4 fdm=marker
 * vim<600: sw=4 ts=4
 */
