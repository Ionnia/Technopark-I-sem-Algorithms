// 2_2. Дан массив целых чисел А[0..n-1]. Известно, что на интервале [0, m] значения массива
//  строго возрастают, а на интервале [m, n-1] строго убывают. Найти m за O(log m).
//  2 ≤ n ≤ 10000.

#include <iostream>

template <typename T>
class DynamicArray {
    public:
        DynamicArray(int arraySize) : numOfElements(0){
            this->arraySize = arraySize;
            array = new T[arraySize];
        }

        DynamicArray() : DynamicArray(16) {};

        ~DynamicArray() { delete[] array; }

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

        T& operator[] (int index) {
            return array[index];
        }
        
    private:
        T* array;
        int arraySize;
        int numOfElements;
};

void getArray(DynamicArray<int>& array, const int& numOfElements) {
    int tmp;
    for(int i = 0; i < numOfElements; ++i) {
        std::cin >> tmp;
        array.add(tmp);
    }
}

int getM(DynamicArray<int>& A, const int& n){
    int windowSize = 2;
    int left = 0;
    int right = left + windowSize;
    // Находим промежуток, в котором есть индекс m за log(m)
    while(A[left] < A[left+1] && A[right-2] < A[right-1] && right != n){
        windowSize *= 2;
        left = right;
        right = left + windowSize;
        if(right > n){
            right = n;
        }
    }

    int curPosition = (left + right) / 2;

    // Находим m в этом промежутке тоже за log(m)
    do{
        if(curPosition > 0 && curPosition < n-1){
            if(A[curPosition-1] < A[curPosition] && A[curPosition] < A[curPosition+1]){
                left = curPosition+1;
                curPosition = (right + left)/2;
            } else if(A[curPosition-1] > A[curPosition] && A[curPosition] > A[curPosition+1]){
                right = curPosition-1;
                curPosition = (right + left)/2;
            }else{
                break;
            }
        } else {
            if(curPosition == 0){
                if(A[curPosition] > A[curPosition+1]){
                    break;
                } else {
                    curPosition = curPosition+1;
                    break;
                }
            } else {    // If curPosition == n-1
                if(A[curPosition] > A[curPosition-1]){
                    break;
                } else {
                    curPosition = curPosition-1;
                    break;
                }
            }
        }
    }while(true);

    return curPosition;
}

int main(){
    int n;

    std::cin >> n;
    DynamicArray<int> A(n);
    getArray(A, n);
    
    std::cout << getM(A, n) << std::endl;

    return 0;
}