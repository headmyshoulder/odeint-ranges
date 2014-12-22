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

#include <boost/numeric/odeint/range/const_step_range.hpp>
#include <boost/numeric/odeint/stepper/runge_kutta4.hpp>

#include <range/v3/view/take.hpp>
#include <range/v3/algorithm/for_each.hpp>

#include <iostream>

namespace odeint = boost::numeric::odeint;

const double sigma = 10.0;
const double R = 28.0;
const double b = 8.0 / 3.0;

struct lorenz
{
    template< typename State , typename Deriv , typename Time >
    void operator()( const State& x , Deriv& dxdt , Time dt ) const
    {
        dxdt[0] = sigma * ( x[1] - x[0] );
        dxdt[1] = R * x[0] - x[1] - x[0] * x[2];
        dxdt[2] = -b * x[2] + x[0] * x[1];
    }
};

struct printer 
{
    template< typename S >
    void operator()( S const& x ) const
    {
        std::cout << x[0] << " " << x[1] << " " << x[2] << "\n";
    }
};


int main( int argc , char *argv[] )
{
    using namespace boost::numeric::odeint;

    using state_type = std::array< double , 3 >;
    
    runge_kutta4< state_type > stepper;
    state_type x {{ 10.0 , 10.0 , 10.0 }};

    auto r = make_const_step_range( stepper , lorenz {} , x , 0.0 , 0.01 );
    auto r2 = ranges::view::take( r , 10 );

    ranges::for_each( r2 , []( state_type const& x ) {
            std::cout << x[0] << " " << x[1] << " " << x[2] << "\n";
        } );

    // ranges::for_each( r , printer {} );

    
    return 0;
}
