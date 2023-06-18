#include <iostream>
#include <filesystem>

int main() {
    std::string dir = "/";

    try {
        for (const auto& entry : std::filesystem::directory_iterator(dir)) {
            std::cout << "name: " << entry.path().filename().string() << "\n";
        }
    } catch (std::filesystem::filesystem_error& e) {
        std::cout << "An error has occurred: " << e.what() << '\n';
    }

    return 0;
}

