#pragma once
#include <odbc/Types.h>
#include <odbc/PreparedStatement.h>
#include <odbc/ResultSet.h>


namespace dblib
{ 

template<typename T>
struct db_trait
{
    void setValue(odbc::PreparedStatementRef& stm, unsigned short pos, T& value)
    {
        static_assert(false, "not inplemented!");
    }
    const T& getValue(odbc::ResultSetRef& rst, unsigned short pos)
    {
        static_assert(false,"not inplemented!");
    }
};

template<>
struct db_trait<odbc::Boolean>
{
    void setValue(odbc::PreparedStatementRef& stm, unsigned short pos, odbc::Boolean& value)
    {
        stm->setBoolean(pos, value);
    }
    const odbc::Boolean getValue(odbc::ResultSetRef& rst, unsigned short pos)
    {
        return rst->getBoolean(pos);
    }
};

template<>
struct db_trait<odbc::Short>
{
    void setValue(odbc::PreparedStatementRef& stm, unsigned short pos, odbc::Short& value)
    {
        stm->setShort(pos, value);
    }
    const odbc::Short getValue(odbc::ResultSetRef& rst, unsigned short pos)
    {
        return rst->getShort(pos);
    }
};

template<>
struct db_trait<odbc::Int>
{
    void setValue(odbc::PreparedStatementRef& stm, unsigned short pos, odbc::Int& value)
    {
        stm->setInt(pos, value);
    }
    const odbc::Int getValue(odbc::ResultSetRef& rst, unsigned short pos)
    {
        return rst->getInt(pos);
    }
};

template<>
struct db_trait<odbc::Long>
{
    void setValue(odbc::PreparedStatementRef& stm, unsigned short pos, odbc::Long& value)
    {
        stm->setLong(pos, value);
    }
    const odbc::Long getValue(odbc::ResultSetRef& rst, unsigned short pos)
    {
        return rst->getLong(pos);
    }
};

template<>
struct db_trait<odbc::Float>
{
    void setValue(odbc::PreparedStatementRef& stm, unsigned short pos, odbc::Float& value)
    {
        stm->setFloat(pos, value);
    }
    const odbc::Float getValue(odbc::ResultSetRef& rst, unsigned short pos)
    {
        return rst->getFloat(pos);
    }
};

template<>
struct db_trait<odbc::Double>
{
    void setValue(odbc::PreparedStatementRef& stm, unsigned short pos, odbc::Double& value)
    {
        stm->setDouble(pos, value);
    }
    const odbc::Double getValue(odbc::ResultSetRef& rst, unsigned short pos)
    {
        return rst->getDouble(pos);
    }
};

template<>
struct db_trait<odbc::Decimal>
{
    void setValue(odbc::PreparedStatementRef& stm, unsigned short pos, odbc::Decimal& value)
    {
        stm->setDecimal(pos, value);
    }
    const odbc::Decimal getValue(odbc::ResultSetRef& rst, unsigned short pos)
    {
        return rst->getDecimal(pos);
    }
};

template<>
struct db_trait<odbc::String>
{
    void setValue(odbc::PreparedStatementRef& stm, unsigned short pos, odbc::String& value)
    {
        stm->setString(pos, value);
    }
    odbc::String getValue(odbc::ResultSetRef& rst, unsigned short pos)
    {
        return rst->getString(pos);
    }
};

template<>
struct db_trait<odbc::NString>
{
    void setValue(odbc::PreparedStatementRef& stm, unsigned short pos, odbc::NString& value)
    {
        stm->setNString(pos, value);
    }
    odbc::NString getValue(odbc::ResultSetRef& rst, unsigned short pos)
    {
        return rst->getNString(pos);
    }
};

template<>
struct db_trait<odbc::Date>
{
    void setValue(odbc::PreparedStatementRef& stm, unsigned short pos, odbc::Date& value)
    {
        stm->setDate(pos, value);
    }
    const odbc::Date getValue(odbc::ResultSetRef& rst, unsigned short pos)
    {
        return rst->getDate(pos);
    }
};

template<>
struct db_trait<odbc::Time>
{
    void setValue(odbc::PreparedStatementRef& stm, unsigned short pos, odbc::Time& value)
    {
        stm->setTime(pos, value);
    }
    const odbc::Time getValue(odbc::ResultSetRef& rst, unsigned short pos)
    {
        return rst->getTime(pos);
    }
};

template<>
struct db_trait<odbc::Timestamp>
{
    void setValue(odbc::PreparedStatementRef& stm, unsigned short pos, odbc::Timestamp& value)
    {
        stm->setTimestamp(pos, value);
    }
    const odbc::Timestamp getValue(odbc::ResultSetRef& rst, unsigned short pos)
    {
        return rst->getTimestamp(pos);
    }
};

template<>
struct db_trait<odbc::Binary>
{
    void setValue(odbc::PreparedStatementRef& stm, unsigned short pos, odbc::Binary& value)
    {
        stm->setBinary(pos, value);
    }
    const odbc::Binary getValue(odbc::ResultSetRef& rst, unsigned short pos)
    {
        return rst->getBinary(pos);
    }
};

}