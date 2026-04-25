#include "ISortedStrategy.hpp"
#include "QuickSort.hpp"
#include "BubbleSort.hpp"
#include <any>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include "Sorter.hpp"

struct User {
    std::string name;
    int age;
};

struct Product {
    std::string name;
    double price;
};

int main() {
    std::vector<User> users = {{"Alice", 30}, {"Bob", 25}, {"Charlie", 35}};
    std::vector<Product> products = {
        {"Laptop", 999.99}, {"Phone", 499.99}, {"Tablet", 299.99}};

    auto &sorter = Sorter::getInstance();

    sorter.setStrategy(std::make_unique<QuickSort<User>>());
    sorter.Sort<User>(
        users, [](const User &a, const User &b) { return a.age < b.age; });

    std::cout << "=== Users (sorted by age) using " << sorter.getStrategy()->name() << " ===" << std::endl;
    for (const auto &u : users)
        std::cout << u.name << ": " << u.age << std::endl;

    sorter.setStrategy(std::make_unique<BubbleSort<Product>>());
    sorter.Sort<Product>(products, [](const Product &a, const Product &b) {
        return a.price < b.price;
    });

    std::cout << "=== Products (sorted by price) using " << sorter.getStrategy()->name() << " ===" << std::endl;
    for (const auto &p : products)
        std::cout << p.name << ": " << p.price << std::endl;

    sorter.Sort<Product>(products, [](const Product &a, const Product &b) {
        return a.name < b.name;
    });

    std::cout << "=== Products (sorted by name) using " << sorter.getStrategy()->name() << " ===" << std::endl;
    for (const auto &p : products)
        std::cout << p.name << ": " << p.price << std::endl;
}