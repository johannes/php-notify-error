/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2008 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id: header 252479 2008-02-07 19:39:50Z iliaa $ */

#ifndef PHP_NOTIFYERROR_H
#define PHP_NOTIFYERROR_H

extern zend_module_entry notifyerror_module_entry;
#define phpext_notifyerror_ptr &notifyerror_module_entry

#ifdef PHP_WIN32
#	define PHP_NOTIFYERROR_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_NOTIFYERROR_API __attribute__ ((visibility("default")))
#else
#	define PHP_NOTIFYERROR_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(notifyerror);
PHP_MSHUTDOWN_FUNCTION(notifyerror);
PHP_RINIT_FUNCTION(notifyerror);
PHP_RSHUTDOWN_FUNCTION(notifyerror);
PHP_MINFO_FUNCTION(notifyerror);


/* 

ZEND_BEGIN_MODULE_GLOBALS(notifyerror)
	long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(notifyerror)
*/

#ifdef ZTS
#define NOTIFYERROR_G(v) TSRMG(notifyerror_globals_id, zend_notifyerror_globals *, v)
#else
#define NOTIFYERROR_G(v) (notifyerror_globals.v)
#endif

#endif	/* PHP_NOTIFYERROR_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
