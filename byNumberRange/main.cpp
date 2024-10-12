#include <iostream>
#include <thread>
#include <windows.h>
#include <string>
#include <iomanip>

void sendKey(char c) {
    INPUT input = {0};
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = 0; 
    input.ki.wScan = c;
    input.ki.dwFlags = KEYEVENTF_UNICODE;

    SendInput(1, &input, sizeof(INPUT));

    // ===========================
    INPUT backspace = {0};
    backspace.type = INPUT_KEYBOARD;
    backspace.ki.wVk = VK_BACK;
    backspace.ki.dwFlags = 0;

    SendInput(1, &backspace, sizeof(INPUT));
    backspace.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &backspace, sizeof(INPUT));
    // ===========================

    //std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

// 模擬鍵盤按下 Enter
void sendEnter() {
    INPUT input = {0};
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = VK_RETURN;
    input.ki.dwFlags = 0;

    SendInput(1, &input, sizeof(INPUT));
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}

std::string formatNumber(int number, int digits) {
    std::string formattedNumber = std::to_string(number);
    while (formattedNumber.length() < digits) {
        formattedNumber.insert(0, "0");
    }
    return formattedNumber;
}

void simulateInput(int startRange, int endRange, int digits) {
    for (int i = startRange; i <= endRange; ++i) {
        std::string formattedNumber = formatNumber(i, digits);
        std::cout << "Formatted Number: " << formattedNumber << std::endl;

        std::string command = "enablecheats " + formattedNumber;

        for (char c : command) {
            sendKey(c);
        }
        sendEnter();

        std::this_thread::sleep_for(std::chrono::milliseconds(4));

        command = "cheat ghost";

        for (char c : command) {
            sendKey(c);
        }
        sendEnter();

        std::this_thread::sleep_for(std::chrono::milliseconds(4));
    }

    //---clean buf
    std::string command = "cheat ghost";
    for (char c : command) {
        sendKey(c);
    }
    sendEnter();
    std::this_thread::sleep_for(std::chrono::milliseconds(4));
    command = "cheat ghost";
    for (char c : command) {
        sendKey(c);
    }
    sendEnter();
    std::this_thread::sleep_for(std::chrono::milliseconds(4));
}

void getInputRange(int &startRange, int &endRange, int &digits) {
    while (true) {
        try {
            std::cout << "Start number: ";
            std::cin >> startRange;
            std::cout << "End number: ";
            std::cin >> endRange;
            std::cout << "Digits: ";
            std::cin >> digits;

            if (startRange > endRange || digits <= 0) {
                std::cout << "Invalid range or digits. Please try again." << std::endl;
            } else {
                break;
            }
        } catch (...) {
            std::cout << "Invalid input. Please enter integers." << std::endl;
        }
    }
}

int main() {
    int startRange = 1, endRange = 100, digits = 4;
    std::cout << "Password Cracker - by using range of two numbers" << std::endl;
    std::cout << "If you want to kill the program, press Ctrl + c to terminate" << std::endl;
    getInputRange(startRange, endRange, digits);
    std::cout << "Input simulation will start in 5 seconds. You can interrupt the simulation by pressing Ctrl + C." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));

    simulateInput(startRange, endRange, digits);
    return 0;
}
