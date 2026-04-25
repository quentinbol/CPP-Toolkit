#pragma once

#include "../ISortedStrategy.hpp"

#include <any>
#include <functional>
#include <utility>
#include <vector>

template <typename T> class QuickSort : public ISorterStrategy {
  public:
    void SortAny(std::any &data, std::any compare) override {
        auto vecRef =
            std::any_cast<std::reference_wrapper<std::vector<T>>>(data);
        auto &vec = vecRef.get();
        auto cmp =
            std::any_cast<std::function<bool(const T &, const T &)>>(compare);
        if (!vec.empty())
            QuickSortHelper(vec, 0, vec.size() - 1, cmp);
    }

    std::string name() const override {
        return "QuickSort";
    }

  private:
    void QuickSortHelper(std::vector<T> &data, int low, int high,
                         std::function<bool(const T &, const T &)> compare) {
        if (low < high) {
            int pi = Partition(data, low, high, compare);
            QuickSortHelper(data, low, pi - 1, compare);
            QuickSortHelper(data, pi + 1, high, compare);
        }
    }

    int Partition(std::vector<T> &data, int low, int high,
                  std::function<bool(const T &, const T &)> compare) {
        T pivot = data[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (compare(data[j], pivot)) {
                i++;
                std::swap(data[i], data[j]);
            }
        }
        std::swap(data[i + 1], data[high]);
        return i + 1;
    }
};