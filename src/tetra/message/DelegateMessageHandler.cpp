#include <tetra/message/DelegateMessageHandler.hpp>

using namespace std;
using namespace tetra;
using namespace tetra::meta;
using namespace tetra::message;

bool DelegateMessageHandler::
operator<( const DelegateMessageHandler& handler ) const noexcept
{
  return ( pObj < handler.pObj );
}

bool DelegateMessageHandler::
operator==( const DelegateMessageHandler& handler ) const noexcept
{
  return ( pObj == handler.pObj );
}

void
DelegateMessageHandler::handleMessage( const Variant& message ) const
{
  delegateFunction( pObj, message );
}

DelegateMessageHandler::DelegateMessageHandler(
  void* pObj, DelegateFunction delegateFunction,
  const MetaData& metaData ) noexcept
  : delegateFunction{delegateFunction},
    pObj{pObj},
    messageMetaData{metaData}
{ }
