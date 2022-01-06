#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include <dbaccess.h>
#include<odbc/Environment.h>
#include <odbc/RefCounted.h>
#include <odbc/Exception.h>
#include "main.h"

odbc::ConnectionRef conn;

odbc::ConnectionRef getDBConnection()
{
    return conn;
}

void createTable(dblib::DbAccess& db)
{
	const char * createTableStm;
#ifdef INFORMIX
    createTableStm = "CREATE TEMP TABLE test1 ("
        "int16 SMALLINT, int32 INT, int64 BIGINT"
        ", float32 REAL, float64 FLOAT(16), decimal18 DECIMAL(18, 8)"
        ", string1 CHAR(16), string2 VARCHAR(128)"
        ", date1 DATE, time1 DATETIME HOUR TO SECOND, timestamp1 DATETIME YEAR TO SECOND"
        ", binary1 BYTE, binary2 BYTE"
	   ");";

#else
    createTableStm = "CREATE TABLE test1 ("
	   " int16 SMALLINT, int32 INT, int64 BIGINT"
       ", float32 REAL, float64 FLOAT(53), decimal18 DECIMAL(18, 8)"
       ", string1 CHAR(16), string2 VARCHAR(128)"
       ", date1 DATE, time1 TIME, timestamp1 DATETIME"
       ", binary1 BINARY(6), binary2 VARBINARY(3)"
#ifdef NSTRING
 	   ", nstring1 NCHAR(16), nstring2 NVARCHAR(128)"
#endif // NSTRING
#ifdef BOOLEAN
	   ", bit1 BIT"
#endif // BOOLEAN
	   ");";
#endif

   db.execute(createTableStm);
}

void dropTable(dblib::DbAccess& db)
{
    const char* dropTableStm = "DROP TABLE test1;";
    db.execute(dropTableStm);
}

int main( int argc, char *argv[] )
{
    ::testing::InitGoogleTest(&argc, argv);

    int res = 0;
    try
    {
        odbc::EnvironmentRef env = odbc::Environment::create();
        conn = env->createConnection();
#ifdef MYSQL
        conn->connect("MySQLTest", nullptr, nullptr);
#endif // MYSQL
#ifdef MS_SQL
        conn->connect("MS_SQLTest", nullptr, nullptr);
#endif // MS_SQL
#ifdef INFORMIX
        conn->connect("INFORMIX", nullptr, nullptr);
#endif

        conn->setAutoCommit(true);

        dblib::DbAccess db;
        db.setConnection(getDBConnection());

        createTable(db);
        
        res = RUN_ALL_TESTS();

        dropTable(db);

        conn->disconnect();
    }
    catch (odbc::Exception& ex) {
            std::cout << ex.what() << std::endl; 
            res = 1;
    }
    return res;
}