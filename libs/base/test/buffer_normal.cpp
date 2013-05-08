#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp> 

#include <ytl/base/buffer/binary_buffer.hpp>
#include <ytl/base/buffer/binary_buffer_stl.hpp>

////////////////////////////////////////////////////////////////////////////////
//
BOOST_AUTO_TEST_CASE( base )
{
    ytl::binary_buffer s;

    // expected
    const ytl::byte_t binx[] = { 0x01, 0x02, 0x03, 0x04 };

    // operator << []
    s << binx;

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


    // expected
    const ytl::byte_t binxx[] = { 0x01, 0x02, 0x03, 0x04, 0x01, 0x02, 0x03, 0x04 };

    // double
    s << s;

    // size check
    BOOST_CHECK_EQUAL( s.size(), 8u );

    // expression check
    BOOST_CHECK( std::equal( s.data(), s.data() + s.size(), binxx ) );

    // expression check
    BOOST_CHECK( std::equal( s.begin(), s.end(), binxx ) );

    // access check
    BOOST_CHECK_EQUAL( s[0], 0x01 );
    BOOST_CHECK_EQUAL( s[1], 0x02 );
    BOOST_CHECK_EQUAL( s[2], 0x03 );
    BOOST_CHECK_EQUAL( s[3], 0x04 );
    BOOST_CHECK_EQUAL( s[4], 0x01 );
    BOOST_CHECK_EQUAL( s[5], 0x02 );
    BOOST_CHECK_EQUAL( s[6], 0x03 );
    BOOST_CHECK_EQUAL( s[7], 0x04 );

    // debug output test
    {
        auto const cs = "[ '0x01' '0x02' '0x03' '0x04' '0x01' '0x02' '0x03' '0x04' ]";
        boost::test_tools::output_test_stream os;
        os << s;
        BOOST_CHECK( os.check_length( std::strlen( cs ), false ) );
        BOOST_CHECK( os.is_equal( cs ) );
    }

    // binary output test
    {
        boost::test_tools::output_test_stream os;
        os <<= s;
        BOOST_CHECK( os.check_length( 8, false ) );
        BOOST_CHECK_EQUAL( os.str()[0], 0x01 );
        BOOST_CHECK_EQUAL( os.str()[1], 0x02 );
        BOOST_CHECK_EQUAL( os.str()[2], 0x03 );
        BOOST_CHECK_EQUAL( os.str()[3], 0x04 );
        BOOST_CHECK_EQUAL( os.str()[4], 0x01 );
        BOOST_CHECK_EQUAL( os.str()[5], 0x02 );
        BOOST_CHECK_EQUAL( os.str()[6], 0x03 );
        BOOST_CHECK_EQUAL( os.str()[7], 0x04 );
    }
}

////////////////////////////////////////////////////////////////////////////////
//
boost::unit_test::test_suite* init_unit_test_suite( int, char* [] )
{
    boost::unit_test::framework::master_test_suite().p_name.value = "ytl.base buffer normal test";

    return nullptr;
}