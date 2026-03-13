#include "LogAnalyzer.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <logfile>" << std::endl;
        return 1;
    }

    LogAnalyzer analyzer(argv[1]);

    if (!analyzer.loadFile()) {
        return 1;
    }

    analyzer.analyze();
    analyzer.printReport();

    return 0;
}
