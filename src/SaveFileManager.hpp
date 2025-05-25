//
// Created by Michele Antonio Pipicelli on 25/5/2025.
//

#ifndef SAVEFILEMANAGER_HPP
#define SAVEFILEMANAGER_HPP
#include <string>


class SaveFileManager {
    public:
        SaveFileManager();
        ~SaveFileManager();
        void saveFile(std::string fileName);
        void loadFile(std::string fileName);
        std::string generateFileName();
    private:
        bool isValidFloat(const std::string& s, float& result);
};



#endif //SAVEFILEMANAGER_HPP
