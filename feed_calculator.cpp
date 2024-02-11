#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>
#include <map>
#include <list>
#include "Cow.h"

std::vector<std::string> split(const std::string &s, char delimiter);

int main() {
    std::list<Cow> herd;

    // Reads csv file and populates 'herd'
    // ===========================================
    std::string csvFilePath = "herd.csv";
    std::ifstream file(csvFilePath);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << csvFilePath << std::endl;
        return 1;
    }

    bool firstLine = true;
    std::string line;
    while (getline(file, line)) {
        std::vector<std::string> tokens = split(line, ',');

        int birthDateIndex;
        int breedIndex;
        int genderIndex;
        int lactatingIndex;

        if (firstLine) {
            int i = 0;
            for (const auto& token : tokens) {
                if (token == "birthDate") {
                    birthDateIndex = i;
                } else if (token == "breed") {
                    breedIndex = i;
                } else if (token == "gender") {
                    genderIndex = i;
                } else if (token == "lactating") {
                    lactatingIndex = i;
                }

                i++;
            }

            firstLine = false;
        } else {
            std::vector<std::string> dateValues = split(tokens[birthDateIndex], '/');

            int year = std::stoi(dateValues[2]);
            int month = std::stoi(dateValues[0]);
            int day = std::stoi(dateValues[1]);

            std::tm birthDate = {};
            birthDate.tm_year = year - 1900;
            birthDate.tm_mon = month;
            birthDate.tm_mday = day;

            std::string breed = tokens[breedIndex];
            std::string gender = tokens[genderIndex];
            bool lactating = tokens[lactatingIndex] == "true";

            Cow animal(birthDate, tokens[breedIndex], tokens[genderIndex], (tokens[lactatingIndex] == "true"));

            herd.push_back(animal);
        };
    }

    file.close();

    // CALCULATES FEED
    // ===================================
    int feedPerDay = 0;
    int feedPerWeek = 0;
    int feedPerMonth = 0;
    int feedPerYear = 0;

    for (Cow cow : herd) {
        cow.calculateWeight();
        feedPerDay += cow.getFeedDay();
        feedPerWeek += cow.getFeedWeek();
        feedPerMonth += cow.getFeedMonth();
        feedPerYear += cow.getFeedYear(6);
    }

    // ADDS DATA TO LOG FILE
    // =================================
    // Get current time
    auto currentTime = std::chrono::system_clock::now();

    std::time_t date = std::chrono::system_clock::to_time_t(currentTime);
    std::string formatedDate = std::ctime(&date);
    formatedDate.pop_back();

    // csv line to add
    std::string log = "\n" + formatedDate + "," + std::to_string(feedPerDay) + "," + std::to_string(feedPerWeek) + "," + std::to_string(feedPerMonth) + "," + std::to_string(feedPerYear);

    std::string logFilePath = "log.csv";

    std::ofstream logFile(logFilePath, std::ios::app);

    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file";
        return 1;
    }

    logFile << log;

    logFile.close();

    std::cout << "Calculated amout of dry feed needed:\n" << std::endl;

    std::cout << feedPerDay << " pounds per day" << std::endl;
    std::cout << feedPerWeek << " pounds per week" << std::endl;
    std::cout << feedPerMonth << " pounds per month" << std::endl;
    std::cout << feedPerYear << " pounds per year (6 months)" << std::endl;

    return 0;
}

std::vector<std::string> split(const std::string &s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Marisa Moore
