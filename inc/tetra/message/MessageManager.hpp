#pragma once
#ifndef TETRA_MESSAGE_MESSAGEMANAGER_HPP
#define TETRA_MESSAGE_MESSAGEMANAGER_HPP

#include <tetra/message/DelegateMessageHandler.hpp>

#include <unordered_map>
#include <vector>

namespace tetra
{
namespace message
{

/**
 * Maintains a set of DelegateMessageHandlers to which is distributes
 * messages when the appropriate methods are called.
 * The MessageManager is not threadsafe and requires external
 * synchronization when used in a multithreded environment.
 **/
class MessageManager
{
  using DelegateVector = std::vector<DelegateMessageHandler>;
  using MessageToDelegatesMap =
    std::unordered_map<const meta::MetaData*, DelegateVector>;

  MessageToDelegatesMap messageToDelegatesMap;

  // 2 message queues, one for reading one for writing
  std::vector<meta::Variant> messageQueue[2]; 

  int writeQueueIndex{0};
  int readQueueIndex{1};

public:
  /**
   * Adds the DelegateMessageHandler to the MessageManager to be
   * called when the correct message type is broadcasted.
   * @param delegateMessageHandler The handler to be registered
   **/
  void registerMessageHandler(
    const DelegateMessageHandler& handler ) noexcept;

  /**
   * Should be called before the handler becomes invalid (e.g. before
   * the instance is destroyed) to prevent messages being broadcast to
   * non-exsistent objects. This is a no-op if the handler does not
   * exist or has already been removed.
   * @param handler The handler to deregister
   **/
  void deregisterMessageHandler(
    const DelegateMessageHandler& handler ) noexcept;

  /**
   * Queues the message variant to be published on the next call to
   * update.
   * @param message The message to be published.
   **/
  void queueMessage( meta::Variant&& message ) noexcept;

  /**
   * Broadcasts each message in the queue to their respective handlers
   * in a FIFO manner.
   **/
  void update() noexcept;

private:
  void swapReadWriteQueues() noexcept;

  std::vector<meta::Variant>& getReadQueue() noexcept;
  std::vector<meta::Variant>& getWriteQueue() noexcept;
};

} /* namespace message */
} /* namespace tetra */

#endif
