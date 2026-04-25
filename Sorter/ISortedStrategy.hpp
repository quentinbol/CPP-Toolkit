
#pragma once
#include <any>
#include <string>

class ISorterStrategy {
  public:
    virtual ~ISorterStrategy() = default;
    virtual void SortAny(std::any &data, std::any compare) = 0;
    virtual std::string name() const = 0;
};