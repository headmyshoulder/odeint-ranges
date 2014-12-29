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

#include <boost/numeric/odeint/range/state_policies.hpp>
#include <boost/numeric/odeint/range/ode_range_base.hpp>

#include <boost/numeric/odeint/util/unwrap_reference.hpp>
#include <boost/numeric/odeint/util/detail/less_with_sign.hpp>
#include <boost/numeric/odeint/stepper/stepper_categories.hpp>


namespace boost {
namespace numeric {
namespace odeint {
    




template< typename Stepper , typename System , typename State , typename Time ,
          typename StatePolicy = state_policy ,
          typename StepperType = typename base_tag< typename odeint::unwrap_reference< Stepper >::type::stepper_category >::type >
class const_step_range ;


/// Factory function for const step range
template< typename Stepper , typename System , typename State , typename Time >
auto make_const_step_range( Stepper stepper , System system , State state , Time time , Time dt )
{
    return const_step_range< Stepper , System , State , Time >(
        std::move( stepper ) , std::move( system ) , std::move( state ) , time , dt );
}

/// Factory function for const step range with time
template< typename Stepper , typename System , typename State , typename Time >
auto make_const_step_time_range( Stepper stepper , System system , State state , Time time , Time dt )
{
    return const_step_range< Stepper , System , State , Time , state_and_time_policy >(
        std::move( stepper ) , std::move( system ) , std::move( state ) , time , dt );
}






/// Specialization for steppers
template< typename Stepper , typename System , typename State , typename Time , typename StatePolicy >
class const_step_range< Stepper , System , State , Time , StatePolicy , stepper_tag >
    : public ode_range_base<
        const_step_range< Stepper , System , State , Time , StatePolicy , stepper_tag > ,
        Stepper , System , State , Time , StatePolicy >
{
public:
    
    using base_type = ode_range_base<
        const_step_range< Stepper , System , State , Time , StatePolicy , stepper_tag > ,
        Stepper , System , State , Time , StatePolicy > ;
    
    using base_type::base_type;

private:

    friend ranges::range_access;
    
    struct cursor
    {
        const_step_range* m_rng;
        
        cursor( void ) = default;
        
        explicit cursor( const_step_range& rng)
        : m_rng( &rng )
        {}
        
        decltype( auto ) current( void ) const
        {
            typename base_type::state_type const& state = m_rng->m_state;
            return StatePolicy {} ( state , m_rng->m_time );
        }
    
        bool done( void ) const
        {
            return false;
        }
  
        void next( void )
        {
            typename base_type::stepper_type& stepper = m_rng->m_stepper;
            typename base_type::state_type& state = m_rng->m_state;
            stepper.do_step( m_rng->m_system , state , m_rng->m_time , m_rng->m_dt );
            m_rng->m_time += m_rng->m_dt;
        }
    };
    
    cursor begin_cursor()
    {
        return cursor { *this };
    }
};







/// Specialization for dense output steppers
template< typename Stepper , typename System , typename State , typename Time , typename StatePolicy >
class const_step_range< Stepper , System , State , Time , StatePolicy , dense_output_stepper_tag >
    : public ode_range_base<
        const_step_range< Stepper , System , State , Time , StatePolicy , dense_output_stepper_tag > ,
        Stepper , System , State , Time , StatePolicy >
{
public:
    
    using base_type = ode_range_base<
        const_step_range< Stepper , System , State , Time , StatePolicy , dense_output_stepper_tag > ,
        Stepper , System , State , Time , StatePolicy > ;
    
    using base_type::base_type;

private:

    friend ranges::range_access;
    
    struct cursor
    {
        const_step_range* m_rng;
        
        cursor( void ) = default;
        
        explicit cursor( const_step_range& rng)
        : m_rng( &rng )
        {}
        
        decltype( auto ) current( void ) const
        {
            typename base_type::state_type const& state = m_rng->m_state;
            return StatePolicy {} ( state , m_rng->m_time );
        }
    
        bool done( void ) const
        {
            return false;
        }
  
        void next( void )
        {
            typename base_type::stepper_type& stepper = m_rng->m_stepper;
            typename base_type::state_type& state = m_rng->m_state;
            m_rng->m_time += m_rng->m_dt;

            while( detail::less_with_sign( stepper.current_time() , m_rng->m_time , stepper.current_time_step() ) )
            {
                stepper.do_step( m_rng->m_system );
            }
            stepper.calc_state( m_rng->m_time , state );
        }
    };
    
    cursor begin_cursor()
    {
        return cursor { *this };
    }
};





} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_RANGE_CONST_STEP_RANGE_HPP_INCLUDED
