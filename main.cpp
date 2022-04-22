#include <iostream>
#include "Vector.h"

void print(Vector& array) {
    for (auto&& item : array) {
        std::cout << item << " ";
    }
    std::cout << "\n";
}

int main() {
    double array[0] = {};
    Vector arr(array, 0);

    arr.shrinkToFit();
    std::cout << "size = " << arr.size() << "\n";
    std::cout << "opacity = " << arr.capacity() << "\n";

    arr.pushFront(1);
    arr.pushFront(1);
    arr.pushFront(1);

    std::cout << "size = " << arr.size() << "\n";
    std::cout << "opacity = " << arr.capacity() << "\n";

    arr.shrinkToFit();
    std::cout << "size = " << arr.size() << "\n";
    std::cout << "opacity = " << arr.capacity() << "\n";

    arr.insert(1, 0);
    std::cout << "size = " << arr.size() << "\n";
    std::cout << "opacity = " << arr.capacity() << "\n";

    arr.insert(2, 1);
    std::cout << "size = " << arr.size() << "\n";
    std::cout << "opacity = " << arr.capacity() << "\n";

    print(arr);

    return 0;
}
