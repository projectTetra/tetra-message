#pragma once
#ifndef TETRA_META_TEST_WIDGET_HPP
#define TETRA_META_TEST_WIDGET_HPP

#include <string>

struct Notify {};

/**
 * Used by the various MetaData tests.
 **/
class Widget
{
  static int instanceCount;
  
  std::string myName; 
  int notifyCount{0};

public:
  static int getInstanceCount() noexcept;

public:
  Widget();
  ~Widget();

  const std::string& getMyName() const noexcept;
  
  void setMyName( const std::string& str ) noexcept;

  void otherSetMyName( const std::string& str ) noexcept;

  void onNotify( const Notify& notify ) noexcept;
  int getNotifyCount() const noexcept;
};

#endif
