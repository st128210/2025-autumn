#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <string>

double calculateRPN(const std::string& expression) {
    std::stack<double> numbers;
    std::stringstream ss(expression);
    std::string op;

    while (ss >> op) {
        if (op == "+" || op == "-" || op == "*" || op == "/") {
            if (numbers.size() < 2) {
                throw std::runtime_error("Not enough operands");
            }

            double second = numbers.top();
            numbers.pop();
            double first = numbers.top();
            numbers.pop();

            if (op == "+") {
                numbers.push(first + second);
            }
            else if (op == "-") {
                numbers.push(first - second);
            }
            else if (op == "*") {
                numbers.push(first * second);
            }
            else if (op == "/") {
                if (second == 0) {
                    throw std::runtime_error("Division by zero");
                }
                numbers.push(first / second);
            }
        }
        else {
            try {
                double num = std::stod(op);
                numbers.push(num);
            }
            catch (const std::invalid_argument&) {
                throw std::runtime_error("Invalid number");
            }
        }
    }

    if (numbers.size() != 1) {
        throw std::runtime_error("Invalid expression");
    }

    return numbers.top();
}

int main() {
    std::string inputFilename;
    std::string outputFilename;

    std::cout << "Enter input filename: ";
    std::cin >> inputFilename;

    std::cout << "Enter output filename: ";
    std::cin >> outputFilename;

    std::ifstream inputFile(inputFilename);

    if (!inputFile.is_open()) {
        std::cerr << "Error: cannot open input file " << inputFilename << std::endl;
        return 1;
    }

    std::ofstream outputFile(outputFilename);

    if (!outputFile.is_open()) {
        std::cerr << "Error: cannot create output file " << outputFilename << std::endl;
        inputFile.close();
        return 1;
    }

    std::string line;

    while (std::getline(inputFile, line)) {
        if (line.empty()) {
            continue;
        }

        try {
            double result = calculateRPN(line);
            outputFile << line << " = " << result << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Error processing line: " << line << " - " << e.what() << std::endl;
            outputFile << line << " = ERROR" << std::endl;
        }
    }

    inputFile.close();
    outputFile.close();

    std::cout << "Results written to " << outputFilename << std::endl;

    return 0;
}