#pragma once

#include "Watchable.hpp"
#include <ostream>
#include <string>

template <typename T> class Watched {
  public:
    Watched() = default;
    Watched(const T &value) : value(value), _owner(nullptr), _key("") {
    }
    Watched(const T &value, Watchable *owner, const std::string &key)
        : value(value), _owner(owner), _key(key) {
    }

    T get() const { return value; }

    friend std::ostream &operator<<(std::ostream &os,
                                    const Watched<T> &watched) {
        os << watched.value;
        return os;
    }

    operator T() const {
        return value;
    }

    Watched<T> &operator=(const T &newValue) {
        T old = value;
        value = newValue;
        if (_owner && !_key.empty()) {
            _owner->notify(_key, newValue, old);
        }
        return *this;
    }

  private:
    T value;
    Watchable *_owner = nullptr;
    std::string _key;
};