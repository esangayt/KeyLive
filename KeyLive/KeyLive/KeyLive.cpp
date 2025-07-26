#include <iostream>
#include <fstream>
#include <conio.h>  // Para _kbhit() y _getch()

int main(int argc, char* argv[])
{

    // std::ios::app indica que se abrirá el archivo en modo de adición
    // Si el archivo no existe, se creará
    // Si el archivo ya existe, se agregará al final del archivo existente
    // std::ios::out indica que se abrirá el archivo para escritura
    // std::ios::in indica que se abrirá el archivo para lectura
    std::ofstream log("key_logs.txt", std::ios::app);
    

    if (!log.is_open())
    {
        std::cerr << "Fail to open log file." << std::endl;
        return 1;
    }

    std::cout << "Presiona cualquier tecla para registrar. Presiona 'q' para salir.\n";

    while (true)
    {
        if (_kbhit()) // Verifica si hay una tecla presionada
        {
            char tecla = _getch();  // Captura la tecla presionada

            //Mostrar en consola
            std::cout << "Key pressed: " << tecla << std::endl;

            if (tecla == 13)
            {
                log << "[ENTER] ";
            } else if (tecla == 27)
            {
                log << "[ESC] ";
                break;
            }
            else if (tecla == 8)
            {
                log << "[BACKSPACE] ";
            }
            else if (tecla == 9)
            {
                log << "[TAB] ";
            }
            else if (tecla == 32)
            {
                log << "[SPACE] ";
            }
            else
            {
                log << tecla << " "; // Registra la tecla presionada
            }

            // Fuerza el volcado del búfer de salida al archivo
            log.flush();
        }
    }
    
    log.close();
    std::cout << "Register has been finished." << std::endl;
    
    return 0;
}
