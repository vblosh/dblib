#pragma once
#include <odbc/Connection.h>

//#define MS_SQL
#define MYSQL
//#define INFORMIX

#define NSTRING

#ifdef MS_SQL
#define BOOLEAN
#endif

odbc::ConnectionRef getDBConnection();
