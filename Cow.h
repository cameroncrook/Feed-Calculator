#include <iostream>
#include <ctime>

#ifndef COW_H
#define COW_H

class Cow {
    private:
        std::tm _birthDate;
        std::string _breed;
        std::string _gender;
        int _weight;
        bool _isLactating = false;

    public:
        Cow(std::tm birthDate, std::string breed, std::string gender, bool lactating) {
            _birthDate = birthDate;
            _breed = breed;
            _gender = gender;
            _isLactating = lactating;
        };

        void setWeight(int weight) {
            _weight = weight;

            return;
        };

        void setLactating(bool isLactating) {
            _isLactating = isLactating;

            return;
        };

        void displayDetails() {
            std::cout << "Age: " << getAge() << std::endl;

            return;
        };

        int getAge() {
            std::time_t now = std::time(nullptr);

            // Convert to local time
            std::tm* now_tm = std::localtime(&now);

            // Extract the year and adjust it
            int currentYear = now_tm->tm_year;

            int birthYear = _birthDate.tm_year;

            int age = currentYear - birthYear;

            return age;
        };

        void calculateWeight() {
            int age = getAge();

            // Predicted breed weights
            std::map<std::string, std::map<std::string, std::map<int, int>>> breedWeights = {
                {"Black Angus", {
                    {"M", {
                        {1, 200},
                        {2, 500},
                        {3, 2075},
                    }},
                    {"F", {
                        {1, 200},
                        {2, 700},
                        {3, 1200}
                    }}
                }},
                {"Red Angus", {
                    {"M", {
                        {1, 200},
                        {2, 500},
                        {3, 1900},
                    }},
                    {"F", {
                        {1, 200},
                        {2, 700},
                        {3, 1300}
                    }}
                }},
                {"Charolais", {
                    {"M", {
                        {1, 200},
                        {2, 500},
                        {3, 2250},
                    }},
                    {"F", {
                        {1, 200},
                        {2, 700},
                        {3, 1425}
                    }}
                }},
                {"Hereford", {
                    {"M", {
                        {1, 200},
                        {2, 500},
                        {3, 1800},
                    }},
                    {"F", {
                        {1, 200},
                        {2, 700},
                        {3, 1200}
                    }}
                }},
            };

            if (age < 1) {
                return;
            } else if (age > 3) {
                age = 3;
            }

            _weight = breedWeights[_breed][_gender][age];

            return;
        }

        int getFeedDay() {
            double factor = 0.025;
            if (_isLactating) {
                factor = 0.03;
            }

            double feed = _weight * factor;

            return std::round(feed);
        };

        int getFeedWeek() {
            return getFeedDay() * 7;
        };

        int getFeedMonth() {
            return getFeedDay() * 30;
        };

        int getFeedYear(int feedMonths) {
            return getFeedMonth() * feedMonths;
        };

        void printWeight() {
            std::cout << _weight << std::endl;
        }
};

#endif