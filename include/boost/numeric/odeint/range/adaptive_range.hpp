/*
  [auto_generated]
  boost/numeric/odeint/range/adaptive_range.hpp

  [begin_description]
  tba.
  [end_description]

  Copyright 2009-2012 Karsten Ahnert
  Copyright 2009-2012 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_RANGE_ADAPTIVE_RANGE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_RANGE_ADAPTIVE_RANGE_HPP_INCLUDED


#include <boost/numeric/odeint/range/state_policies.hpp>
#include <boost/numeric/odeint/range/ode_range_base.hpp>

#include <boost/numeric/odeint/util/exception.hpp>
#include <boost/numeric/odeint/util/unwrap_reference.hpp>
#include <boost/numeric/odeint/util/detail/less_with_sign.hpp>
#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/stepper/controlled_step_result.hpp>

#include <boost/throw_exception.hpp>

namespace boost {
namespace numeric {
namespace odeint {


template< typename Stepper , typename System , typename State , typename Time ,
          typename StatePolicy = state_policy ,
          typename StepperType = typename base_tag< typename odeint::unwrap_reference< Stepper >::type::stepper_category >::type >
class adaptive_range ;


/// Factory function for const step range
template< typename Stepper , typename System , typename State , typename Time >
auto make_adaptive_range( Stepper stepper , System system , State state , Time time , Time dt )
{
    return adaptive_range< Stepper , System , State , Time >(
        std::move( stepper ) , std::move( system ) , std::move( state ) , time , dt );
}

/// Factory function for const step range with time
template< typename Stepper , typename System , typename State , typename Time >
auto make_adaptive_time_range( Stepper stepper , System system , State state , Time time , Time dt )
{
    return adaptive_range< Stepper , System , State , Time , state_and_time_policy >(
        std::move( stepper ) , std::move( system ) , std::move( state ) , time , dt );
}






/// Specialization for steppers
template< typename Stepper , typename System , typename State , typename Time , typename StatePolicy >
class adaptive_range< Stepper , System , State , Time , StatePolicy , controlled_stepper_tag >
    : public ode_range_base<
        adaptive_range< Stepper , System , State , Time , StatePolicy , controlled_stepper_tag > ,
        Stepper , System , State , Time , StatePolicy >
{
public:
    
    using base_type = ode_range_base<
        adaptive_range< Stepper , System , State , Time , StatePolicy , controlled_stepper_tag > ,
        Stepper , System , State , Time , StatePolicy > ;
    
    using base_type::base_type;

private:

    friend ranges::range_access;
    
    struct cursor
    {
        adaptive_range* m_rng;
        
        cursor( void ) = default;
        
        explicit cursor( adaptive_range& rng)
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
//             stepper.do_step( m_rng->m_system , state , m_rng->m_time , m_rng->m_dt );
//             m_rng->m_time += m_rng->m_dt;
            
            const size_t max_attempts = 1000;
            size_t trials = 0;
            controlled_step_result res = success;
            do
            {
                res = stepper.try_step( m_rng->m_system , state , m_rng->m_time , m_rng->m_dt );
                ++trials;
            }
            while( ( res == fail ) && ( trials < max_attempts ) );
            if( trials == max_attempts )
            {
                BOOST_THROW_EXCEPTION( odeint_error( "Adaptive range: Maximal number of iterations reached. A step size could not be found." ));
            }
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


#endif // BOOST_NUMERIC_ODEINT_RANGE_ADAPTIVE_RANGE_HPP_INCLUDED
