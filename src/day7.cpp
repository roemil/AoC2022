#include "../include/FileReader.h"
#include <string>
#include <vector>
#include <iostream>
#include <memory>

class File
{
    public:
        File(const int fileSize, const std::string& name) : fileSize_(fileSize), name_(name) {};

    private:
        int fileSize_;
        std::string name_;
};

class Node
{
    public:
        Node(const std::string& name) : name_(name){};
        int size_;
        std::string name_;
        std::vector<Node*> dirs_;
        std::vector<File*> files_;
        Node* next;
        Node* parent;

        ~Node()
        {
            for(auto& dir : dirs_)
            {
                delete dir;
            }
            for(auto& file : files_)
            {
                delete file;
            }
        }
};

int countNumRows(const std::vector<std::string>& lines, int startIndex)
{
    int count = 0;
    for(int i = startIndex; i < lines.size(); ++i)
    {
        auto line = lines[i];
        if(line[0] == '$')
        {
            break;
        }
        count++;
    }
    return count;
}

int main(){
    FileReader fr;
    auto readLines = fr.readLines("data/input_test.txt");

    Node * head = new Node("dummy");
    auto currentHead = head;

    for(int i = 0; i < readLines.size(); ++i)
    {
        auto line = readLines[i];
        std::cout << line << std::endl;
        if(line.substr(0,7) == "$ cd ..")
        {
            if(currentHead && currentHead->parent)
            {
                std::cout << "Backing to " << currentHead->parent->name_ << std::endl;
                currentHead = currentHead->parent;
                continue;
            }
        }
        if(line.substr(0,4) == "$ cd")
        {
            std::string dirName = line.substr(line.find("cd ") + 3); 
            const auto& dir = currentHead->dirs_.begin();
            for(const auto& dir : currentHead->dirs_)
            {
                if(dir->name_ == dirName)
                {
                    std::cout << "Moving into " << dirName << std::endl;
                    currentHead->next = dir;
                    break;
                }
            }
            if(dir == currentHead->dirs_.end())
            {
                std::cout << "Creating and cd into " << dirName << std::endl;
                Node* newDir = new Node(dirName);
                newDir->parent = currentHead;
                currentHead->next = newDir;
            }
            Node* parent = currentHead;
            currentHead = currentHead->next;
            currentHead->parent = parent;
            continue;
        }
        if(line.substr(0,4) == "$ ls")
        {
            int numRows = countNumRows(readLines, i+1);
            for(int j = i+1; j <=i+numRows; ++j)
            {
                auto insideLine = readLines[j];
                std::cout << "insideLine " << insideLine << std::endl;
                if(insideLine.substr(0, 3) == "dir")
                {
                    std::string dirName = insideLine.substr(insideLine.find("dir ") + 4);
                    std::cout << "Creating new Dir " << dirName << std::endl;
                    Node* newDir = new Node(dirName);
                    currentHead->dirs_.push_back(newDir);
                }
                else
                {
                    int fileSize = std::stoi(insideLine.substr(0, insideLine.find(" ")));
                    std::cout << "Filesize: " << fileSize << std::endl;
                    std::string fileName = insideLine.substr(insideLine.find(" ") + 1);
                    std::cout << "FileName: " << fileName << std::endl;
                    File* newFile = new File(fileSize, fileName);
                    currentHead->files_.push_back(newFile);
                }
            }
        }
    }

/*     auto currentHead = head;
    while(currentHead)
    {
        // print name of dir
        std::cout << currentHead->name_ << std::endl;
        for(const auto& dir : currentHead->dirs_)
        {

        }
        // print all files inside dir
        for(const auto& file : currentHead->files_)
        {
            std::cout << "File: " << file->name_ << " Size: " << file->fileSize_ std::endl;
        }
    }*/


    return 0;
}