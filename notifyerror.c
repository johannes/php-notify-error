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

#include "libnotify/notify.h"

static void (*orig_error_cb)(int type, const char *error_filename, const uint error_lineno, const char *format, va_list args);

/* If you declare any globals in php_notifyerror.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(notifyerror)
*/

static void notifyerror_error_cb(int type, const char *error_filename, const uint error_lineno, const char *format, va_list args)
{
	char *buffer, *error_message, *header;

	vspprintf(&buffer, PG(log_errors_max_len), format, args);
	spprintf(&error_message, 0, "%s\nin %s on line %d", buffer, error_filename, error_lineno);
	efree(buffer);

	switch (type) {
		case E_CORE_ERROR:
		case E_ERROR:
		case E_COMPILE_ERROR:
		case E_USER_ERROR:
			header = "PHP Fatal Error";
			break;
		case E_RECOVERABLE_ERROR:
			header = "PHP Recoverable Fatal Error";
			break;
		case E_WARNING:
		case E_CORE_WARNING:
		case E_COMPILE_WARNING:
			header = "PHP Warning";
			break;
		case E_PARSE:
			header = "PHP Parse Error";
			break;
		case E_NOTICE:
		case E_USER_NOTICE:
			header = "PHP Notice";
			break;
		case E_STRICT:
			header = "PHP Strict Error";
			break;
#ifdef E_DEPRECATED
		case E_DEPRECATED:
		case E_USER_DEPRECATED:
			header = "PHP Deprecation";
			break;
#endif
		default:
			header = "Unknown PHP Error";
			break;
	}

	NotifyNotification* not = notify_notification_new(header, error_message, NULL, NULL);
    notify_notification_show(not, NULL);
    g_object_unref(not);

	efree(error_message);

	orig_error_cb(type, error_filename, error_lineno, format, args);
}

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
	NULL,
	NULL,
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
	notify_init("php " PHP_VERSION);
	orig_error_cb = zend_error_cb;
	zend_error_cb = notifyerror_error_cb;

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

	notify_uninit();

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
