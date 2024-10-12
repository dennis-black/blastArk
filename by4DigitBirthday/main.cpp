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
    //不足所設定的位數，空位補上0
    while (formattedNumber.length() < digits) {
        formattedNumber.insert(0, "0"); // 在前面補上0
    }
    return formattedNumber;
}

void simulateInput(int startMonth, int endMonth) {
    int digits_i = 1;
    int digits_j = 1;
    for (int i = startMonth; i <= endMonth; i++) {
        for (int j = 1; j <= 31; j++) {
            if(i<10)
                digits_i = 2;
            if(j<10)
                digits_j = 2;
            std::string formattedNumber = formatNumber(i, digits_i);
            formattedNumber += formatNumber(j, digits_j);
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


int main() {
    int startMonth = 1, endMonth = 12;
    char c;
    std::cout << "Password Cracker - by using date" << std::endl;
    std::cout << "If you want to kill the program, press Ctrl + c to terminate" << std::endl;
    std::cout << "Start month(1~12):";
    std::cin >> startMonth;
    std::cout << "End month(1~12):";
    std::cin >> endMonth;
    std::cout << "Input simulation will start in 5 seconds. You can interrupt the simulation by pressing Ctrl + C." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5)); // 延遲
    simulateInput(startMonth, endMonth);
    return 0;
}
