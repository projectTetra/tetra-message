#pragma once
#ifndef TETRA_MESSAGE_MESSAGEDELEGATE_HPP
#define TETRA_MESSAGE_MESSAGEDELEGATE_HPP

#include <tetra/meta/Variant.hpp>

#include <functional>
#include <iostream>

namespace tetra
{
namespace message
{

using DelegateFunction =
  std::function<void(void*, const meta::Variant&)>;

template <class Class, typename Message>
DelegateFunction
DelegateFunctionBuilder( void ( Class::*method )( const Message& ) )
{
  return [method]( void* pObj, const meta::Variant& variant )
  {
    Class* pInstance = reinterpret_cast<Class*>( pObj );
    ( pInstance->*method )( variant.getObject<Message>() );
  };
}

} /* namespace message */
} /* namespace tetra */

#endif
