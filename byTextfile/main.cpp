#include <iostream>
#include <thread>
#include <filesystem>
#include <fstream>
#include <windows.h>
#include <string>
#include <iomanip>
using namespace std;

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

    //std::this_thread::sleep_for(std::chrono::milliseconds(1)); //延遲 1 毫秒
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

void simulateInput() {
    ifstream passwdFile("password.txt"); //讀取 password.txt
    if (!passwdFile) {
        cerr << "Can not find password.txt, program terminated." << endl;
        exit(1);
    }

    string password;
    while(getline(passwdFile, password)){ //一行一行讀
        std::cout << "Password: " << password << std::endl;

        std::string command = "enablecheats " + password;

        for (char c : command) {
            sendKey(c);
        }
        sendEnter();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(3));

        command = "cheat ghost ";

        for (char c : command) {
            sendKey(c);
        }
        sendEnter();

        std::this_thread::sleep_for(std::chrono::milliseconds(3));
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
    char c[2];
    std::cout << "Password Cracker - by using password.txt" << std::endl;
    std::cout << "If you want to kill the program, press Ctrl + c to terminate" << std::endl;
    std::cout << "Press enter to continue:";
    cin.getline(c, 1);
    std::cout << "Input simulation will start in 5 seconds. You can interrupt the simulation by pressing Ctrl + C." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    simulateInput();
    return 0;
}