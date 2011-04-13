/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_FUNCTION_FUNCTION_HANDLING_HPP
#define BOOST_PHOENIX_FUNCTION_FUNCTION_HANDLING_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/support/iterate.hpp>
#include <boost/proto/tags.hpp>

namespace boost { namespace phoenix
{
    /////////////////////////////////////////////////////////////////////////////
    // Functions
    /////////////////////////////////////////////////////////////////////////////

    namespace tag
    {
        typedef proto::tag::function function;
    }

    namespace expression
    {

        template <
            typename F
          , BOOST_PHOENIX_typename_A_void(BOOST_PHOENIX_LIMIT)
          , typename Dummy = void
        >
        struct function;

    #define BOOST_PHOENIX_DEFINE_FUNCTION_EXPRESSION(_, N, __)                  \
        template <typename F, BOOST_PHOENIX_typename_A(N)>                      \
        struct function<F, BOOST_PHOENIX_A(N)>                                  \
            : expr<tag::function, F, BOOST_PHOENIX_A(N)>                        \
        {};                                                                     \

        BOOST_PP_REPEAT_FROM_TO(
            1
          , BOOST_PHOENIX_LIMIT
          , BOOST_PHOENIX_DEFINE_FUNCTION_EXPRESSION
          , _
        )

    #undef BOOST_PHOENIX_DEFINE_FUNCTION_EXPRESSION
    }

    namespace rule
    {
        struct function
            : expression::function<proto::vararg<meta_grammar> >
        {};
    }

    template <typename Dummy>
    struct meta_grammar::case_<proto::tag::function, Dummy>
        : enable_rule<rule::function, Dummy>
    {};

}}

#endif
