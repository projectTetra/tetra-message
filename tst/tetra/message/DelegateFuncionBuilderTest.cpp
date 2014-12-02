#include <tetra/message/DelegateFunctionBuilder.hpp>

#include <Widget.hpp>
#include <catch.hpp>

#include <iostream>

using namespace std;
using namespace tetra;
using namespace tetra::message;
using namespace tetra::meta;

SCENARIO( "Calling a method through a DelegateFunction",
          "[Delegate]" )
{
  Widget widget{};

  DelegateFunction widgetDelegate =
    DelegateFunctionBuilder( &Widget::setMyName );

  GIVEN( "A class instance, and a DelegateFuncion built with the "
         "DelegateFuntionBuilder" )
  {
    
    THEN( "Calling the DelegateFunction should properly call the "
          "classes method" )
    {
      string widgetName{"new name"};
      Variant variant = Variant::create( widgetName );

      widgetDelegate( &widget, variant );

      REQUIRE( widget.getMyName() == widgetName );
    }

    THEN( "Calling the DelegateFunction with the wrong type should "
          "throw a TypeCastException" )
    {
      Variant variant = Variant::create( 5 );

      REQUIRE_THROWS_AS( widgetDelegate( &widget, variant ),
                         meta::TypeCastException );
    }
  }
}
