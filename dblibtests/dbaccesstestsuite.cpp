#include <iostream>
#include <tuple>
#include <utility>

#include <UnitTest++.h>

#include <odbc/Types.h>
#include <odbc/RefCounted.h>
#include <odbc/Exception.h>
#include <odbc/Connection.h>

#include <dbaccess.h>
#include "main.h"

#define CATCH_odbc_EXP() catch (odbc::Exception & ex) { \
            std::cout << ex.what() << std::endl; \
            throw; }\


struct dbaccessFixture
{
    dbaccessFixture()
    {
        db.setConnection(getDBConnection());
        insertRow();
    }

    ~dbaccessFixture()
    {
        truncateTable();
    }

    void insertRow()
    {

        for (int i = 0; i < NUM_ROWS; i++)
        {
            odbc::Short int16val = *int16 + i;
            const char* insertRowStm = "INSERT INTO test1 (boolean, int16, int32, int64, float32, float64, decimal, string1, string2, nstring1, nstring2, date, time, dateTime, binary1, binary2)"
                " VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
            size_t affectedRec = db.execute(insertRowStm, boolean, int16val, int32, int64, float32, float64, decimal, string1, string2, nstring1, nstring2, date, time, dateTime, binary1, binary2);

            CHECK_EQUAL(1, affectedRec);
        }
    }

    void truncateTable()
    {
        try
        {
            const char* truncateStm = "TRUNCATE TABLE test1";
            db.execute(truncateStm);
        }
        catch (odbc::Exception& ex) {
            std::cout << ex.what() << std::endl;
        }
    }

    const int NUM_ROWS = 3;

    dblib::DbAccess db;

    odbc::Boolean boolean = true;
    odbc::Short int16 = 16;
    odbc::Int int32 = 32;
    odbc::Long int64 = 64;
    odbc::String string1 = std::string("string1         ");
    odbc::String string2 = std::string("string2");
    odbc::NString nstring1 = std::u16string(u"nstring1        ");
    odbc::NString nstring2 = std::u16string(u"nstring2");
    odbc::Float float32 = (float)3.2;
    odbc::Double float64 = 6.4;
    odbc::Decimal decimal = odbc::decimal((uint64_t)1234, 4, 3);
    odbc::Date date = odbc::date(2020, 1, 30);
    odbc::Time time = odbc::time(1, 2, 3);
    odbc::Timestamp dateTime = odbc::timestamp(2010, 2, 8, 4, 3, 2, 1);
    odbc::Binary binary1 = std::vector<char>{ 1, 2, 3, 4, 5, 6 };
    odbc::Binary binary2 = std::vector<char>{ 5, 6, 7 };
};

SUITE(dbaccessSuite)
{
    TEST_FIXTURE(dbaccessFixture, NotFound_Test1)
    {
        try
        {
            odbc::Short wrongKey = *int16 * 2;
            auto res = db.executeSingleQuery<odbc::Short>("SELECT int16 FROM test1 WHERE int16=?", wrongKey);
            CHECK(!res);
        }
        CATCH_odbc_EXP();
    }

    TEST_FIXTURE(dbaccessFixture, Boolean_Test1)
    {
        try
        {
            auto res = db.executeSingleQuery<odbc::Boolean>("SELECT boolean FROM test1 WHERE boolean=?", boolean);
            CHECK(res);
            CHECK_EQUAL(boolean, std::get<0>(*res));
        }
        CATCH_odbc_EXP();
    }

    TEST_FIXTURE(dbaccessFixture, Short_Test1)
    {
        try
        {
            auto res = db.executeSingleQuery<odbc::Short>("SELECT int16 FROM test1 WHERE int16=?", int16);
            CHECK(res);
            CHECK_EQUAL(int16, std::get<0>(*res));
        }
        CATCH_odbc_EXP();
    }

    TEST_FIXTURE(dbaccessFixture, Int_Test1)
    {
        try
        {
            auto res = db.executeSingleQuery<odbc::Int>("SELECT int32 FROM test1 WHERE int32=?", int32);
            CHECK(res);
            CHECK_EQUAL(int32, std::get<0>(*res));
        }
        CATCH_odbc_EXP();
    }

    TEST_FIXTURE(dbaccessFixture, Long_Test1)
    {
        try
        {
            auto res = db.executeSingleQuery<odbc::Long>("SELECT int64 FROM test1 WHERE int64=?", int64);
            CHECK(res);
            CHECK_EQUAL(int64, std::get<0>(*res));
        }
        CATCH_odbc_EXP();
    }

    TEST_FIXTURE(dbaccessFixture, Float_Test1)
    {
        try
        {
            auto res = db.executeSingleQuery<odbc::Float>("SELECT float32 FROM test1 WHERE float32=?", float32);
            CHECK(res);
            CHECK_EQUAL(float32, std::get<0>(*res));
        }
        CATCH_odbc_EXP();
    }

    TEST_FIXTURE(dbaccessFixture, Double_Test1)
    {
        try
        {
            auto res = db.executeSingleQuery<odbc::Double>("SELECT float64 FROM test1 WHERE float64=?", float64);
            CHECK(res);
            CHECK_EQUAL(float64, std::get<0>(*res));
        }
        CATCH_odbc_EXP();
    }

    TEST_FIXTURE(dbaccessFixture, Decimal_Test1)
    {
        try
        {
            auto res = db.executeSingleQuery<odbc::Decimal>("SELECT decimal FROM test1 WHERE decimal=?", decimal);
            CHECK(res);
            CHECK_EQUAL(decimal, std::get<0>(*res));
        }
        CATCH_odbc_EXP();
    }

    TEST_FIXTURE(dbaccessFixture, string1_Test1)
    {
        try
        {
            auto res = db.executeSingleQuery<odbc::String>("SELECT string1 FROM test1 WHERE string1=?", string1);
            CHECK(res);
            CHECK_EQUAL(string1, std::get<0>(*res));
        }
        CATCH_odbc_EXP();
    }

    TEST_FIXTURE(dbaccessFixture, string2_Test1)
    {
        try
        {
            auto res = db.executeSingleQuery<odbc::String>("SELECT string2 FROM test1 WHERE string2=?", string2);
            CHECK(res);
            CHECK_EQUAL(string2, std::get<0>(*res));
        }
        CATCH_odbc_EXP();
    }
    
    TEST_FIXTURE(dbaccessFixture, Date_Test1)
    {
        try
        {
            auto res = db.executeSingleQuery<odbc::Date>("SELECT date FROM test1 WHERE date=?", date);
            CHECK(res);
            CHECK_EQUAL(date, std::get<0>(*res));
        }
        CATCH_odbc_EXP();
    }

    TEST_FIXTURE(dbaccessFixture, Time_Test1)
    {
        try
        {
            auto res = db.executeSingleQuery<odbc::Time>("SELECT time FROM test1 WHERE time=?", time);
            CHECK(res);
            CHECK_EQUAL(time, std::get<0>(*res));
        }
        CATCH_odbc_EXP();
    }

    TEST_FIXTURE(dbaccessFixture, DateTime_Test1)
    {
        try
        {
            auto res = db.executeSingleQuery<odbc::Timestamp>("SELECT dateTime FROM test1 WHERE dateTime=?", dateTime);
            CHECK(res);
            CHECK_EQUAL(dateTime, std::get<0>(*res));
        }
        CATCH_odbc_EXP();
    }

    TEST_FIXTURE(dbaccessFixture, Binary_Test1)
    {
        try
        {
            auto res = db.executeSingleQuery<odbc::Binary>("SELECT binary1 FROM test1 WHERE binary1=?", binary1); 
            CHECK(res);
            CHECK_ARRAY_EQUAL(*binary1, *std::get<0>(*res), (*binary1).size());
        }
        CATCH_odbc_EXP();
    }

    TEST_FIXTURE(dbaccessFixture, Binary_Test2)
    {
        try
        {
            auto res = db.executeSingleQuery<odbc::Binary>("SELECT binary2 FROM test1 WHERE binary2=?", binary2);
            CHECK(res);
            CHECK_ARRAY_EQUAL(*binary2, *std::get<0>(*res), (*binary2).size());
        }
        CATCH_odbc_EXP();
    }

    TEST_FIXTURE(dbaccessFixture, Count_Test1)
    {
        try
        {
            auto res = db.executeSingleQuery<odbc::Long>("SELECT COUNT(*) FROM test1 WHERE time =?", time);
            CHECK(res);
            CHECK_EQUAL(NUM_ROWS, *std::get<0>(*res));
        }
        CATCH_odbc_EXP();
    }
 
    TEST_FIXTURE(dbaccessFixture, All_Test1)
    {
        try
        {
            auto res = db.executeSingleQuery<
                odbc::Boolean, odbc::Short, odbc::Int, odbc::Long
                , odbc::Float, odbc::Double, odbc::Decimal
                , odbc::String, odbc::String, odbc::NString, odbc::NString
                , odbc::Date, odbc::Time, odbc::Timestamp
                , odbc::Binary, odbc::Binary
                >
                ("SELECT boolean, int16, int32, int64"
                    ", float32, float64, decimal"
                    ", string1, string2, nstring1, nstring2"
                    ", date, time, dateTime"
                    ", binary1, binary2"
                    " FROM test1 WHERE boolean=?"
                    " AND int16=? AND int32=? AND int64=?"
                    " AND float32=? AND float64=? AND decimal=?"
                    " AND string1=? AND string2=? AND nstring1=? AND nstring2=?"
                    " AND date=? AND time=? AND dateTime=?"
                    " AND binary1=? AND binary2=?"
                    , boolean, int16, int32, int64
                    , float32, float64, decimal
                    , string1, string2, nstring1, nstring2
                    , date, time, dateTime
                    , binary1, binary2
                    );
            CHECK(res);
            CHECK_EQUAL(boolean, std::get<0>(*res));
            CHECK_EQUAL(int16, std::get<1>(*res));
            CHECK_EQUAL(int32, std::get<2>(*res));
            CHECK_EQUAL(int64, std::get<3>(*res));

            CHECK_EQUAL(float32, std::get<4>(*res));
            CHECK_EQUAL(float64, std::get<5>(*res));
            CHECK_EQUAL(decimal, std::get<6>(*res));

            CHECK_EQUAL(string1, std::get<7>(*res));
            CHECK_EQUAL(string2, std::get<8>(*res));
            CHECK_EQUAL(nstring1, std::get<9>(*res));
            CHECK_EQUAL(nstring2, std::get<10>(*res));

            CHECK_EQUAL(date, std::get<11>(*res));
            CHECK_EQUAL(time, std::get<12>(*res));
            CHECK_EQUAL(dateTime, std::get<13>(*res));

            CHECK_ARRAY_EQUAL(*binary1, *std::get<14>(*res), (*binary1).size());
            CHECK_ARRAY_EQUAL(*binary2, *std::get<15>(*res), (*binary2).size());
        }
        CATCH_odbc_EXP();
    }


    TEST_FIXTURE(dbaccessFixture, executeQuery_All_Test1)
    {
        try
        {
            auto res = db.executeQuery<
                odbc::Boolean, odbc::Short, odbc::Int, odbc::Long
                , odbc::Float, odbc::Double, odbc::Decimal
                , odbc::String, odbc::String, odbc::NString, odbc::NString
                , odbc::Date, odbc::Time, odbc::Timestamp
                , odbc::Binary, odbc::Binary
            >
                ("SELECT boolean, int16, int32, int64"
                    ", float32, float64, decimal"
                    ", string1, string2, nstring1, nstring2"
                    ", date, time, dateTime"
                    ", binary1, binary2"
                    " FROM test1 WHERE boolean=?"
                    " AND int32=? AND int64=?"
                    " AND float32=? AND float64=? AND decimal=?"
                    " AND string1=? AND string2=? AND nstring1=? AND nstring2=?"
                    " AND date=? AND time=? AND dateTime=?"
                    " AND binary1=? AND binary2=?"
                    " ORDER BY int16"
                    , boolean, int32, int64
                    , float32, float64, decimal
                    , string1, string2, nstring1, nstring2
                    , date, time, dateTime
                    , binary1, binary2
                    );
            CHECK_EQUAL(NUM_ROWS, res.size());
            for (size_t i = 0; i < NUM_ROWS; i++)
            {
                CHECK_EQUAL(boolean, std::get<0>(res[i]));
                CHECK_EQUAL(*int16 + i, *std::get<1>(res[i]));
                CHECK_EQUAL(int32, std::get<2>(res[i]));
                CHECK_EQUAL(int64, std::get<3>(res[i]));

                CHECK_EQUAL(float32, std::get<4>(res[i]));
                CHECK_EQUAL(float64, std::get<5>(res[i]));
                CHECK_EQUAL(decimal, std::get<6>(res[i]));

                CHECK_EQUAL(string1, std::get<7>(res[i]));
                CHECK_EQUAL(string2, std::get<8>(res[i]));
                CHECK_EQUAL(nstring1, std::get<9>(res[i]));
                CHECK_EQUAL(nstring2, std::get<10>(res[i]));

                CHECK_EQUAL(date, std::get<11>(res[i]));
                CHECK_EQUAL(time, std::get<12>(res[i]));
                CHECK_EQUAL(dateTime, std::get<13>(res[i]));

                CHECK_ARRAY_EQUAL(*binary1, *std::get<14>(res[i]), (*binary1).size());
                CHECK_ARRAY_EQUAL(*binary2, *std::get<15>(res[i]), (*binary2).size());
            }
        }
        CATCH_odbc_EXP();
    }

 
    TEST_FIXTURE(dbaccessFixture, executeQueryLimit_All_Test1)
    {
        const int limit = 2;

        try
        {
            auto res = db.executeQueryLimit <
                odbc::Boolean, odbc::Short, odbc::Int, odbc::Long
                , odbc::Float, odbc::Double, odbc::Decimal
                , odbc::String, odbc::String, odbc::NString, odbc::NString
                , odbc::Date, odbc::Time, odbc::Timestamp
                , odbc::Binary, odbc::Binary
            >
                ("SELECT boolean, int16, int32, int64"
                    ", float32, float64, decimal"
                    ", string1, string2, nstring1, nstring2"
                    ", date, time, dateTime"
                    ", binary1, binary2"
                    " FROM test1 WHERE boolean=?"
                    " AND int32=? AND int64=?"
                    " AND float32=? AND float64=? AND decimal=?"
                    " AND string1=? AND string2=? AND nstring1=? AND nstring2=?"
                    " AND date=? AND time=? AND dateTime=?"
                    " AND binary1=? AND binary2=?"
                    " ORDER BY int16"
                    , limit
                    , boolean, int32, int64
                    , float32, float64, decimal
                    , string1, string2, nstring1, nstring2
                    , date, time, dateTime
                    , binary1, binary2
                    );
            CHECK_EQUAL(limit, res.size());
            for (size_t i = 0; i < limit; i++)
            {
                CHECK_EQUAL(boolean, std::get<0>(res[i]));
                CHECK_EQUAL(*int16 + i, *std::get<1>(res[i]));
                CHECK_EQUAL(int32, std::get<2>(res[i]));
                CHECK_EQUAL(int64, std::get<3>(res[i]));

                CHECK_EQUAL(float32, std::get<4>(res[i]));
                CHECK_EQUAL(float64, std::get<5>(res[i]));
                CHECK_EQUAL(decimal, std::get<6>(res[i]));

                CHECK_EQUAL(string1, std::get<7>(res[i]));
                CHECK_EQUAL(string2, std::get<8>(res[i]));
                CHECK_EQUAL(nstring1, std::get<9>(res[i]));
                CHECK_EQUAL(nstring2, std::get<10>(res[i]));

                CHECK_EQUAL(date, std::get<11>(res[i]));
                CHECK_EQUAL(time, std::get<12>(res[i]));
                CHECK_EQUAL(dateTime, std::get<13>(res[i]));

                CHECK_ARRAY_EQUAL(*binary1, *std::get<14>(res[i]), (*binary1).size());
                CHECK_ARRAY_EQUAL(*binary2, *std::get<15>(res[i]), (*binary2).size());
            }
        }
        CATCH_odbc_EXP();
    }
    
} // end SUITE(   )

