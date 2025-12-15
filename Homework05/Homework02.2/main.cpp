#include <iostream>
#include <stack>
#include <string>
#include <gtest/gtest.h>

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

    size_t getCursorPosition() {
        return left_stack.size();
    }
};

TEST(TextEditorTest, AddTextTest) {
    TextEditor editor;

    editor.addText("Hello");
    EXPECT_EQ(editor.getFullText(), "Hello");

    editor.addText(" World");
    EXPECT_EQ(editor.getFullText(), "Hello World");
}

TEST(TextEditorTest, DeleteTextTest) {
    TextEditor editor;

    editor.addText("Hello World");

    int deleted = editor.deleteText(6);
    EXPECT_EQ(deleted, 6);
    EXPECT_EQ(editor.getFullText(), "Hello");

    deleted = editor.deleteText(10);
    EXPECT_EQ(deleted, 5);
    EXPECT_EQ(editor.getFullText(), "");
}

TEST(TextEditorTest, CursorLeftTest) {
    TextEditor editor;

    editor.addText("Hello");

    std::string leftText = editor.cursorLeft(2);
    EXPECT_EQ(leftText, "Hel");
    EXPECT_EQ(editor.getCursorPosition(), 3);

    editor.addText("world");
    EXPECT_EQ(editor.getFullText(), "Helworldlo");
}

TEST(TextEditorTest, CursorRightTest) {
    TextEditor editor;

    editor.addText("Programming");
    editor.cursorLeft(4);

    std::string leftText = editor.cursorRight(2);
    EXPECT_EQ(leftText, "Programm");
    EXPECT_EQ(editor.getCursorPosition(), 9);

    editor.addText("C++");
    EXPECT_EQ(editor.getFullText(), "ProgrammC++ing");
}

TEST(TextEditorTest, ComplexScenarioTest) {
    TextEditor editor;

    editor.addText("The quick brown fox");
    EXPECT_EQ(editor.getFullText(), "The quick brown fox");

    std::string leftText = editor.cursorLeft(8);
    EXPECT_EQ(leftText, "The quick");
    EXPECT_EQ(editor.getCursorPosition(), 10);

    editor.addText("red ");
    EXPECT_EQ(editor.getFullText(), "The quick red brown fox");


    int deleted = editor.deleteText(5);
    EXPECT_EQ(deleted, 5);
    EXPECT_EQ(editor.getFullText(), "The quick r brown fox");

    leftText = editor.cursorRight(3);
    EXPECT_EQ(leftText, "The quick r br");
    EXPECT_EQ(editor.getCursorPosition(), 14);

    deleted = editor.deleteText(0);
    EXPECT_EQ(deleted, 0);

    leftText = editor.cursorRight(100);
    EXPECT_EQ(editor.getCursorPosition(), 21); 
}

int main(int argc, char** argv) {
    if (argc > 1 && std::string(argv[1]) == "--run-tests") {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
    else {
        TextEditor editor;

        std::cout << "=== Text Editor Demo ===" << std::endl;

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

        std::cout << "\n5. Complex example:" << std::endl;
        TextEditor editor2;
        editor2.addText("Programming");
        std::cout << "Added 'Programming': " << editor2.getFullText() << std::endl;

        editor2.cursorLeft(4);
        std::cout << "Cursor moved 4 positions left" << std::endl;

        editor2.addText("C++");
        std::cout << "Added 'C++': " << editor2.getFullText() << std::endl;

        editor2.cursorRight(2);
        std::cout << "Cursor moved 2 positions right: " << editor2.getFullText() << std::endl;

        std::cout << "\nTo run tests, execute: ./text_editor --run-tests" << std::endl;

        return 0;
    }
}