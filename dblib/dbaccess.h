#pragma once
#include <odbc/Connection.h>
#include <tuple>
#include <optional>

#include "db_traits.h"

namespace dblib
{
    class DbAccess
    {
    public:
        void setConnection(odbc::ConnectionRef activeConn)
        {
            odbcConn = activeConn;
        }

        template<typename... Args>
        size_t execute(const char * odbcStatement, Args&... args)
        {
            odbc::PreparedStatementRef stm = odbcConn->prepareStatement(odbcStatement);
            setParameter<1, Args...>(stm, args...);

            return stm->executeUpdate();
        }

        template <typename... Results, typename... Args>
        std::optional<std::tuple<Results...>> executeSingleQuery(const char * odbcStatement, Args&... args)
        {
            odbc::PreparedStatementRef stm = odbcConn->prepareStatement(odbcStatement);
            setParameter<1, Args...>(stm, args...);

            odbc::ResultSetRef results = stm->executeQuery();
            if (results->next())
            {
                return createTuple<1, Results...>(results);
            }

            return std::nullopt;
        }

        template <typename... Results, typename... Args>
        std::vector<std::tuple<Results...>> executeQuery(const char * odbcStatement, Args&... args)
        {
            odbc::PreparedStatementRef stm = odbcConn->prepareStatement(odbcStatement);
            setParameter<1, Args...>(stm, args...);

            std::vector<std::tuple<Results...>> vec;
            odbc::ResultSetRef results = stm->executeQuery();
            while (results->next())
            {
                vec.push_back(createTuple<1, Results...>(results));
            }

            return vec;
        }

        template <typename... Results, typename... Args>
        std::vector<std::tuple<Results...>> executeQueryLimit(const char * odbcStatement, size_t limit, Args&... args)
        {
            odbc::PreparedStatementRef stm = odbcConn->prepareStatement(odbcStatement);
            setParameter<1, Args...>(stm, args...);

            std::vector<std::tuple<Results...>> vec;
            vec.reserve(limit);
            odbc::ResultSetRef results = stm->executeQuery();
            for (size_t i = 0; i < limit; i++)
            {
                if (results->next())
                    vec.push_back(createTuple<1, Results...>(results));
                else
                    break;
            }

            return vec;
        }

    private:

        template <unsigned int N>
        void setParameter(odbc::PreparedStatementRef&) { }

        template<unsigned int N, typename T, typename... Args>
        void setParameter(odbc::PreparedStatementRef& stm, T& nextArgs, Args&... args)
        {
            db_trait<T>().setValue(stm, N, nextArgs);
            setParameter<N + 1, Args...>(stm, args...);
        }

        template <unsigned int N>
        std::tuple<> createTuple(odbc::ResultSetRef&) 
        {
            return std::tuple<>();
        }

        template <unsigned int N, class T, class... Tail>
        std::tuple<T, Tail...> createTuple(odbc::ResultSetRef& set)
        {
            T cur = db_trait<T>().getValue(set, N);
            return std::tuple_cat(std::tuple<T>(cur), createTuple<N + 1, Tail...>(set));
        }

        odbc::ConnectionRef odbcConn;
    };

}

