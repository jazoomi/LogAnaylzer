#include "LogAnalyzer.h"
#include <fstream>
#include <iostream>
#include <algorithm>

LogAnalyzer::LogAnalyzer(const std::string& filename)
    : m_filename(filename) {}

bool LogAnalyzer::loadFile() {
    std::ifstream file(m_filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file '" << m_filename << "'" << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            m_lines.push_back(line);
        }
    }

    file.close();
    return true;
}

void LogAnalyzer::analyze() {
    for (const auto& line : m_lines) {
        std::string level = extractLevel(line);
        std::string message = extractMessage(line);

        m_levelCounts[level]++;
        if (!message.empty()) {
            m_messageFrequency[message]++;
        }
    }
}

void LogAnalyzer::printReport() const {
    std::cout << "========================================" << std::endl;
    std::cout << "          LOG ANALYSIS REPORT           " << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "File: " << m_filename << std::endl;
    std::cout << "Total lines processed: " << m_lines.size() << std::endl;
    std::cout << std::endl;

    // --- Log level counts ---
    std::cout << "--- Log Level Counts ---" << std::endl;
    for (const auto& [level, count] : m_levelCounts) {
        std::cout << "  " << level << ": " << count << std::endl;
    }
    std::cout << std::endl;

    // --- Top 5 most frequent messages ---
    std::cout << "--- Top 5 Most Frequent Messages ---" << std::endl;

    // Copy into a vector so we can sort by frequency
    std::vector<std::pair<std::string, int>> sorted(
        m_messageFrequency.begin(), m_messageFrequency.end());

    std::sort(sorted.begin(), sorted.end(),
        [](const auto& a, const auto& b) {
            return b.second < a.second;  // descending by count
        });

    int limit = std::min(static_cast<int>(sorted.size()), 5);
    for (int i = 0; i < limit; ++i) {
        std::cout << "  " << i + 1 << ". \"" << sorted[i].first
                  << "\" (x" << sorted[i].second << ")" << std::endl;
    }

    std::cout << "========================================" << std::endl;
}

// --- Private helpers ---

std::string LogAnalyzer::extractLevel(const std::string& line) const {
    // Expected format: [TIMESTAMP] [LEVEL] Message
    // Find the second '[' ... ']' pair
    size_t firstClose = line.find(']');
    if (firstClose == std::string::npos) {
        return "UNKNOWN";
    }

    size_t secondOpen = line.find('[', firstClose + 1);
    size_t secondClose = line.find(']', secondOpen + 1);
    if (secondOpen == std::string::npos || secondClose == std::string::npos) {
        return "UNKNOWN";
    }

    std::string level = line.substr(secondOpen + 1, secondClose - secondOpen - 1);

    if (level == "INFO" || level == "WARNING" || level == "ERROR") {
        return level;
    }
    return "UNKNOWN";
}

std::string LogAnalyzer::extractMessage(const std::string& line) const {
    // Message is everything after the second ']'
    size_t firstClose = line.find(']');
    if (firstClose == std::string::npos) {
        return line;  // whole line is the message if format is unexpected
    }

    size_t secondClose = line.find(']', firstClose + 1);
    if (secondClose == std::string::npos) {
        return line;
    }

    // Skip '] ' after the level bracket
    size_t msgStart = secondClose + 1;
    while (msgStart < line.size() && line[msgStart] == ' ') {
        ++msgStart;
    }

    return line.substr(msgStart);
}
