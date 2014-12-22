/*
  [auto_generated]
  boost/numeric/odeint/range/const_step_range.hpp

  [begin_description]
  tba.
  [end_description]

  Copyright 2009-2012 Karsten Ahnert
  Copyright 2009-2012 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_RANGE_CONST_STEP_RANGE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_RANGE_CONST_STEP_RANGE_HPP_INCLUDED

#include <boost/numeric/odeint/util/unwrap_reference.hpp>
#include <boost/numeric/odeint/stepper/stepper_categories.hpp>

#include <range/v3/range_facade.hpp>


namespace boost {
namespace numeric {
namespace odeint {

template< typename Stepper , typename System , typename State , typename Time ,
          typename StepperType = typename odeint::unwrap_reference< Stepper >::type::stepper_category >
class const_step_range ;


/// Specialization for steppers
template< typename Stepper , typename System , typename State , typename Time >
class const_step_range< Stepper , System , State , Time , stepper_tag >
    : public ranges::range_facade< const_step_range< Stepper , System , State , Time , stepper_tag > , true >
{
public:

    using wrapped_stepper_type = Stepper;
    using stepper_type = typename odeint::unwrap_reference< wrapped_stepper_type >::type;
    using system_type = System;
    using wrapped_state_type = State;
    using state_type = typename odeint::unwrap_reference< wrapped_state_type >::type;
    using time_type = Time;

    const_step_range( void ) = default;

    const_step_range( wrapped_stepper_type stepper , system_type system , wrapped_state_type state ,
                      time_type time , time_type dt )
        : m_stepper( std::move( stepper ) )
        , m_system( std::move( system ) )
        , m_state( std::move( state ) )
        , m_time( time )
        , m_dt( dt )
    {}

    state_type const& value( void ) const
    {
        return current();
    }

private:

    friend ranges::range_access;

    state_type const& current( void ) const
    {
        state_type const& state = m_state;
        return state;
    }
    
    bool done( void ) const
    {
        return false;
    }
  
    void next( void )
    {
        stepper_type& stepper = m_stepper;
        state_type& state = m_state;
        stepper.do_step( m_system , state , m_time , m_dt );
        m_time += m_dt;
    }

    wrapped_stepper_type m_stepper;
    system_type m_system;
    wrapped_state_type m_state;
    time_type m_time;
    time_type m_dt;
};

template< typename Stepper , typename System , typename State , typename Time >
auto make_const_step_range( Stepper stepper , System system , State state , Time time , Time dt )
{
    return const_step_range< Stepper , System , State , Time >(
        std::move( stepper ) , std::move( system ) , std::move( state ) , time , dt );
}




} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_RANGE_CONST_STEP_RANGE_HPP_INCLUDED
