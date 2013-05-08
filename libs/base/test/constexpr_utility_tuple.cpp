#include <boost/test/unit_test.hpp>

#include <ytl/base/constexpr_utility/tuple.hpp>

////////////////////////////////////////////////////////////////////////////////
//
BOOST_AUTO_TEST_CASE( tuple )
{
#if !defined(YTL_OLD_IMPL)
    {
        YTL_CONSTEXPR ytl::cu::tuple<bool, int, double> const s( true, 72, 3.14  );
        static_assert( ytl::cu::get<0>( s ) == true, "" );
        static_assert( ytl::cu::get<1>( s ) == 72, "" );
        static_assert( ytl::cu::get<2>( s ) == 3.14, "" );

        static_assert( ytl::cu::tuple<bool, int, double>::element_num == 3, "" );
    }

    {
        ytl::cu::tuple<bool, int, double> const s( true, 72, 3.14  );
        BOOST_CHECK_EQUAL( ytl::cu::get<0>( s ), true );
        BOOST_CHECK_EQUAL( ytl::cu::get<1>( s ), 72 );
        BOOST_CHECK_EQUAL( ytl::cu::get<2>( s ), 3.14 );
    }
#else
    BOOST_TEST_MESSAGE( "Skipped...( defined YTL_OLD_IMPL )" );
#endif
}

////////////////////////////////////////////////////////////////////////////////
//
boost::unit_test::test_suite* init_unit_test_suite( int, char* [] )
{
    boost::unit_test::framework::master_test_suite().p_name.value = "ytl.base constexpr_utility tuple";

    return nullptr;
}