#pragma once
#ifndef TETRA_MESSAGE_DELEGATEMESSAGEHANDLER_HPP
#define TETRA_MESSAGE_DELEGATEMESSAGEHANDLER_HPP

#include <tetra/message/DelegateFunctionBuilder.hpp>

namespace tetra
{
namespace message
{

/**
 * Holds a non-owning reference to a class instance, and a
 * DelegateFunction. Provides an ordering function so that
 * DelegateMessageHandlers can be stored in a map.
 **/
class DelegateMessageHandler
{
  DelegateFunction delegateFunction;
  void* pObj = nullptr;
  const meta::MetaData* messageMetaData;

public:
  DelegateMessageHandler( const DelegateMessageHandler& ) = default;
  DelegateMessageHandler( DelegateMessageHandler&& ) = default;

  DelegateMessageHandler&
  operator=( const DelegateMessageHandler& ) = default;

  DelegateMessageHandler&
  operator=( DelegateMessageHandler&& ) = default;

  bool operator<( const DelegateMessageHandler& ) const noexcept;
  bool operator==( const DelegateMessageHandler& ) const noexcept;

  /**
   * Creates a DelegateMessageHandler from a class instance and a
   * method pointer. For example: given a widget with the following
   * method Widget.setName( const string& name ), we could craft a
   * DelegateMessageHandler for a string by calling
   * DelegateMessageHandler::create( widget, &Widget::setName );
   * @param instance The instance of the class the the method should
   *                 be called on.
   * @param handler The method that will be called to handle a
   *                message.
   * @return DelegateMessageHandler for delegating message handling to
   *         the class instance provided.
   **/
  template <class Class, typename Message>
  static DelegateMessageHandler
  create( Class& instance,
          void ( Class::*handler )( const Message& ) ) noexcept
  {
    return {&instance, DelegateFunctionBuilder( handler ),
            meta::MetaData::get<Message>()};
  }

  /**
   * Given a variant containing an instance of the Message type, use
   * the delegateFunction to handle the message.
   * @param message A variant containing the message instance.
   * @throws meta::TypeCastException if the Variant does not actually
   *         contain an instance of the message type.
   **/
  void handleMessage( const meta::Variant& message ) const;

  /**
   * Returns the MetaData instance for message type for this Delagate.
   **/
  const meta::MetaData& getMessageMetaData() const noexcept;

private:
  DelegateMessageHandler(
    void* pObj, DelegateFunction delegateFunction,
    const meta::MetaData& messageMetaData ) noexcept;
};

} /* namespace message */
} /* namespace tetra */

#endif
