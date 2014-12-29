/*
  [auto_generated]
  boost/numeric/odeint/util/exception.hpp

  [begin_description]
  tba.
  [end_description]

  Copyright 2009-2012 Karsten Ahnert
  Copyright 2009-2012 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_UTIL_EXCEPTION_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_UTIL_EXCEPTION_HPP_INCLUDED

#include <stdexcept>

namespace boost {
namespace numeric {
namespace odeint {
    
class odeint_error : public std::exception 
{
    std::string m_msg;

public:
    
    explicit odeint_error( std::string const& msg ) : m_msg ( msg ) {};

    const char* what( void ) const noexcept override { return m_msg.c_str(); }
};



} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_UTIL_EXCEPTION_HPP_INCLUDED
