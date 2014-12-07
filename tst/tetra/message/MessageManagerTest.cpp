#include <tetra/message/MessageManager.hpp>

#include <Widget.hpp>
#include <catch.hpp>

using namespace std;
using namespace tetra;
using namespace tetra::meta;
using namespace tetra::message;

SCENARIO( "Using the MessageManager to manage messages",
          "[MessageManager]" )
{
  MessageManager messageManager{};
  Widget widget{};

  messageManager.registerMessageHandler( widget, &Widget::setMyName );

  GIVEN( "A MessageManager with a DelegateMessageHandler registered "
         "to listen for string messages" )
  {
    THEN(
      "Queuing an int message and updating should have no effect" )
    {
      messageManager.queueMessage( Variant::create( 5 ) );
      messageManager.update();

      REQUIRE( widget.getMyName() == "Widget{1}" );
    }

    THEN(
      "Queuing string messages and updating should call the handler" )
    {
      string msg1{"test1"};
      string msg2{"test2"};
      messageManager.queueMessage( Variant::create( msg1 ) );
      messageManager.queueMessage( Variant::create( msg2 ) );

      messageManager.update();

      REQUIRE( widget.getMyName() == "test2" );
    }

    THEN( "removing the message handler should make it not recieve "
          "any new messages" )
    {
      messageManager.deregisterMessageHandler( widget,
                                               &Widget::setMyName );

      string oldName = widget.getMyName();

      messageManager.queueMessage(
        Variant::create( string{"newName"} ) );
      messageManager.update();

      REQUIRE( widget.getMyName() == oldName );
    }
  }

  GIVEN( "A MessageHandler with multiple DelegateMessageHandler's "
         "registered for the same message type" )
  {
    Widget w1, w2;
    messageManager.registerMessageHandler( w1, &Widget::onNotify );
    messageManager.registerMessageHandler( w2, &Widget::onNotify );

    THEN( "each instance should recieve each message" )
    {
      messageManager.queueMessage( Variant::create( Notify{} ) );
      messageManager.queueMessage( Variant::create( Notify{} ) );
      messageManager.queueMessage( Variant::create( Notify{} ) );
      messageManager.queueMessage( Variant::create( 4 ) );
      messageManager.update();

      REQUIRE( w1.getNotifyCount() == 3 );
      REQUIRE( w2.getNotifyCount() == 3 );
    }

    messageManager.deregisterMessageHandler( w1, &Widget::onNotify );
    messageManager.deregisterMessageHandler( w2, &Widget::onNotify );
  }
}

