//var4
//Вариант 4.
//a) Разработайте абстрактный тип данных  одномерный массив.
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
using namespace std;


class Massiv {
private:
    int* data;
    int size;

public:
    Massiv(int n = 0) {
        size = n;
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
        return data[index];
    }
    void set(int index, int value) {
        data[index] = value;
    }
};

//2

class ElectrDevice {
private:
    char* name;
    static double allmem;
    static int devcount;
    
protected:
    double memory;

public:
    ElectrDevice(const char* n, double memory) : memory(memory) {
        name = new char[strlen(n) + 1];
        strcpy_s(name, strlen(n) + 1, n);
        allmem += memory;
        devcount++;
    }
    virtual ~ElectrDevice() {
        delete[] name;
        devcount--;
        allmem -= memory;
    }

    virtual void show() {
        cout << "Name: " << name << ", memory: " << memory << " GB" << endl << endl;
    }
    virtual double getPeriodOfUsing() {
        return 5.0;
    }
    static double getSredMem() {
        if (devcount == 0)
            return 0;
        else
            return allmem / devcount;
    }
    double getMem() const {
        return memory;
    }
    const char* getName() const {
        return name;
    }

};
class Laptop : public ElectrDevice {
private:
    double screensize;

public:
    Laptop(const char* name, double mem, double screen)
        : ElectrDevice(name, mem), screensize(screen) {
    }

    void show() {
        cout << "Laptop: " << getName() << ", Memory: " << memory << " GB, Screen: " << screensize << endl << endl;
    }

    double getPeriodOfUsing() {
        return 10.0;
    }
};
class Smartphone : public ElectrDevice {
private:
    double battery;

public:
    Smartphone(const char* name, double mem, double batt)
        : ElectrDevice(name, mem), battery(batt) {
    }

    void show() {
        cout << "Smartphone: " << getName() << ", Memory: " << memory
            << " GB, Battery: " << battery << " mAh" << endl << endl;
    }

    double getPeriodOfUsing() {
        return 4.0;
    }
};

template<typename T>
class DeviceArray {
private:
    T** arr;
    int size;
public:
    DeviceArray(int s) {
        size = s;
        arr = new T * [s];
        for (int i = 0; i < s; i++) {
            arr[i] = nullptr;
        }
    }
    ~DeviceArray() {
        for (int i = 0; i < size; i++) {
            delete arr[i];
        }
        delete[] arr;
    }
    void set(int index, T* device) {
        if (index >= 0 && index < size) {
            delete arr[index];
            arr[index] = device;
        }
    }
    T* operator[](int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        }
        return nullptr;
    }
    int getSize() {
        return size;
    }
    void showAll() {
        for (int i = 0; i < size; i++) {
            if (arr[i] != nullptr) {
                arr[i]->show();
            }
        }
    }
    void showAverageMemory() {
        cout << "Average memory of all devices: " << ElectrDevice::getSredMem() << " GB" << endl << endl;
    }
};
double ElectrDevice::allmem = 0;
int ElectrDevice::devcount = 0;

int main() {
    Massiv arr(5);

    for (int i = 0; i < 5; i++) {
        arr[i] = i * 10;
    }

    int size = arr;
    cout << "Size: " << size << ", element 2: " << arr[2] << endl << endl;

    Laptop laptop("Dell", 512, 15.6);
    Smartphone phone("iPhone", 128, 3000);

    laptop.show();
    phone.show();

    cout << "Time for using Dell: " << laptop.getPeriodOfUsing() << "years." << endl;
    cout << "Time for using iPhone: " << phone.getPeriodOfUsing() << "years." << endl;

    cout << "Sred memory: " << ElectrDevice::getSredMem() << endl << endl;

    DeviceArray<ElectrDevice> devices(3);

    devices.set(0, new Laptop("ASUS", 1024, 17.3));
    devices.set(1, new Smartphone("Pixel", 256, 4000));
    devices.set(2, new Laptop("HP", 512, 15.6));

    devices.showAll();

    cout << "Dostup 1: ";
    devices[1]->show();

    cout << "Size of massiv: " << devices.getSize() << endl << endl;

    return 0;
}