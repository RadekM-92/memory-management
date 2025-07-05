#include <iostream>
#include <memory>
#include <vector>
#include <string>

using namespace std;

struct Resource
{
    Resource(char* byte) : byte_(byte) {}
    char* byte() const { return byte_; }
    virtual string name() const = 0;
    ~Resource() { delete[] byte_; }

protected:
    char* byte_ = nullptr;
};

struct ResourceA : Resource
{
    ResourceA(char* byte) : Resource(byte) {}
    string name() const override { return string("ResourceA ").append(byte_); }
};

struct ResourceB : Resource
{
    ResourceB(char* byte) : Resource(byte) {}
    string name() const override { return string("ResourceB ").append(byte_); }
};

struct ResourceFactory
{ 
    std::shared_ptr<Resource> makeResourceA(char* byte) { return std::make_shared<ResourceA>(byte); }
    std::shared_ptr<Resource> makeResourceB(char* byte) { return std::make_shared<ResourceB>(byte); }
};

struct ResourceCollection
{
    void add(std::shared_ptr<Resource> r) { resources.push_back(r); }
    void clear() { resources.clear(); }
    std::shared_ptr<Resource> operator[](int index) { return resources[index]; }
    void printAll()
    {
        for (const auto & res : resources)
        {
            cout << res->name() << endl;
        }
    }

private:
    vector<std::shared_ptr<Resource>> resources;
};

int main()
{
    ResourceCollection collection;
    ResourceFactory rf;
    collection.add(rf.makeResourceA(new char[2]{0x01, '\0'}));
    collection.add(rf.makeResourceB(new char[2]{0x02, '\0'}));
    collection.printAll();

    auto firstByte = collection[0]->byte();
    cout << *firstByte << endl; 
    collection.clear();
    return 0;
}

