#include "Watchable.hpp"
#include "Watched.hpp"
#include <iostream>

class Player : public Watchable {
  public:
    void setHealth(int h) {
        health = h;
    }

    void setName(const std::string &n) {
        name = n;
    }

    Player() {
        watch({"health"}, [&]() {
            if (health <= 0) {
                std::cout << "[WATCH] " << name.get() << " is Dead"
                          << std::endl;
                setName(name.get() + " (RIP)");
            }
        });
        watch({"name"}, [&]() {
            std::cout << "[WATCH] Name changed to: " << name.get() << std::endl;
        });
    }

    Watched<int> getHealth() const {
        return health;
    }

    Watched<std::string> getName() const {
        return name;
    }

  private:
    Watched<int> health{100, this, "health"};
    Watched<std::string> name{"Player1", this, "name"};

  protected:
    void onChanged(const std::string &key, const std::any &newValue,
                   const std::any &oldValue) override {
        if (key == "health")
            std::cout << "[LOG - Health] Old: " << std::any_cast<int>(oldValue)
                      << " New: " << std::any_cast<int>(newValue) << std::endl;
        else if (key == "name")
            std::cout << "[LOG - Name] Old: "
                      << std::any_cast<std::string>(oldValue)
                      << " New: " << std::any_cast<std::string>(newValue)
                      << std::endl;
    }
};

int main() {
    Player player;

    player.setHealth(80);
    player.setName("Alice");
    player.setHealth(60);
    player.setHealth(player.getHealth() - 70);
}