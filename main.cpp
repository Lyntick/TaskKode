#include <iostream>

#include "ObjectManager.h"

int main() {


    bool inf = true;
    size_t N = 3;//number of types to group
    custom::ObjectManager objM;
    objM.readFromFile("file.txt");
    while(inf){
        std::cout << "1-Add elem to list\n2-GroupBy Distance\n"
                     "3-GroupBy Name\n4-GroupBy CreationTime\n5-GroupBy Type\n"
                     "6-Save\n7-Exit\nChoose action:";
        int choice = 0;
        std::cin >> choice;
        switch (choice) {
            case 1: objM.addObject();
                break;
            case 2: objM.GroupByDistance();
                break;
            case 3: objM.GroupByName();
                break;
            case 4: objM.GroupByCreationTime();
                break;
            case 5: objM.GroupByType(N);
                break;
            case 6: objM.writeIntoFile();
                break;
            case 7: inf = false;
                break;
        }
    }
    return 0;
}
