/*
  [auto_generated]
  boost/numeric/odeint/range/state_policies.hpp

  [begin_description]
  tba.
  [end_description]

  Copyright 2009-2012 Karsten Ahnert
  Copyright 2009-2012 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_RANGE_STATE_POLICIES_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_RANGE_STATE_POLICIES_HPP_INCLUDED

#include <utility>


namespace boost {
namespace numeric {
namespace odeint {

struct state_policy
{
    template< typename State , typename Time >
    State const& operator()( State const& state , Time t ) const
    {
        return state;
    }
};

struct state_and_time_policy
{
    template< typename State , typename Time >
    std::pair< State const& , Time > operator()( State const& state , Time t ) const
    {
        return std::pair< State const& , Time >( state , t );
    }
};


} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_RANGE_STATE_POLICIES_HPP_INCLUDED
