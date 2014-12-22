/*
 [auto_generated]
 const_step_range.cpp

 [begin_description]
 tba.
 [end_description]

 Copyright 2009-2012 Karsten Ahnert
 Copyright 2009-2012 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <boost/config.hpp>
#ifdef BOOST_MSVC
    #pragma warning(disable:4996)
#endif

#define BOOST_TEST_MODULE odeint_const_step_range

#include <boost/numeric/odeint/range/const_step_range.hpp>
#include <boost/numeric/odeint/stepper/runge_kutta4.hpp>

#include <boost/test/unit_test.hpp>

#include <range/v3/view/take.hpp>
#include <range/v3/algorithm/for_each.hpp> 


#include <iostream>

using namespace boost::unit_test;
using namespace boost::numeric::odeint;

const double sigma = 10.0;
const double R = 28.0;
const double b = 8.0 / 3.0;

struct lorenz
{
    template< typename State , typename Deriv , typename Time >
    void operator()( const State& x , Deriv& dxdt , Time dt ) const
    {
        dxdt[0] = 1.0 ;
    }
};

struct printer 
{
    template< typename S >
    void operator()( S const& x ) const
    {
        std::cout << x[0] << "\n";
    }
};



BOOST_AUTO_TEST_SUITE( const_step_range_test )

BOOST_AUTO_TEST_CASE( test_rk4 )
{
    using state_type = std::array< double , 1 >;
    
    runge_kutta4< state_type > stepper;
    state_type x {{ 10.0 }};

    auto r = make_const_step_range( stepper , lorenz {} , x , 0.0 , 0.01 );
    auto r2 = ranges::view::take( r , 10 );

    ranges::for_each( r2 , []( state_type const& x ) {
            // std::cout << x[0] << " " << & ( x ) << std::endl;
        } );

    BOOST_CHECK_CLOSE( 10.0 , x[0] , 1.0e-10 );
    BOOST_CHECK_CLOSE( 10.09 , r.value()[0] , 1.0e-10 );
}

BOOST_AUTO_TEST_CASE( test_rk4_ref )
{
    using state_type = std::array< double , 1 >;
    
    runge_kutta4< state_type > stepper;
    state_type x {{ 10.0 }};

    auto r = make_const_step_range( stepper , lorenz {} , boost::ref( x ) , 0.0 , 0.01 );
    auto r2 = ranges::view::take( r , 10 );

    ranges::for_each( r2 , []( state_type const& x ) {
            std::cout << x[0] << "\n";
        } );

    // BOOST_CHECK_CLOSE( 10.09 , x[0] , 1.0e-10 );
    // BOOST_CHECK_CLOSE( 10.09 , r.value()[0] , 1.0e-10 );
}


BOOST_AUTO_TEST_SUITE_END()
