#include <tetra/message/MessageManager.hpp>

#include <algorithm>

using namespace std;
using namespace tetra;
using namespace tetra::meta;
using namespace tetra::message;

void MessageManager::registerMessageHandler(
  const DelegateMessageHandler& handler ) noexcept
{
  const auto& msgMetaData = handler.getMessageMetaData();
  messageToDelegatesMap[&msgMetaData].push_back( handler );
}

void MessageManager::deregisterMessageHandler(
  const DelegateMessageHandler& handler ) noexcept
{
  const auto& msgMetaData = handler.getMessageMetaData();

  if ( messageToDelegatesMap.find( &msgMetaData ) ==
       messageToDelegatesMap.end() )
    return; // we don't have any delegates for the message type

  DelegateVector& delegates = messageToDelegatesMap[&msgMetaData];
  auto iter = find( begin( delegates ), end( delegates ), handler );
  if ( iter != end(delegates) )
  {
    delegates.erase( iter );
  }
}

void MessageManager::queueMessage( Variant&& message ) noexcept
{
  getWriteQueue().push_back( move( message ) );
}

void MessageManager::update() noexcept
{
  swapReadWriteQueues();

  auto& messageQueue = getReadQueue();
  for ( const Variant& message : messageQueue )
  {
    dispatchMessage( message );
  }
  messageQueue.clear();
}

void MessageManager::dispatchMessage( const Variant& message ) const
  noexcept
{
  auto iter = messageToDelegatesMap.find( &message.getMetaData() );
  if ( iter == end( messageToDelegatesMap ) )
    return; // the message is not registered, so do nothing

  const DelegateVector& delegates = iter->second;
  for ( const auto& delegate : delegates )
  {
    delegate.handleMessage( message );
  }
}

void MessageManager::swapReadWriteQueues() noexcept
{
  swap( readQueueIndex, writeQueueIndex );
}

vector<Variant>& MessageManager::getReadQueue() noexcept
{
  return messageQueue[readQueueIndex];
}

vector<Variant>& MessageManager::getWriteQueue() noexcept
{
  return messageQueue[writeQueueIndex];
}
