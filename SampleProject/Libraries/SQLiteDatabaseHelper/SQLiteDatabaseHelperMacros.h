//
// SQLiteDatabaseHelper
// Include/SQLiteDatabaseHelperMacros.h
//
#ifndef __SQLITEDATABASEHELPER_MACROS_H__
#define __SQLITEDATABASEHELPER_MACROS_H__

#ifdef __cplusplus
# define C_FUNC extern "C"
# define C_FUNC_BLOCK_START extern "C" {
# define C_FUNC_BLOCK_END }
#else
# define C_FUNC
# define C_FUNC_BLOCK_START
# define C_FUNC_BLOCK_END
#endif

#endif