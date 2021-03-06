/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
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

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_berg.h"

/* If you declare any globals in php_berg.h uncomment this:*/
ZEND_DECLARE_MODULE_GLOBALS(berg)
zend_class_entry *berg_buffers_class_entry;

/* True global resources - no need for thread safety here */
static int le_berg;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini*/
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("berg.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_berg_globals, berg_globals)
    STD_PHP_INI_ENTRY("berg.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_berg_globals, berg_globals)
PHP_INI_END()

/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_berg_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_berg_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "berg", arg);

	RETURN_STR(strg);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_berg_init_globals
 */
/* Uncomment this function if you have INI entries*/
static void php_berg_init_globals(zend_berg_globals *berg_globals)
{
	berg_globals->global_value = 0;
	berg_globals->global_string = NULL;
}

/* }}} */

ZEND_BEGIN_ARG_INFO_EX(arginfo_berg_decode, 0, 0, 1)
	ZEND_ARG_INFO(0, class_name)
	ZEND_ARG_INFO(0, bytes)
	ZEND_ARG_INFO(0, descriptor)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_berg_encode, 0, 0, 1)
	ZEND_ARG_INFO(0, object)
	ZEND_ARG_INFO(0, descriptor)
ZEND_END_ARG_INFO()


/* {{{ proto ProtocolBuffers_DescriptorBuilder ProtocolBuffers_DescriptorBuilder::__construct()
*/
PHP_METHOD(berg_buffers, __construct)
{
	zval *instance = getThis();
	zval fields,options,extension_ranges,*tmp;
	array_init(&fields);
	add_next_index_double(&fields,42.00);
	add_next_index_long(&fields,42);
	php_var_dump(&fields,1);
	zend_update_property(Z_OBJCE_P(instance),instance,ZEND_STRL("fields"),&fields);
	zval_ptr_dtor(&fields);

//	array_init(&options);
//	zend_update_property(berg_buffers_class_entry,instance,ZEND_STRL("options"),&options);
//	zval_ptr_dtor(&options);
//
//	array_init(&extension_ranges);
//	zend_update_property(berg_buffers_class_entry,instance,ZEND_STRL("extension_ranges"),&extension_ranges);
//	zval_ptr_dtor(&extension_ranges);

	zend_string *key = zend_string_init(ZEND_STRL("fields"),0);
	if((tmp=zend_hash_find(Z_OBJPROP_P(instance), key))!=NULL){
		php_var_dump(tmp,1);
	}
	zend_string_release(key);
	//>gdb
	//(gdb) p fields1->u2
	//$1 = {var_flags = 4294967295, next = 4294967295, cache_slot = 4294967295, lineno = 4294967295, num_args = 4294967295, fe_pos = 4294967295, fe_iter_idx = 4294967295}
	//(gdb) p fields1->value->arr->nNumUsed
	//$4 = 1
	//(gdb) p fields1->value->arr->nTableSize
	//$5 = 4294956704
	//(gdb) p fields1->value->arr->nNumOfElements
	//$6 = 0
}
/* }}} */


static zend_function_entry php_berg_methods[] = {
	PHP_ME(berg_buffers, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_FE_END
};


/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(berg)
{
	/* If you have INI entries, uncomment these lines*/
	REGISTER_INI_ENTRIES();
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "BergBuffers", php_berg_methods);
	berg_buffers_class_entry = zend_register_internal_class(&ce TSRMLS_CC);
	zend_declare_property_null(berg_buffers_class_entry, ZEND_STRL("name"), ZEND_ACC_PUBLIC);
	zend_declare_property_null(berg_buffers_class_entry, ZEND_STRL("fields"), ZEND_ACC_PUBLIC);
	zend_declare_property_null(berg_buffers_class_entry, ZEND_STRL("options"), ZEND_ACC_PUBLIC);
	zend_declare_property_null(berg_buffers_class_entry, ZEND_STRL("extension_ranges"), ZEND_ACC_PUBLIC);
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(berg)
{
	/* uncomment this line if you have INI entries*/
	UNREGISTER_INI_ENTRIES();

	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(berg)
{
#if defined(COMPILE_DL_BERG) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(berg)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(berg)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "berg support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini*/
	DISPLAY_INI_ENTRIES();

}
/* }}} */

/* {{{ berg_functions[]
 *
 * Every user visible function must have an entry in berg_functions[].
 */
const zend_function_entry berg_functions[] = {
	PHP_FE(confirm_berg_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in berg_functions[] */
};
/* }}} */

/* {{{ berg_module_entry
 */
zend_module_entry berg_module_entry = {
	STANDARD_MODULE_HEADER,
	"berg",
	berg_functions,
	PHP_MINIT(berg),
	PHP_MSHUTDOWN(berg),
	PHP_RINIT(berg),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(berg),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(berg),
	PHP_BERG_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_BERG
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(berg)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
