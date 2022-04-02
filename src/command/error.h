#ifndef _ERROR_H_
#define _ERROR_H_

enum Error {
	FILE_NOT_FIND = 1,
	HAVE_LOOP_ERROR,
	MULTI_FILE_PATH,
	PARAMETER_NOT_EXISTS,
	NO_FILE_PATH,
	FILE_PATH_FORM_ERROR,
	NO_CHAR_ERROR,
	CHAR_FORM_ERROR,
	PARAMETER_FORM_ERROR,
	ALLOC_MEMORY_ERROR,
	MULTI_WORK_ERROR,
	FIRST_CHAR_DUPLICATE,
	FINAL_CHAR_DUPLICATE
};

#endif