#ifndef LOG_ANALYZER_H
#define LOG_ANALYZER_H

#include <string>
#include <vector>
#include <map>

class LogAnalyzer {
public:
    explicit LogAnalyzer(const std::string& filename);

    bool loadFile();
    void analyze();
    void printReport() const;

private:
    std::string m_filename;
    std::vector<std::string> m_lines;
    std::map<std::string, int> m_levelCounts;
    std::map<std::string, int> m_messageFrequency;

    std::string extractLevel(const std::string& line) const;
    std::string extractMessage(const std::string& line) const;
};

#endif // LOG_ANALYZER_H
