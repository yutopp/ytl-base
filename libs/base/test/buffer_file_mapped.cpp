#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp> 

#include <ytl/base/buffer/file_mapped_binary_buffer.hpp>
#include <ytl/base/buffer/binary_buffer_stl.hpp>

////////////////////////////////////////////////////////////////////////////////
//
BOOST_AUTO_TEST_CASE( base_buffer_load )
{
    ytl::file_mapped_binary_buffer s( "binary_01_02_03_04.bin" );

    // expected
    const char binx[] = { 0x01, 0x02, 0x03, 0x04 };

    // size check
    BOOST_CHECK_EQUAL( s.size(), 4u );

    // expression check
    BOOST_CHECK( std::equal( s.data(), s.data() + s.size(), binx ) );

    // expression check
    BOOST_CHECK( std::equal( s.begin(), s.end(), binx ) );

    // access check
    BOOST_CHECK_EQUAL( s[0], 0x01 );
    BOOST_CHECK_EQUAL( s[1], 0x02 );
    BOOST_CHECK_EQUAL( s[2], 0x03 );
    BOOST_CHECK_EQUAL( s[3], 0x04 );

    // debug output test
    {
        auto const cs = "[ '0x01' '0x02' '0x03' '0x04' ]";
        boost::test_tools::output_test_stream os;
        os << s;
        BOOST_CHECK( os.check_length( std::strlen( cs ), false ) );
        BOOST_CHECK( os.is_equal( cs ) );
    }

    // binary output test
    {
        boost::test_tools::output_test_stream os;
        os <<= s;
        BOOST_CHECK( os.check_length( 4, false ) );
        BOOST_CHECK_EQUAL( os.str()[0], 0x01 );
        BOOST_CHECK_EQUAL( os.str()[1], 0x02 );
        BOOST_CHECK_EQUAL( os.str()[2], 0x03 );
        BOOST_CHECK_EQUAL( os.str()[3], 0x04 );
    }
}

////////////////////////////////////////////////////////////////////////////////
//
BOOST_AUTO_TEST_CASE( base_buffer_not_exist )
{
    BOOST_CHECK_THROW(
        ytl::file_mapped_binary_buffer( "nonexist file name" ),
        boost::interprocess::interprocess_exception
        );
}

////////////////////////////////////////////////////////////////////////////////
//
BOOST_AUTO_TEST_CASE( base_buffer_move )
{
    ytl::file_mapped_binary_buffer s( "binary_01_02_03_04.bin" );

    auto ms( std::move( s ) );
    BOOST_CHECK_EQUAL( ms.size(), 4u );

    // access check
    BOOST_CHECK_EQUAL( s[0], 0x01 );
    BOOST_CHECK_EQUAL( s[1], 0x02 );
    BOOST_CHECK_EQUAL( s[2], 0x03 );
    BOOST_CHECK_EQUAL( s[3], 0x04 );
}

////////////////////////////////////////////////////////////////////////////////
//
boost::unit_test::test_suite* init_unit_test_suite( int, char* [] )
{
    boost::unit_test::framework::master_test_suite().p_name.value = "ytl.base buffer file_mapped test";

    return nullptr;
}