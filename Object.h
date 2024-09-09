#pragma once

#include <string>
#include <sstream>
#include <ctime>
#include <cmath>

namespace custom{
    class Object final{
    public:
        Object(std::string n,double _x, double _y, std::string t,double ct):
                name(n), x(_x),y(_y), type(t), creationTime(ct){}
        ~Object() = default;

        [[nodiscard]] double getDistance() const{
            return std::sqrt(x*x + y*y);
        }

        [[nodiscard]] std::string formatTime() const{
            std::stringstream ss;
            time_t raw_time = static_cast<time_t>(creationTime);
            std::tm* time_info = std::gmtime(&raw_time);
            ss << "Date and Time: " << std::put_time(time_info, "%Y-%m-%d %H:%M:%S");
            double fractional_part = creationTime - static_cast<long>(creationTime);
            ss << "." << static_cast<int>(fractional_part * 1000000) << " seconds" << std::endl;
            return ss.str();
        }

        std::string name;
        double x, y;
        std::string type;
        double creationTime;
    };
}



