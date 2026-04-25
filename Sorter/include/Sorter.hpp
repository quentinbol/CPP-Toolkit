#pragma once
#include "ISortedStrategy.hpp"
#include <any>
#include <functional>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

class Sorter {
  public:
    static Sorter &getInstance() {
        static Sorter instance;
        return instance;
    }

    Sorter(const Sorter &) = delete;
    Sorter &operator=(const Sorter &) = delete;
    Sorter(Sorter &&) = delete;
    Sorter &operator=(Sorter &&) = delete;

    void setStrategy(std::unique_ptr<ISorterStrategy> strategy) {
        strategy_ = std::move(strategy);
    }

    ISorterStrategy *getStrategy() const {
        if (!strategy_)
            throw std::runtime_error("No strategy set");
        return strategy_.get();
    }

    template <typename T>
    void Sort(std::vector<T> &data,
              std::function<bool(const T &, const T &)> compare) {
        if (!strategy_)
            throw std::runtime_error("No strategy set");

        std::any anyData = std::ref(data);
        std::any anyCmp = std::move(compare);

        strategy_->SortAny(anyData, anyCmp);
    }

  private:
    Sorter() = default;
    ~Sorter() = default;

    std::unique_ptr<ISorterStrategy> strategy_;
};
