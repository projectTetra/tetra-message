#include <Widget.hpp>

#include <iostream>

int Widget::instanceCount{0};

Widget::Widget()
{
  ++instanceCount;
  this->myName = "Widget{" + std::to_string( instanceCount ) + "}";
}

Widget::~Widget()
{
  --instanceCount;
}

const std::string& Widget::getMyName() const noexcept
{
  return this->myName;
}

int Widget::getInstanceCount() noexcept
{
  return instanceCount;
}

void Widget::setMyName( const std::string& str ) noexcept
{
  std::cout << str << std::endl;
  this->myName = str;
} 
