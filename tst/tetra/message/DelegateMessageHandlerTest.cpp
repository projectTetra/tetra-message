#include <tetra/message/DelegateMessageHandler.hpp>
#include <Widget.hpp>

#include <catch.hpp>

using namespace std;
using namespace tetra;
using namespace tetra::meta;
using namespace tetra::message;

SCENARIO( "Testing the DelegateMessageHandler",
          "[DelegateMessageHandler]" )
{
  Widget widget{};
  DelegateMessageHandler handler =
    DelegateMessageHandler::create( widget, &Widget::setMyName );

  GIVEN( "A DelegateMessageHandler for a widget instance" )
  {
    THEN( "The handler should have correctly identified the message "
          "type" )
    {
      REQUIRE( MetaData::get<string>() ==
               handler.getMessageMetaData() );
    }

    THEN( "HandleMessage should correctly handle a valid message" )
    {
      string newName{"message"};
      Variant message = Variant::create( newName );

      handler.handleMessage( message );

      REQUIRE( widget.getMyName() == newName );
    }

    THEN( "HandleMessage should throw a TypeCastException when told "
          "to handle an invalid message" )
    {
      Variant message = Variant::create( 5 );

      REQUIRE_THROWS_AS( handler.handleMessage( message ),
                         TypeCastException );
    }
  }

  GIVEN( "Two DelegateMessageHandlers to different widgets" )
  {
    Widget seccondWidget{};
    DelegateMessageHandler secondHandler =
      DelegateMessageHandler::create( seccondWidget,
                                      &Widget::setMyName );

    THEN( "The DelegateMessageHandlers should not evaluate as equal" )
    {
      REQUIRE( !( handler == secondHandler ) );
    }
  }
}
