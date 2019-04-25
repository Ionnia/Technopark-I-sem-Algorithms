// Баймаканов В.К. АПО-11
// 1_3. Даны два строго возрастающих массива целых чисел A[0..n) и B[0..m) и число k.
// Найти количество таких пар индексов (i, j), что A[i] + B[j] = k. Время работы O(n + m).
// n, m ≤ 100000.

#include <memory>
#include <iostream>
#include <istream>

template <typename T>
class DynamicArray {
    public:
        DynamicArray(int arraySize) : numOfElements(0){
            this->arraySize = arraySize;
            array = new T[arraySize];
        }

        DynamicArray() : DynamicArray(16) {};

        ~DynamicArray() { 
            delete[] array; 
        }

        T& get(int i){
            return array[i];
        }

        void add(T obj){
            if(numOfElements == arraySize){
                arraySize *= 2;
                T* tmp = new T[arraySize];
                for(int i = 0; i < numOfElements; ++i){
                    tmp[i] = array[i];
                }
                delete[] array;
                array = tmp;
            }
            array[numOfElements++] = obj;
        }

        void reverse(){
            for(int i = 0; i < numOfElements/2; ++i){
                std::swap(array[i], array[numOfElements-i-1]);
            }
        }
        
    private:
        T* array;
        int arraySize;
        int numOfElements;
};


void getArray(DynamicArray<int>& array, const int &numOfElements) {
    int tmp;
    for(int i = 0; i < numOfElements; ++i) {
        std::cin >> tmp;
        array.add(tmp);
    }
}

int getResult(DynamicArray<int>& A, DynamicArray<int>& B, int n, int m, int k) {
    int resultCounter = 0;
    for(int i = 0, j = 0; i < n && j < m;) {
        if(A.get(i) + B.get(j) == k) {
            ++resultCounter;
            ++i;
            ++j;
        } else if(A.get(i) + B.get(j) < k) {
            ++i;
        } else {
            ++j;
        }
    }
    return resultCounter;
}

int main() {
    int n, m, k;

    std::cin >> n;
    DynamicArray<int> A(n);
    getArray(A, n);
    std::cin >> m;
    DynamicArray<int> B(m);
    getArray(B, m);
    std::cin >> k;

    B.reverse();
    std::cout << getResult(A, B, n, m, k) << std::endl;

    return 0;
}