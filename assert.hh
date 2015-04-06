#ifndef ASSERT_HH
#define ASSERT_HH

/********************************************************************************\
 *  The ENABLE_ASSERTIONS macro can be defined before first using this header   *
 *      or by including a preprocessor definition for it at compile-time.       *
 *  The latter method is my preferred method, as it coincides more closely      *
 *      with a build system and release hierarchy. Users of this file are,      *
 *      however, free to do as they please.                                     *
\********************************************************************************/
#ifdef ENABLE_ASSERTIONS

	#include <stdexcept>
	using std :: logic_error;

	#include <string>
	using std :: string;

    /********************************************************************************\
     *  assertion_error structure                                                   *
     *==============================================================================*
     *  This structure defines a type of error which occurs at runtime, but whose   *
     *      origin are traced back to debug assertions, and are ultimately the      *
     *      responsibility of the programmer to eliminate before release.           *
     *------------------------------------------------------------------------------*
     *  NOTE: This structure is not defined if assertions are not enabled with      *
     *      the ENABLE_ASSERTIONS macro.                                            *
    \********************************************************************************/
    struct assertion_error
    {
        /********************************************************************************\
         *  assertion_error :: assertion_error ( const string& )                        *
         *==============================================================================*
         *  Construct an assertion_error with a message to be displayed or returned     *
         *      if the assertion fails.                                                 *
         *  ( Success messages defeat the purpose of assertions )                       *
         *------------------------------------------------------------------------------*
         *  @param  failMsg - the message to display/return via what() if the           *
         *                      assertion fails                                         *
        \********************************************************************************/
        explicit assertion_error ( const string& failMsg )
            : logic_error ( failMsg )
        {}
    };

    /********************************************************************************\
     *  assert ( const bool, const string& ) : void                                 *
     *==============================================================================*
     *  Assert that the given condition is true, otherwise throw an exception       *
     *      with the given message on failure.                                      *
     *------------------------------------------------------------------------------*
     *  @param  condition - the condition to assert upon ( test with )              *
     *  @param  failureMessage - the message to display/return from the exception   *
    \********************************************************************************/
    void
    assert ( const bool condition, const string& failureMessage )
    {
        if ( condition ) ;  // Do nothing if the condition is true
        else throw assertion_error ( failureMessage );
    }

    /********************************************************************************\
     *  assert ( const bool ) : void                                                *
     *==============================================================================*
     *  Assert that the given condition is true, otherwise throw an exception on    *
     *      failure.                                                                *
     *------------------------------------------------------------------------------*
     *  @param  condition - the condition to assert upon ( test with )              *
    \********************************************************************************/
    void
    assert ( const bool condition )
    {
        assert ( condition, "" );
    }

#else

    /** Let the preprocessor eat up any assertions  */

    #define assert( condition, message )

    #define assert( condition )

#endif

/** Since static_assert is a C++ built-in, give our new assert a better name    */

#define dynamic_assert assert

#endif//ASSERT_HH