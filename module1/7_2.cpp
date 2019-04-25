// 7_2. LSD для unsigned long long.
// Дан массив неотрицательных целых 64-битных чисел. Количество чисел не больше 10^6.
// Отсортировать массив методом поразрядной сортировки LSD по байтам.

#include <iostream>
#include <cstring>

typedef unsigned long long ull;

int getByte(ull number, int byteIndex);

int getByte(ull number, int byteIndex){
    number <<= 8 * (8-byteIndex);
    number >>= 8 * 7;
    return number;
}

void LSD(ull *array, int n){
    // При поразрядной сортировке по байтам размер алфавита -- 256
    int *countingArray = new int[256];
    ull *tmpArray = new ull[n];
    for(int curByte = 1; curByte <= 8; ++curByte){
        for(int i = 0; i < n; ++i){
            ++countingArray[getByte(array[i], curByte)];
        }
        for(int i = 1; i < 256; ++i){
            countingArray[i] += countingArray[i-1];
        }
        for(int i = n-1; i >= 0; --i){
            tmpArray[--countingArray[getByte(array[i], curByte)]] = array[i];
        }
        std::memcpy(array, tmpArray, sizeof(ull)*n);
        std::memset(countingArray, 0, sizeof(int)*256);
    }
    delete[] tmpArray;
}

int main(){
    int n = 0;
    
    std::cin >> n;

    ull *array = new ull [n];

    for(int i = 0; i < n; ++i){
        std::cin >> array[i];
    }

    LSD(array, n);

    for(int i = 0; i < n; ++i){
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    delete[] array;
    return 0;
}