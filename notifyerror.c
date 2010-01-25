/*
  +----------------------------------------------------------------------+
  | Notify Error                                                         |
  +----------------------------------------------------------------------+
  | Copyright (c) 2010 Johannes Schlüter                                 |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Johannes Schlüter <johannes@php.net>                         |
  +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_notifyerror.h"

/* If you declare any globals in php_notifyerror.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(notifyerror)
*/


/* {{{ notifyerror_module_entry
 */
zend_module_entry notifyerror_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"notifyerror",
	NULL,
	PHP_MINIT(notifyerror),
	PHP_MSHUTDOWN(notifyerror),
	PHP_RINIT(notifyerror),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(notifyerror),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(notifyerror),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_NOTIFYERROR
ZEND_GET_MODULE(notifyerror)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("notifyerror.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_notifyerror_globals, notifyerror_globals)
    STD_PHP_INI_ENTRY("notifyerror.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_notifyerror_globals, notifyerror_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_notifyerror_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_notifyerror_init_globals(zend_notifyerror_globals *notifyerror_globals)
{
	notifyerror_globals->global_value = 0;
	notifyerror_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(notifyerror)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(notifyerror)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(notifyerror)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(notifyerror)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(notifyerror)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "notifyerror support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
