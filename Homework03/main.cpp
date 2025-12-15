#include <iostream>
#include <cstring>

class String {
private:
    char* data;
    size_t length;

public:
    String(const char* str = "") {
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
    }

    String(const String& other) {
        length = other.length;
        data = new char[length + 1];
        strcpy(data, other.data);
    }

    ~String() {
        delete[] data;
    }

    String& operator=(const String& other) {
        if (this != &other) {
            delete[] data;
            length = other.length;
            data = new char[length + 1];
            strcpy(data, other.data);
        }
        return *this;
    }

    class SubstringProxy {
    private:
        const String& original;
        size_t start;

    public:
        SubstringProxy(const String& str, size_t i) : original(str), start(i) {}

        String operator[](size_t end) const {
            if (start > end || end > original.length) {
                return String("");
            }

            size_t substr_length = end - start;
            char* substr_data = new char[substr_length + 1];

            strncpy(substr_data, original.data + start, substr_length);
            substr_data[substr_length] = '\0';

            String result(substr_data);
            delete[] substr_data;
            return result;
        }
    };

    SubstringProxy operator[](size_t i) const {
        return SubstringProxy(*this, i);
    }

    size_t getLength() const {
        return length;
    }

    const char* c_str() const {
        return data;
    }

    friend std::ostream& operator<<(std::ostream& os, const String& str) {
        os << str.data;
        return os;
    }
};

int safeInputInt(const std::string& prompt, int min, int max) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Error! Please enter an integer.\n";
        }
        else if (value < min || value > max) {
            std::cout << "Error! Number must be between " << min << " and " << max << ".\n";
        }
        else {
            std::cin.ignore(10000, '\n');
            return value;
        }
    }
}

String inputString(const std::string& prompt) {
    const int MAX_LENGTH = 1000;
    char buffer[MAX_LENGTH];

    std::cout << prompt;
    std::cin.getline(buffer, MAX_LENGTH);

    return String(buffer);
}

int main() {
    std::cout << "=== SUBSTRING EXTRACTION PROGRAM ===" << std::endl;
    std::cout << "Use syntax: string[start][end]" << std::endl;
    std::cout << "Example: hello[0][4] returns 'hell'" << std::endl;
    std::cout << "Indices start from 0, end is not included\n" << std::endl;

    while (true) {
        String userString = inputString("Enter a string (or 'exit' to quit): ");

        if (strcmp(userString.c_str(), "exit") == 0) {
            std::cout << "Exiting program..." << std::endl;
            break;
        }

        size_t strLength = userString.getLength();
        std::cout << "String length: " << strLength << std::endl;
        std::cout << "Valid indices: from 0 to " << strLength << std::endl;

        int startIndex = safeInputInt("Enter start index (i): ", 0, strLength);
        int endIndex = safeInputInt("Enter end index (j, not included): ", startIndex, strLength);

        String substring = userString[startIndex][endIndex];

        std::cout << "\n=== RESULT ===" << std::endl;
        std::cout << "Original string: \"" << userString << "\"" << std::endl;
        std::cout << "Range: [" << startIndex << "][" << endIndex << "]" << std::endl;
        std::cout << "Substring: \"" << substring << "\"" << std::endl;
        std::cout << "Substring length: " << substring.getLength() << std::endl;

        if (substring.getLength() == 0) {
            std::cout << ">>> Empty string (i == j)" << std::endl;
        }

        std::cout << "====================================\n" << std::endl;
    }

    return 0;
}