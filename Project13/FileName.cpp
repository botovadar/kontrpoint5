//var4
//Вариант 4.
//a) Разработайте абстрактный тип данных − одномерный массив.
//Дополнительно перегрузить следующие операции :
//int() - размер массива;
//[] - доступ по индексу.
//b) Разработайте иерархию классов электронные устройства(приватные
//члены сконструировать самостоятельно).Добавьте статические члены по
//подсчету среднего значения емкости памяти всех электронных устройств.
//Разработайте не менее 2 - х виртуальных функций.
//c) Создайте шаблонный класс одномерного массива электронных
//устройств.Продемонстрируйте работу класса и все его операции.


#include <iostream>
#include <cstring>
#include <stdexcept>
#include <string>
using namespace std;

class Massiv {
private:
    int* data;
    int size;
public:
    Massiv(int n = 0) : size(n) {
        if (n > 0)
            data = new int[n];
        else
            data = nullptr;
    }

    ~Massiv() {
        delete[] data;
    }

    operator int() const {
        return size;
    }

    int& operator[](int index) {
        if (index < 0 || index >= size)
            throw out_of_range("Index out of range");
        return data[index];
    }

    void set(int index, int value) {
        if (index >= 0 && index < size)
            data[index] = value;
    }
};

class ElectrDevice {
private:
    string name;
    static double allmem;
    static int devcount;
protected:
    double memory;
public:
    ElectrDevice(const string& n, double memory) : name(n), memory(memory) {
        allmem += memory;
        devcount++;
    }

    virtual ~ElectrDevice() {
        devcount--;
        allmem -= memory;
    }

    virtual void show() const {
        cout << "Name: " << name << ", memory: " << memory << " GB";
    }

    virtual double getPeriodOfUsing() const {
        return 5.0;
    }

    static double getSredMem() {
        if (devcount == 0) return 0;
        return allmem / devcount;
    }

    double getMem() const { return memory; }
    string getName() const { return name; }

    bool operator==(const ElectrDevice& other) const {
        return memory == other.memory && name == other.name;
    }
    ElectrDevice(const ElectrDevice& other) : name(other.name), memory(other.memory) {
        allmem += memory;
        devcount++;
    }
};

class Laptop : public ElectrDevice {
private:
    double screensize;
public:
    Laptop(const string& name, double mem, double screen)
        : ElectrDevice(name, mem), screensize(screen) {
    }

    void show() const override {
        ElectrDevice::show();
        cout << ", screen: " << screensize << "\"";
    }

    double getPeriodOfUsing() const override {
        return 10.0;
    }
};

class Smartphone : public ElectrDevice {
private:
    double battery;
public:
    Smartphone(const string& name, double mem, double batt)
        : ElectrDevice(name, mem), battery(batt) {
    }

    void show() const override {
        ElectrDevice::show();
        cout << ", battery: " << battery << " mAh";
    }

    double getPeriodOfUsing() const override {
        return 4.0;
    }
};

double ElectrDevice::allmem = 0;
int ElectrDevice::devcount = 0;

template<typename T>
class DeviceArray {
private:
    T** elems;
    int count;
    int maxsize;

    void printElem(int val) const {
        cout << val;
    }

    void printElem(double val) const {
        cout << val;
    }

    void printElem(const char* str) const {
        cout << str;
    }

    void printElem(const ElectrDevice& elem) const {
        elem.show();
    }

public:
    DeviceArray(int maxSz = 10) : maxsize(maxSz), count(0) {
        elems = new T * [maxsize];
        for (int i = 0; i < maxsize; i++)
            elems[i] = nullptr;
    }

    DeviceArray(const DeviceArray& other) : maxsize(other.maxsize), count(other.count) {
        elems = new T * [maxsize];
        for (int i = 0; i < count; i++)
            elems[i] = new T(*other.elems[i]);
        for (int i = count; i < maxsize; i++)
            elems[i] = nullptr;
    }

    ~DeviceArray() {
        for (int i = 0; i < count; i++)
            delete elems[i];
        delete[] elems;
    }

    DeviceArray<T>& operator=(const DeviceArray<T>& op) {
        if (this == &op)
            return *this;
        for (int i = 0; i < count; i++)
            delete elems[i];
        delete[] elems;
        maxsize = op.maxsize;
        count = op.count;
        elems = new T * [maxsize];
        for (int i = 0; i < count; i++)
            elems[i] = new T(*op.elems[i]);
        for (int i = count; i < maxsize; i++)
            elems[i] = nullptr;
        return *this;
    }

    void add(const T& elem) {
        if (count >= maxsize) {
            cout << "Full massive";
            return;
        }
        for (int i = 0; i < count; i++)
            if (*elems[i] == elem) return;
        elems[count++] = new T(elem);
    }

    bool operator>(const T& elem) const {
        for (int i = 0; i < count; i++)
            if (*elems[i] == elem) return true;
        return false;
    }

    DeviceArray<T> operator*(const DeviceArray<T>& other) const {
        DeviceArray<T> res(maxsize);
        for (int i = 0; i < count; i++)
            if (other > *elems[i])
                res.add(*elems[i]);
        return res;
    }

    bool operator<(const DeviceArray<T>& other) const {
        for (int i = 0; i < count; i++)
            if (!(other > *elems[i])) return false;
        return true;
    }

    T& operator[](int index) {
        if (index >= 0 && index < count)
            return *elems[index];
        throw out_of_range("Index out of range");
    }

    operator int() const {
        return count;
    }

    void show() const {
        cout << "[ ";
        for (int i = 0; i < count; i++) {
            printElem(*elems[i]);
            cout << " ";
        }
        cout << "]" << endl;
    }

    void showAverageMemory() const {
        cout << "Average memory of all devices: " << ElectrDevice::getSredMem() << " GB" << endl;
    }

    int getCount() const { return count; }
    int getMaxSize() const { return maxsize; }
};

int main() {
    Massiv arr(5);
    for (int i = 0; i < 5; i++)
        arr[i] = i * 10;

    int size = arr;
    cout << "Massiv size: " << size << ", element 2: " << arr[2] << endl;
    arr.set(0, 100);
    cout << "After set(0, 100): " << arr[0] << endl << endl;

    Laptop laptop("Dell", 512, 15.6);
    Smartphone phone("iPhone", 128, 3000);

    cout << "Devices:" << endl;
    laptop.show();
    cout << endl;
    phone.show();
    cout << endl;

    cout << "Laptop period: " << laptop.getPeriodOfUsing() << " years" << endl;
    cout << "Phone period: " << phone.getPeriodOfUsing() << " years" << endl;
    cout << "Average memory: " << ElectrDevice::getSredMem() << " GB" << endl << endl;

    Laptop laptop2("Dell", 512, 15.6);
    cout << "Laptop == laptop2: " << (laptop == laptop2 ? "true" : "false") << endl;

    Smartphone phone2("iPhone", 128, 3000);
    cout << "Phone == phone2: " << (phone == phone2 ? "true" : "false") << endl;
    cout << "Laptop == phone: " << (laptop == phone ? "true" : "false") << endl << endl;

    cout << "Laptop memory (getMem): " << laptop.getMem() << " GB" << endl;
    cout << "Phone name (getName): " << phone.getName() << endl << endl;

    DeviceArray<int> intArray(5);
    intArray.add(10);
    intArray.add(20);
    intArray.add(30);
    cout << "Int array: ";
    intArray.show();
    int arrlen = intArray;
    cout << "Array length iz operator int: " << arrlen << endl << endl;
    cout << "Count: " << intArray.getCount() << endl;
    cout << "Element 0: " << intArray[0] << endl << endl;

    DeviceArray<ElectrDevice> devices(5);
    devices.add(Laptop("ASUS", 1024, 17.3));
    devices.add(Smartphone("Pixel", 256, 4000));
    devices.add(Laptop("HP", 512, 15.6));

    cout << "Devices array: ";
    devices.show();
    devices.showAverageMemory();

    cout << "Period of device[0]: " << devices[0].getPeriodOfUsing() << " years" << endl;
    cout << "Period of device[1]: " << devices[1].getPeriodOfUsing() << " years" << endl << endl;

    DeviceArray<ElectrDevice> devices2(3);
    devices2 = devices;
    cout << "Copied array: ";
    devices2.show();
    cout << endl;

    DeviceArray<ElectrDevice> devices3(devices);
    cout << "Copy construct array: ";
    devices3.show();
    cout << endl;

    DeviceArray<int> arr1(5);
    arr1.add(1);
    arr1.add(2);
    arr1.add(3);

    DeviceArray<int> arr2(5);
    arr2.add(2);
    arr2.add(3);
    arr2.add(4);

    DeviceArray<int> intrsc = arr1 * arr2;
    cout << "Peresechenie: ";
    intrsc.show();

    DeviceArray<int> arr3(5);
    arr3.add(2);
    arr3.add(3);

    cout << "arr1 < arr2: " << (arr1 < arr2 ? "true" : "false") << endl;
    cout << "arr3 < arr1: " << (arr3 < arr1 ? "true" : "false") << endl;

    return 0;
}
