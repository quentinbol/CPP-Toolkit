#pragma once
#include <any>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

class Watchable {
  public:
    struct Effect {
        std::unordered_set<std::string> deps;
        std::function<void()> fn;
    };

  protected:
    virtual void onChanged(const std::string &key, const std::any &newValue,
                           const std::any &oldValue) {}

    void notify(const std::string &key, const std::any &newValue,
                const std::any &oldValue) {
        onChanged(key, newValue, oldValue);
        trigger(key);
    }

    void watch(std::unordered_set<std::string> deps, std::function<void()> fn) {
        effects.push_back({deps, fn});
    }

    void trigger(const std::string &key) {
        for (const auto &effect : effects) {
            if (effect.deps.count(key) > 0) {
                effect.fn();
            }
        }
    }

  private:
    template <typename T> friend class Watched;

    std::vector<Effect> effects;
};