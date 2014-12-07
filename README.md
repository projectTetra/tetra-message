tetra-message
=============

A simple publish-subscribe messaging system built using the 
[tetra-meta](http://github.com/projectTetra/tetra-meta) library.

## Basic Usage

The main interface for the library is the MessageManager class.

Creating a MessageManager is easy:

```C++
MessageManager messageManager{};
```

From here, adding a mesage handler is super easy:

```C++
Widget widget{};

messageManager.registerHandler( widget, &Widget::onMessage );
```

This adds the Widget::onMessage method as a message handler.

But wait, you ask, what message will this be handling? Well, that depends on
the signature of the Widget::onMessage class. Here is an example:

```C++
struct Message
{
  Message() = default;
  Message( string name, int data );

  string name;
  int data;
};

class Widget
{
public:
  void onMessage( const Message& msg )
  {
    cout << name << ": " << data << endl;
  }
};
```
In this case, the onMessage method will, when registered, automatically be
set up to handle Message objects when they are published.

So how do publish messages?

```C++
messageManager.queueMessage( Variant::create( Message{"test message", 5} ) );
 ```





