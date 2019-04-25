// 4_3. Тупики.
// На вокзале есть некоторое количество тупиков, куда прибывают электрички. Этот вокзал является их конечной станцией. Дано расписание движения электричек, в котором для каждой электрички указано время ее прибытия, а также время отправления в следующий рейс. Электрички в расписании упорядочены по времени прибытия. Когда электричка прибывает, ее ставят в свободный тупик с минимальным номером. При этом если электричка из какого-то тупика отправилась в момент времени X, то электричку, которая прибывает в момент времени X, в этот тупик ставить нельзя, а электричку, прибывающую в момент X+1 — можно.
// В данный момент на вокзале достаточное количество тупиков для работы по расписанию.
// Напишите программу, которая по данному расписанию определяет, какое минимальное количество тупиков требуется для работы вокзала.
// Формат входных данных. Вначале вводится n - количество электричек в расписании. Затем вводится n строк для каждой электрички, в строке - время прибытия и время отправления. Время - натуральное число от 0 до 10^9. Строки в расписании упорядочены по времени прибытия.
// Формат выходных данных. Натуральное число - минимальное количеством тупиков.
// Максимальное время: 50мс, память: 5Мб.

#include <iostream>

template <class T>
class MinHeap {
    public:
    MinHeap() : arraySize(0), numOfElements(0) {}
    ~MinHeap(){
        if(arraySize != 0) {
            delete[] array;
        }
    }
    void add(T obj);
    void remove(int index);
    T getMin();
    int getSize();
    bool isEmpty();
    private:
    T *array;
    int arraySize;
    int numOfElements;
    void siftUp(int index);
    void siftDown(int index);
};

template <class T>
void MinHeap<T>::siftUp(int index){
    int parent = (index - 1) / 2;
    while(index > 0 && array[parent] > array[index]){
        std::swap(array[parent], array[index]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

template <class T>
void MinHeap<T>::siftDown(int index){
    int leftChild = index * 2 + 1;
    int rightChild = index * 2 + 2;
    int smallest = index;
    while(index < (numOfElements / 2)){
        if(array[leftChild] < array[smallest]){
            smallest = leftChild;
        }
        if(array[rightChild] < array[smallest]) {
            smallest = rightChild;
        }
        if(smallest == index){
            break;
        } else {
            std::swap(array[index], array[smallest]);
            index = smallest;
            leftChild = index * 2 + 1;
            rightChild = index * 2 + 2;
        }
    }
}

template <class T>
void MinHeap<T>::add(T obj){
    if(arraySize == 0){
        arraySize = 1;
        array = new T [arraySize];
    }
    else if(numOfElements == arraySize){
        arraySize *= 2;
        T *tmp = new T [arraySize];
        for(int i = 0; i < numOfElements; ++i){
            tmp[i] = array[i];
        }
        delete[] array;
        array = tmp;
    }
    array[numOfElements++] = obj;
    siftUp(numOfElements-1);
}

template <class T>
T MinHeap<T>::getMin(){
    T tmp = array[0];
    array[0] = array[--numOfElements];
    siftDown(0);
    return tmp;
}

template <class T>
int MinHeap<T>::getSize(){
    return numOfElements;
}

template <class T>
bool MinHeap<T>::isEmpty(){
    return (numOfElements == 0) ? true : false;
}

int calculateNumberOfStops(MinHeap<int>& arrivalTime, MinHeap<int>& departionTime){
    int maxNumberOfStops = 0;
    int curNumberOfStops = 0;
    int aTime = -1;  // Arrival Time
    int dTime = -1;  // Departion Time
    
    aTime = arrivalTime.getMin();
    dTime = departionTime.getMin();

    while(!arrivalTime.isEmpty() && !departionTime.isEmpty()){
        if(aTime <= dTime){
            curNumberOfStops++;
            aTime = arrivalTime.getMin();
        } else {
            curNumberOfStops--;
            dTime = departionTime.getMin();
        }
        if(curNumberOfStops > maxNumberOfStops){
            maxNumberOfStops = curNumberOfStops;
        }
    }
    if(aTime <= dTime){
        curNumberOfStops++;
        if(maxNumberOfStops < curNumberOfStops){
            maxNumberOfStops = curNumberOfStops;
        }
    }
    
    return maxNumberOfStops;
}

int main(){
    int n;
    std::cin >> n;
    MinHeap<int> arrivalTime;
    MinHeap<int> departionTime;

    int tmp;
    for(int i = 0; i < n; ++i){
        std::cin >> tmp;
        arrivalTime.add(tmp);
        std::cin >> tmp;
        departionTime.add(tmp);
    }

    std::cout << calculateNumberOfStops(arrivalTime, departionTime) << std::endl;

    return 0;
}