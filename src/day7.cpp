#include "../include/FileReader.h"
#include <string>
#include <vector>
#include <iostream>
#include <memory>

class File
{
    public:
        File(const int fileSize, const std::string& name) : fileSize_(fileSize), name_(name) {};
        int getSize() {return fileSize_;};
        std::string getName() {return name_;};

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
        int part1 = 0;

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

void printFilesystem(Node* head, std::string indent)
{
    auto currentHead = head;
    std::cout << indent << "Dir: " << head->name_ << " size: " << head->size_ << std::endl;
    for(const auto& dir : currentHead->dirs_)
    {
        printFilesystem(dir, indent + "    ");
    }
    for(const auto& file : currentHead->files_)
    {
        std::cout << indent << " "<< "File: " << file->getName() << " Size: " << file->getSize() << std::endl;
    }

}

int sumDirectory(Node* head)
{
    auto currentHead = head;
    for(const auto& dir : currentHead->dirs_)
    {
        head->size_ += sumDirectory(dir);
    }
    for(const auto& file : currentHead->files_)
    {
        head->size_ += file->getSize();
    }
    return head->size_;
}

void sumDirectoryPart1(Node* head, int& res)
{
    auto currentHead = head;
    for(const auto& dir : currentHead->dirs_)
    {
        if(dir->size_ < 100000)
        {
            res += dir->size_;
        }
        sumDirectoryPart1(dir, res);
    }
}

void sumDirectoryPart2(Node* head, int& res, int target, std::vector<int>& dirs)
{
    auto currentHead = head;
    for(const auto& dir : currentHead->dirs_)
    {
        if(dir->size_ >= target)
        {
            res += dir->size_;
            dirs.push_back(dir->size_);
        }
        sumDirectoryPart2(dir, res, target, dirs);
    }
}

int main(){
    FileReader fr;
    auto readLines = fr.readLines("data/input_day7.txt");

    Node * head = new Node("dummy");
    auto currentHead = head;

    for(int i = 0; i < readLines.size(); ++i)
    {
        auto line = readLines[i];
        if(line.substr(0,7) == "$ cd ..")
        {
            if(currentHead && currentHead->parent)
            {
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
                    currentHead->next = dir;
                    break;
                }
            }
            if(dir == currentHead->dirs_.end())
            {
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
                if(insideLine.substr(0, 3) == "dir")
                {
                    std::string dirName = insideLine.substr(insideLine.find("dir ") + 4);
                    Node* newDir = new Node(dirName);
                    currentHead->dirs_.push_back(newDir);
                }
                else
                {
                    int fileSize = std::stoi(insideLine.substr(0, insideLine.find(" ")));
                    std::string fileName = insideLine.substr(insideLine.find(" ") + 1);
                    File* newFile = new File(fileSize, fileName);
                    currentHead->files_.push_back(newFile);
                }
            }
        }
    }

    currentHead = head->next;
    sumDirectory(currentHead);
    //printFilesystem(currentHead, "");
    int res = 0;
    sumDirectoryPart1(currentHead, res);
    std::cout << "Part1: " << res << std::endl;
    assert(res == 1453349);
    int res2 = 0;
    std::cout << "Total space used: " << currentHead->size_ << std::endl;
    int target = 30000000 - (70000000 - currentHead->size_);
    std::cout << "Total space left to reach 3MB: " << target << std::endl;

    std::vector<int> dirs{};
    sumDirectoryPart2(currentHead, res2, target, dirs);
    auto it = std::min_element(dirs.begin(), dirs.end());
    std::cout << "Min dir: " <<  *it << std::endl;
    assert(*it == 2948823);


    return 0;
}