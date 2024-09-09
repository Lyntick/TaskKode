#pragma once
#include <vector>
#include <fstream>
#include <exception>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <climits>
#include <iomanip>
#include <unordered_map>

#include "Object.h"

namespace custom{
    class ObjectManager {
    public:
        void readFromFile(const std::string&);
        void writeIntoFile(const std::string file = "default.txt");
        void addObject();
    public:
        void GroupByDistance();
        void GroupByName();
        void GroupByCreationTime();
        void GroupByType(std::size_t);
    private:
        std::time_t startOfDay(std::time_t time);
        std::string getTimeGroup(const custom::Object& obj);
        std::stringstream ss;
        std::vector<Object> objList;
        std::string bufToPrint;
    };
}




