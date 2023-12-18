#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

// 生成包含随机整数的数组
void generateRandomArray(int arr[], int size) {
    srand(static_cast<unsigned>(time(0))); // 设置随机数种子

    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 1000; // 生成0到999之间的随机整数
    }
}

// 将数组写入文件
void writeArrayToFile(const char* filename, int arr[], int size) {
    std::ofstream outFile(filename);

    if (outFile.is_open()) {
        for (int i = 0; i < size; ++i) {
            outFile << arr[i] << " ";
            if ((i+1) % 20 == 0) {
                outFile << "\n";
            }
        }
        outFile.close();
        std::cout << "Array written to file: " << filename << std::endl;
    } else {
        std::cerr << "Unable to open file for writing." << std::endl;
    }
}

// 从文件中读取数组
void readArrayFromFile(const char* filename, int arr[], int size) {
    std::ifstream inFile(filename);

    if (inFile.is_open()) {
        for (int i = 0; i < size; ++i) {
            inFile >> arr[i];
        }
        inFile.close();
        std::cout << "Array read from file: " << filename << std::endl;
    } else {
        std::cerr << "Unable to open file for reading." << std::endl;
    }
}

// 打印数组内容
void printArray(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    const int arraySize = 100000; // 设置数组大小
    int myArray[arraySize];

    // 生成随机数组
    generateRandomArray(myArray, arraySize);

    // 打印数组内容
    std::cout << "Original Array: ";
    printArray(myArray, arraySize);

    // 将数组写入文件
    writeArrayToFile("random_array.txt", myArray, arraySize);

    // 从文件中读取数组
    int newArray[arraySize];
    readArrayFromFile("random_array.txt", newArray, arraySize);

    // 打印从文件中读取的数组内容
    std::cout << "Array from file: ";
    printArray(newArray, arraySize);

    return 0;
}
