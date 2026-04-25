#pragma once

#include "../ISortedStrategy.hpp"

#include <any>
#include <functional>
#include <utility>
#include <vector>

template <typename T> class BubbleSort : public ISorterStrategy {
  public:
    void SortAny(std::any &data, std::any compare) override {
        auto vecRef =
            std::any_cast<std::reference_wrapper<std::vector<T>>>(data);
        auto &vec = vecRef.get();
        auto cmp =
            std::any_cast<std::function<bool(const T &, const T &)>>(compare);
        BubbleSortHelper(vec, cmp);
    }

    std::string name() const override {
        return "BubbleSort";
    }

  private:
    void BubbleSortHelper(std::vector<T> &data,
                          std::function<bool(const T &, const T &)> compare) {
        int n = data.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (compare(data[j + 1], data[j])) {
                    std::swap(data[j], data[j + 1]);
                }
            }
        }
    }
};