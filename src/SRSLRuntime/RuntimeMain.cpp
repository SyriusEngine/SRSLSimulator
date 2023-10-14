#include <iostream>

int main(int argc, char** argv) {
    try {


    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}
