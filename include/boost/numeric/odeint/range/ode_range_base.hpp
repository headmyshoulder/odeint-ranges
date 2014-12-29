/*
  [auto_generated]
  boost/numeric/odeint/range/ode_range_base.hpp

  [begin_description]
  tba.
  [end_description]

  Copyright 2009-2012 Karsten Ahnert
  Copyright 2009-2012 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_RANGE_ODE_RANGE_BASE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_RANGE_ODE_RANGE_BASE_HPP_INCLUDED

#include <boost/numeric/odeint/util/unwrap_reference.hpp>

#include <range/v3/range_facade.hpp>

namespace boost {
namespace numeric {
namespace odeint {


template< typename Rng , typename Stepper , typename System , typename State , typename Time , typename StatePolicy >
class ode_range_base : public ranges::range_facade< Rng >
{
public:

    using wrapped_stepper_type = Stepper;
    using stepper_type = typename odeint::unwrap_reference< wrapped_stepper_type >::type;
    using system_type = System;
    using wrapped_state_type = State;
    using state_type = typename odeint::unwrap_reference< wrapped_state_type >::type;
    using time_type = Time;

    ode_range_base( void ) = default;

    ode_range_base( wrapped_stepper_type stepper , system_type system , wrapped_state_type state ,
                    time_type time , time_type dt )
        : m_stepper( std::move( stepper ) )
        , m_system( std::move( system ) )
        , m_state( std::move( state ) )
        , m_time( time )
        , m_dt( dt )
    {}

    state_type const& value( void ) const
    {
        state_type const& state = m_state;
        return state;
    }

protected:

    wrapped_stepper_type m_stepper;
    system_type m_system;
    wrapped_state_type m_state;
    time_type m_time;
    time_type m_dt;
};

} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_RANGE_ODE_RANGE_BASE_HPP_INCLUDED
