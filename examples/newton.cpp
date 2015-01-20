/*
 * newton.cpp
 * Date: 2015-01-13
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 *
 */

#include <range/v3/range_facade.hpp>
#include <range/v3/view/take_while.hpp>
#include <range/v3/algorithm/for_each.hpp>


#include <iostream>
#include <cmath>

template< typename T , typename F , typename DF >
T newton( T x , F f , DF df )
{
    using std::abs;
    T y = f(x);
    while( abs(y) > static_cast< T >( 1.0e-12 ) )
    {
        x = x - y / df(x);
        y = f(x);
    }
    return x;
}

template< typename T , typename F , typename DF >
class newton_range : public ranges::range_facade< newton_range< T , F , DF > >
{
    friend ranges::range_access;

public:

    newton_range( T x , F f , DF df )
        : m_x( std::move( x ) ) , m_f( std::move( f ) ) , m_df( std::move( df ) )
    {
        m_y = m_f( m_x );
    }

    T const& x( void ) const
    {
        return m_x; 
    }

    T const& y( void ) const
    {
        return m_y;
    }


private:


    
    struct cursor
    {
        newton_range* m_rng;
        
        cursor( void ) = default;
        
        explicit cursor( newton_range& rng )
        : m_rng( &rng )
        {}
        
        decltype( auto ) current( void ) const
        {
            return m_rng->m_x;
        }
    
        bool done( void ) const
        {
            return false;
        }
  
        void next( void )
        {
            m_rng->m_x -= m_rng->m_y / m_rng->m_df( m_rng->m_x );
            m_rng->m_y = m_rng->m_f( m_rng->m_x );
        }
    };
    
    cursor begin_cursor()
    {
        return cursor { *this };
    }


    T m_x , m_y;
    F m_f;
    DF m_df;
};

template< typename T , typename F , typename DF >
newton_range< T , F , DF > make_newton_range( T x , F f , DF df )
{
    return newton_range< T , F , DF >( std::move( x ) , std::move( f ) , std::move( df ) );
}



int main( int argc , char *argv[] )
{
    using namespace std;

    cout.precision( 14 );

    auto f = []( auto x ) { return exp( - x * x ) - 0.5; };
    auto df = []( auto x ) { return -2.0 * x * exp( -x * x ); };

    { // example 1 without ranges

        double x = 1.0;
        double root = newton( x , f , df );
        cout << "Solution: " << root << " " << f( root ) << endl;
    }

    { // example 2 with ranges
        double x = 1.0;
        auto r = make_newton_range( x , f , df );
        auto r2 = ranges::view::take_while( r , [f]( auto x ) {
                using std::abs;
                return abs( f(x) ) > 1.0e-12; } );

        ranges::for_each( r2 , [f]( auto x ) {
                cout << x << " " << f(x) << "\n";
        } );
        cout << "Solution: " << r.x() << " " << r.y() << endl;
    }


        

    return 0;
}
