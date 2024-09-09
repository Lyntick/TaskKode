
#include "ObjectManager.h"


void custom::ObjectManager::readFromFile(const std::string &filename) {
    std::ifstream file;
    std::string name, type;
    double x, y;
    double time;
    try{
        file.open(filename);
        if(!file.is_open()){
            std::cerr << "file doesn't open" << std::endl;
        }
        while (file >> name >> x >> y >> type >> time) {
            objList.emplace_back(name, x, y, type, time);
        }
    }catch(const std::ifstream::failure& fail){
        std::cerr << "Error code: " <<fail.code() << "\nwhat: " << fail.what() <<  std::endl;
    }
    file.close();

}

void custom::ObjectManager::addObject() {
    std::string name, type;
    double x, y;
    double time;
    std::cout << "Enter name:";
    std::cin.clear();
    std::cin.ignore(2);
    std::getline(std::cin, name, '\n');
    std::cout << "Enter type:";
    std::getline(std::cin, type, '\n');
    std::cout << "Enter x,y and time separated by space:";

    std::cin >> x >> y >> time;
}


void custom::ObjectManager::writeIntoFile(const std::string filename) {
    try{
        std::ofstream file(filename);
        file << ss.str();
    }catch (const std::ofstream::failure& fail){
        std::cerr << fail.what() << std::endl;
    }
}


time_t custom::ObjectManager::startOfDay(time_t time) {
    struct tm* timeInfo = localtime(&time);
    timeInfo->tm_hour = 0;
    timeInfo->tm_min = 0;
    timeInfo->tm_sec = 0;
    return mktime(timeInfo);
}


std::string custom::ObjectManager::getTimeGroup(const custom::Object& obj) {
    time_t now = time(nullptr);  //get current time
    time_t objTime = obj.creationTime;

    time_t today = startOfDay(now);

    if (objTime >= today) {
        return "Сегодня";
    }

    time_t yesterday = today - 86400;  // 86400 sec in a day
    if (objTime >= yesterday) {
        return "Вчера";
    }

    struct tm* timeInfo = localtime(&now);
    timeInfo->tm_wday = (timeInfo->tm_wday == 0) ? 6 : timeInfo->tm_wday - 1;
    time_t startOfWeek = today - timeInfo->tm_wday * 86400;

    if (objTime >= startOfWeek) {
        return "На этой неделе";
    }

    timeInfo = localtime(&now);
    timeInfo->tm_mday = 1;
    time_t startOfMonth = mktime(timeInfo);
    if (objTime >= startOfMonth) {
        return "В этом месяце";
    }

    timeInfo = localtime(&now);
    timeInfo->tm_mon = 0;
    timeInfo->tm_mday = 1;
    time_t startOfYear = mktime(timeInfo);
    if (objTime >= startOfYear) {
        return "В этом году";
    }

    return "Ранее";
}


void custom::ObjectManager::GroupByDistance() {
    ss.clear();
    std::sort(objList.begin(), objList.end(), [](const Object& elem1, const Object& elem2){
        return elem1.getDistance() < elem2.getDistance();
    });

    size_t number[4] = {100, 1000, 10000, UINT32_MAX};
    auto fun = [&number](int j)-> std::string{
        if(number[j] <= 10000){
            return std::to_string(number[j]);
        }else{
            return "Слишком далеко";
        }
    };
    ss << "Группировка по расстоянию:\n";
    for(int j = 0; j < 4; ++j){
        ss << "\nГруппа: До " << fun(j) <<" единиц\n" << std::setw(10)
           << "Имя" << std::setw(15)<< " Координаты " << std::setw(10)<< "Тип" << std::setw(20) << " Время создания" << std::endl;
        for (int i = 0; objList[i].getDistance() <= number[j] && i < objList.size(); ++i) {
            ss << std::setw(10) << objList[i].name << ' '
               << std::setw(8) << objList[i].x << ", " << objList[i].y << ' '
               << std::setw(10) << objList[i].type << ' '
               << std::setw(20) << objList[i].formatTime()
               << std::endl;
        }
    }
}

void custom::ObjectManager::GroupByName() {//todo
    ss.clear();
    std::sort(objList.begin(), objList.end(), [](const Object& elem1, const Object& elem2){
        return elem1.name[0] < elem2.name[0];
    });
    char theS = 'a';
    ss << "Группировка по имени:\n";
    for(int i = 0; i < objList.size();){
        if(theS < objList[i].name[0]){
            ss << "\nГруппа: " << '#' << "\n" << std::setw(10)
               << "Имя" << std::setw(15)<< " Координаты " << std::setw(10)<< "Тип" << std::setw(20) << " Время создания" << std::endl;
        }else{
            theS = objList[i].name[0];
            ss << "\nГруппа: " << theS << "\n" << std::setw(10)
               << "Имя" << std::setw(15)<< " Координаты " << std::setw(10)<< "Тип" << std::setw(20) << " Время создания" << std::endl;
        }
        for(;i < objList.size() && objList[i].name[0] == theS;++i){
            ss << std::setw(10) << objList[i].name << ' '
               << std::setw(8) << objList[i].x << ", " << objList[i].y << ' '
               << std::setw(10) << objList[i].type << ' '
               << std::setw(20) << objList[i].formatTime()
               << std::endl;
        }
    }

}

void custom::ObjectManager::GroupByCreationTime() {//todo
    ss.clear();
    std::sort(objList.begin(), objList.end(), [](const Object& elem1, const Object& elem2){
        return elem1.creationTime < elem2.creationTime;
    });
    ss << "Группировка по времени создания:\n";
    std::string preGroup;
    for(const auto& obj : objList){
        std::string curGroup = getTimeGroup(obj);
        if(preGroup != curGroup){
            ss << "\nГруппа: " << curGroup << "\n" << std::setw(10)
              << "Имя" << std::setw(15)<< " Координаты " << std::setw(10)<< "Тип" << std::setw(20) << " Время создания" << std::endl;
            preGroup = curGroup;
        }
        ss << std::setw(10) << obj.name << ' '
           << std::setw(8) << obj.x << ", " << obj.y << ' '
           << std::setw(10) << obj.type << ' '
           << std::setw(20) << obj.formatTime()
           << std::endl;
    }
}

void custom::ObjectManager::GroupByType(std::size_t N) { // N - if number of objects more create group
    ss.clear();//todo
    std::unordered_map<std::string,int> um;
    for(auto item : objList){
        auto iterUM = um.find(item.type);
        if(iterUM == um.end()){
            um.insert({item.type,1});
        }else{
            iterUM->second++;
        }
    }
    ss << "Группировка по типу:\n";
    for(int i = 0, j = objList.size() - 1; i < objList.size();){
        auto iterUM = um.find(objList[i].type);
        if(iterUM->second >= N){
            ss << "\nГруппа: " << objList[i].type << "\n" << std::setw(10)
               << "Имя" << std::setw(15)<< " Координаты " << std::setw(10)<< "Тип" << std::setw(20) << " Время создания" << std::endl;
            for(; i < objList.size() && objList[i].type == iterUM->first;++i){
                ss << std::setw(10) << objList[i].name << ' '
                   << std::setw(8) << objList[i].x << ", " << objList[i].y << ' '
                   << std::setw(10) << objList[i].type << ' '
                   << std::setw(20) << objList[i].formatTime()
                   << std::endl;
            }
        }else{
            if(i < j){
                std::swap(objList[i], objList[j]);
                --j;
            }else{
                ss << "\nГруппа: " << "Разное"<< "\n" << std::setw(10)
                   << "Имя" << std::setw(15)<< " Координаты " << std::setw(10)<< "Тип" << std::setw(20) << " Время создания" << std::endl;
                for(; i < objList.size();++i){
                    ss << std::setw(10) << objList[i].name << ' '
                       << std::setw(8) << objList[i].x << ", " << objList[i].y << ' '
                       << std::setw(10) << objList[i].type << ' '
                       << std::setw(20) << objList[i].formatTime()
                       << std::endl;
                }
            }
        }
    }
}


