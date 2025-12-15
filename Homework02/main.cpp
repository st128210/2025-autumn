#include <iostream>
#include <stack>
#include <string>

class TextEditor {
private:
    std::stack<char> left_stack;
    std::stack<char> right_stack;

    std::string getLeftText() {
        std::string result;
        std::stack<char> temp;

        while (!left_stack.empty()) {
            temp.push(left_stack.top());
            left_stack.pop();
        }

        int count = 0;
        while (!temp.empty()) {
            char c = temp.top();
            temp.pop();
            left_stack.push(c);

            if (count < 10) {
                result += c;
                count++;
            }
        }

        if (result.length() > 10) {
            std::string last_ten;
            for (size_t i = result.length() - 10; i < result.length(); i++) {
                last_ten += result[i];
            }
            return last_ten;
        }
        return result;
    }

public:
    TextEditor() = default;

    void addText(const std::string& text) {
        for (char c : text) {
            left_stack.push(c);
        }
    }

    int deleteText(int k) {
        int count = 0;
        while (k > 0 && !left_stack.empty()) {
            left_stack.pop();
            k--;
            count++;
        }
        return count;
    }

    std::string cursorLeft(int k) {
        while (k > 0 && !left_stack.empty()) {
            char c = left_stack.top();
            left_stack.pop();
            right_stack.push(c);
            k--;
        }
        return getLeftText();
    }

    std::string cursorRight(int k) {
        while (k > 0 && !right_stack.empty()) {
            char c = right_stack.top();
            right_stack.pop();
            left_stack.push(c);
            k--;
        }
        return getLeftText();
    }

    std::string getFullText() {
        std::string fullText;
        std::stack<char> temp_left = left_stack;
        std::stack<char> temp_right = right_stack;

        std::stack<char> reversed_left;
        while (!temp_left.empty()) {
            reversed_left.push(temp_left.top());
            temp_left.pop();
        }

        while (!reversed_left.empty()) {
            fullText += reversed_left.top();
            reversed_left.pop();
        }

        std::stack<char> temp;
        while (!temp_right.empty()) {
            temp.push(temp_right.top());
            temp_right.pop();
        }
        while (!temp.empty()) {
            fullText += temp.top();
            temp.pop();
        }

        return fullText;
    }
};

int main() {
    TextEditor editor;

    std::cout << "=== Text Editor ===" << std::endl;

    std::cout << "\n1. Adding text 'Hello'" << std::endl;
    editor.addText("Hello");
    std::cout << "Full text: " << editor.getFullText() << std::endl;

    std::cout << "\n2. Moving cursor 2 positions left and adding 'world'" << std::endl;
    std::string leftText = editor.cursorLeft(2);
    std::cout << "Left of cursor: '" << leftText << "'" << std::endl;
    editor.addText("world");
    std::cout << "Full text after addition: " << editor.getFullText() << std::endl;

    std::cout << "\n3. Deleting 3 characters" << std::endl;
    int deleted = editor.deleteText(3);
    std::cout << "Deleted characters: " << deleted << std::endl;
    std::cout << "Full text after deletion: " << editor.getFullText() << std::endl;

    std::cout << "\n4. Moving cursor 2 positions right" << std::endl;
    std::string rightText = editor.cursorRight(2);
    std::cout << "Left of cursor: '" << rightText << "'" << std::endl;
    std::cout << "Full text: " << editor.getFullText() << std::endl;

    return 0;
}