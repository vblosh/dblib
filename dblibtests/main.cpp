#include <UnitTest++.h>
#include <iostream>
#include <string>
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
   const char * createTableStm = "CREATE TABLE test1 (boolean BIT, int16 SMALLINT, int32 INT, int64 BIGINT"
       ", float32 REAL, float64 FLOAT, decimal DECIMAL(18, 8)"
       ", string1 CHAR(16), string2 VARCHAR(128), nstring1 NCHAR(16), nstring2 NVARCHAR(128)"
       ", date DATE, time TIME, dateTime DATETIME2"
       ", binary1 BINARY(6), binary2 VARBINARY(3));";
    db.execute(createTableStm);
}

void dropTable(dblib::DbAccess& db)
{
    const char* dropTableStm = "DROP TABLE test1;";
    db.execute(dropTableStm);
}

int main( int argc, char *argv[] )
{
    int res = 0;
    try
    {
        odbc::EnvironmentRef env = odbc::Environment::create();
        conn = env->createConnection();
        conn->connect("MySQLTest", nullptr, nullptr);
//        conn->connect("testDB", nullptr, nullptr);
        conn->setAutoCommit(true);

        dblib::DbAccess db;
        db.setConnection(getDBConnection());

        createTable(db);

        int res = UnitTest::RunAllTests();

        dropTable(db);

        conn->disconnect();
    }
    catch (odbc::Exception& ex) {
            std::cout << ex.what() << std::endl; 
            res = 1;
    }
    return res;
}