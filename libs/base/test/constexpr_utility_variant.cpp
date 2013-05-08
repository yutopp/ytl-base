#include <boost/test/unit_test.hpp>

#include <string>

#include <ytl/base/constexpr_utility/variant.hpp>

////////////////////////////////////////////////////////////////////////////////
//
template<typename T>
struct hoge_visitor
{
    typedef bool    result_type;

    YTL_CONSTEXPR hoge_visitor( T&& v )
        : val_( v )
    {}

    YTL_CONSTEXPR auto operator()( T const& t ) const -> result_type
    {
        return t == val_;
    }

    template<typename U>
    YTL_CONSTEXPR auto operator()( U const& ) const -> result_type
    {
        return false;
    }

    T val_;
};

BOOST_AUTO_TEST_CASE( variant )
{
#if !defined(YTL_OLD_IMPL)
    {
        static_assert(
            std::is_same<
                decltype( ytl::cu::find_type_index<bool, bool, int, double>() ),
                ytl::cu::detail::found_type_index_value<true, 0u>
            >::value,
            "" );
        static_assert(
            std::is_same<
                decltype( ytl::cu::find_type_index<int, bool, int, double>() ),
                ytl::cu::detail::found_type_index_value<true, 1u>
            >::value,
            "" );
        static_assert(
            std::is_same<
                decltype( ytl::cu::find_type_index<double, bool, int, double>() ),
                ytl::cu::detail::found_type_index_value<true, 2u>
            >::value,
            "" );

        static_assert(
            std::is_same<
                decltype( ytl::cu::find_type_index<char const*, bool, std::string>() ),
                ytl::cu::detail::found_type_index_value<true, 0u>
            >::value,
            "" );
    }

    {
        YTL_CONSTEXPR ytl::cu::variant<bool, int, double> const p( true );
        static_assert( p.which() == 0, "" );
        static_assert( p.apply_visitor( hoge_visitor<bool>( true ) ), "" );
        static_assert( ytl::cu::apply_visitor( hoge_visitor<bool>( true ), p ), "" );
    }

    {
        bool b = false;
        ytl::cu::variant<bool, int, double> const p( b );
        BOOST_CHECK_EQUAL( p.which(), 0 );
        BOOST_CHECK( p.apply_visitor( hoge_visitor<bool>( false ) ) );
        BOOST_CHECK( ytl::cu::apply_visitor( hoge_visitor<bool>( false ), p ) );
    }

    {
        YTL_CONSTEXPR auto const p = ytl::cu::variant<bool, int, double>( 72 );
        static_assert( p.which() == 1, "" );
        static_assert( p.apply_visitor( hoge_visitor<int>( 72 ) ), "" );
        static_assert( ytl::cu::apply_visitor( hoge_visitor<int>( 72 ), p ), "" );
        static_assert( !p.apply_visitor( hoge_visitor<int>( 123 ) ), "" );
        static_assert( !ytl::cu::apply_visitor( hoge_visitor<int>( 123 ), p ), "" );
        static_assert( !p.apply_visitor( hoge_visitor<bool>( true ) ), "" );
        static_assert( !ytl::cu::apply_visitor( hoge_visitor<bool>( true ), p ), "" );
    }

    {
        YTL_CONSTEXPR auto const p = ytl::cu::variant<bool, int, double>( 3.14 );
        static_assert( p.which() == 2, "" );
        static_assert( p.apply_visitor( hoge_visitor<double>( 3.14 ) ), "" );
        static_assert( ytl::cu::apply_visitor( hoge_visitor<double>( 3.14 ), p ), "" );
    }
#else
    BOOST_TEST_MESSAGE( "Skipped...( defined YTL_OLD_IMPL )" );
#endif
}

////////////////////////////////////////////////////////////////////////////////
//
boost::unit_test::test_suite* init_unit_test_suite( int, char* [] )
{
    boost::unit_test::framework::master_test_suite().p_name.value = "ytl.base constexpr_utility variant";

    return nullptr;
}