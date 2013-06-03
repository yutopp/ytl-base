#include <boost/test/unit_test.hpp>

#include <ytl/base/buffer/short_buffer.hpp>

////////////////////////////////////////////////////////////////////////////////
//
BOOST_AUTO_TEST_CASE( expression )
{
#if defined(YTL_HAS_CONSTEXPR)
    {
        typedef ytl::detail::short_buffer<std::size_t, 6> buffer_t;
        static_assert( buffer_t( ytl::detail::short_buffer_construct ).size() == 0u, "" );
        static_assert( buffer_t( ytl::detail::short_buffer_construct, 1 ).size() == 1u, "" );
        static_assert( buffer_t( ytl::detail::short_buffer_construct, 1, 2 ).size() == 2u, "" );
        static_assert( buffer_t( ytl::detail::short_buffer_construct, 1, 2, 3 ).size() == 3u, "" );
        static_assert( buffer_t( ytl::detail::short_buffer_construct, 1, 2, 3, 4 ).size() == 4u, "" );
        static_assert( buffer_t( ytl::detail::short_buffer_construct, 1, 2, 3, 4, 5 ).size() == 5u, "" );
        static_assert( buffer_t( ytl::detail::short_buffer_construct, 1, 2, 3, 4, 5, 6 ).size() == 6u, "" );
    }

    {
        static_assert( ytl::make_short_buffer().size() == 0u, "" );
        static_assert( ytl::make_short_buffer( 1 ).size() == 1u, "" );
        static_assert( ytl::make_short_buffer( 1, 2 ).size() == 2u, "" );
        static_assert( ytl::make_short_buffer( 1, 2, 3 ).size() == 3u, "" );
        static_assert( ytl::make_short_buffer( 1, 2, 3, 4 ).size() == 4u, "" );
        static_assert( ytl::make_short_buffer( 1, 2, 3, 4, 5 ).size() == 5u, "" );
        static_assert( ytl::make_short_buffer( 1, 2, 3, 4, 5, 6 ).size() == 6u, "" );
    }

//    static_assert( x86::detail::mod_rm_sib_disp_buffer( detail::buffer_construct, 1, 2, 3, 4, 5, 6 ).size() == 6, "" );
//
//    static_assert( x86::detail::mod_rm_sib_disp_buffer( detail::buffer_construct, 1, 2, 3, 4, 5, 6 ) == _b( 1, 2, 3, 4, 5, 6 ), "" );
//    static_assert( x86::detail::mod_rm_sib_disp_buffer( detail::buffer_construct, 1, 2 ) != _b( 1, 2, 3, 4, 5, 6 ), "" );
//    static_assert( x86::detail::mod_rm_sib_disp_buffer( detail::buffer_construct, 1, 2, 3, 4, 5, 6 ) != _b( 1, 2 ), "" );
//    static_assert( x86::detail::mod_rm_sib_disp_buffer( detail::buffer_construct, 1, 2 ) != _b( 2, 1 ), "" );
//
//    static_assert( x86::detail::instruction_buffer( detail::buffer_construct, 1, 2, 3, 4, 5, 6 ) == _b( 1, 2, 3, 4, 5, 6 ), "" );

#endif
    {
        typedef ytl::detail::short_buffer<std::size_t, 6> buffer_t;
        BOOST_CHECK_EQUAL( buffer_t( ytl::detail::short_buffer_construct ).size(), 0u );
        BOOST_CHECK_EQUAL( buffer_t( ytl::detail::short_buffer_construct, 1 ).size(), 1u );
        BOOST_CHECK_EQUAL( buffer_t( ytl::detail::short_buffer_construct, 1, 2 ).size(), 2u );
        BOOST_CHECK_EQUAL( buffer_t( ytl::detail::short_buffer_construct, 1, 2, 3 ).size(), 3u );
        BOOST_CHECK_EQUAL( buffer_t( ytl::detail::short_buffer_construct, 1, 2, 3, 4 ).size(), 4u );
        BOOST_CHECK_EQUAL( buffer_t( ytl::detail::short_buffer_construct, 1, 2, 3, 4, 5 ).size(), 5u );
        BOOST_CHECK_EQUAL( buffer_t( ytl::detail::short_buffer_construct, 1, 2, 3, 4, 5, 6 ).size(), 6u );
    }

    {
        BOOST_CHECK_EQUAL( ytl::make_short_buffer().size(), 0u );
        BOOST_CHECK_EQUAL( ytl::make_short_buffer( 1 ).size(), 1u );
        BOOST_CHECK_EQUAL( ytl::make_short_buffer( 1, 2 ).size(), 2u );
        BOOST_CHECK_EQUAL( ytl::make_short_buffer( 1, 2, 3 ).size(), 3u );
        BOOST_CHECK_EQUAL( ytl::make_short_buffer( 1, 2, 3, 4 ).size(), 4u );
        BOOST_CHECK_EQUAL( ytl::make_short_buffer( 1, 2, 3, 4, 5 ).size(), 5u );
        BOOST_CHECK_EQUAL( ytl::make_short_buffer( 1, 2, 3, 4, 5, 6 ).size(), 6u );
    }

    {
        typedef ytl::detail::short_buffer<std::size_t, 6> buffer_t;
        BOOST_CHECK( buffer_t( ytl::detail::short_buffer_construct, 1, 2, 3, 4, 5, 6 ) == ytl::make_short_buffer( 1, 2, 3, 4, 5, 6 ) );
        BOOST_CHECK( buffer_t( ytl::detail::short_buffer_construct, 1, 2 ) != ytl::make_short_buffer( 1, 2, 3, 4, 5, 6 ) );
        BOOST_CHECK( buffer_t( ytl::detail::short_buffer_construct, 1, 2, 3, 4, 5, 6 ) != ytl::make_short_buffer( 1, 2 ) );
        BOOST_CHECK( buffer_t( ytl::detail::short_buffer_construct, 1, 2 ) != ytl::make_short_buffer( 2, 1 ) );

        BOOST_CHECK( buffer_t( ytl::detail::short_buffer_construct, 1, 2, 3, 4, 5, 6 ) == ytl::make_short_buffer( 1, 2, 3, 4, 5, 6 ) );
    }
}

////////////////////////////////////////////////////////////////////////////////
//
boost::unit_test::test_suite* init_unit_test_suite( int, char* [] )
{
    boost::unit_test::framework::master_test_suite().p_name.value = "ytl.base buffer short test";

    return nullptr;
}