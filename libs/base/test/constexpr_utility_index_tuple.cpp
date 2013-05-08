#include <boost/test/unit_test.hpp>

#include <ytl/base/constexpr_utility/index_tuple.hpp>

////////////////////////////////////////////////////////////////////////////////
//
BOOST_AUTO_TEST_CASE( index_tuple )
{
#if !defined(YTL_OLD_IMPL)
    {
        static_assert( std::is_same<decltype( ytl::cu::make_index_tuple<int, 0, 0>() ), ytl::cu::index_tuple<int>>::value, "" );
        static_assert( std::is_same<decltype( ytl::cu::make_index_tuple<int, 3, 0>() ), ytl::cu::index_tuple<int>>::value, "" );
        static_assert( std::is_same<decltype( ytl::cu::make_index_tuple<int, 0, 5, 1>() ), ytl::cu::index_tuple<int, 0, 1, 2, 3, 4>>::value, "" );
        static_assert( std::is_same<decltype( ytl::cu::make_index_tuple<int, 0, 9, 2>() ), ytl::cu::index_tuple<int, 0, 2, 4, 6, 8>>::value, "" );
    }
#else
    BOOST_TEST_MESSAGE( "Skipped...( defined YTL_OLD_IMPL )" );
#endif
}

////////////////////////////////////////////////////////////////////////////////
//
boost::unit_test::test_suite* init_unit_test_suite( int, char* [] )
{
    boost::unit_test::framework::master_test_suite().p_name.value = "ytl.base constexpr_utility index_tuple";

    return nullptr;
}