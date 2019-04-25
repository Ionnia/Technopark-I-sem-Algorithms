// 5_2. Современники
// Группа людей называется современниками если был такой момент, когда они могли собраться вместе.
// Для этого в этот момент каждому из них должно было  уже исполниться 18 лет, но ещё не исполниться 80 лет.
// Дан список Жизни Великих Людей. Необходимо получить максимальное количество современников. 
// В день 18летия человек уже может принимать участие в собраниях, а в день 80летия и в день смерти уже не может.
// Замечание. Человек мог не дожить до 18-летия, либо умереть в день 18-летия. В этих случаях 
// принимать участие в собраниях он не мог.

#include <iostream>
#include <cstring>

struct Date {
    int day;
    int month;
    int year;
    bool isBirthDate;
};

class DateUtilities {
    public:
    static bool changeToValidTimeFrame(Date& birthDate, Date& deathDate);
    static void changeToPreviousDate(Date& date);
    static bool isSameDates(Date& d1, Date& d2);
};

template <class T>
void mergeSort(T *array, int size, bool comp(T& obj1, T& obj2));

template <class T>
void merge(T *array1, int size1, T *array2, int size2, T *mergeArray, bool comp(T& obj1, T& obj2));

bool DateUtilities::changeToValidTimeFrame(Date& birthDate, Date& deathDate){
    if(deathDate.year - birthDate.year < 18 || ( deathDate.year - birthDate.year == 18 
        && deathDate.month == birthDate.month && deathDate.day == birthDate.day ) ){
        return false;
    }
    Date startTmp(birthDate);
    Date endTmp(deathDate);

    // Если прошёл первую проверку, то значит ему больше 18 лет
    startTmp.year += 18;

    if(deathDate.year - birthDate.year > 80 || (deathDate.year - birthDate.year == 80 
        && deathDate.month == birthDate.month && deathDate.day == birthDate.day) ){
            endTmp.year = birthDate.year + 80;
            endTmp.month = birthDate.month;
            endTmp.day = birthDate.day;
            changeToPreviousDate(endTmp);
    } else {
        changeToPreviousDate(endTmp);
    }
    
    birthDate = startTmp;
    deathDate = endTmp;
    return true;
}

void DateUtilities::changeToPreviousDate(Date& date){
    if(date.day == 1){
        switch (date.month) {
            case 2: case 4: case 6:
            case 8: case 9: case 11:
                date.day = 31;
                --date.month;
                break;
            case 5: case 7: case 10: case 12:
                date.day = 30;
                --date.month;
                break;
            case 3: // Учёт високосного года
                if( (date.year % 4 == 0 && date.year % 100 != 0) || (date.year % 400 == 0)){
                    date.day = 29;
                } else {
                    date.day = 28;
                }
                --date.month;
            case 1:
                date.day = 31;
                date.month = 12;
                --date.year;
                break;
            default:
                break;
        }
    } else {
        --date.day;
    }
}

bool DateUtilities::isSameDates(Date& d1, Date& d2){
    return (d1.year == d2.year && d1.month == d2.month && d1.day == d2.day);
}

template <class T>
void mergeSort(T *array, int size, bool comp(T& obj1, T& obj2)){
    if(size <= 1){
        return;
    }
    int leftSize = size / 2;
    int rightSize = size - leftSize;
    mergeSort(array, leftSize, comp);
    mergeSort(array+leftSize, rightSize, comp);
    T *tmpArray = new T [size];
    merge(array, leftSize, array+leftSize, rightSize, tmpArray, comp);
    memcpy(array, tmpArray, sizeof(T)*size);
    delete[] tmpArray;
}

template <typename T>
void merge(T *array1, int size1, T *array2, int size2, T *mergeArray, bool comp(T& obj1, T& obj2)){
    int counter1 = 0;
    int counter2 = 0;
    int mergeCounter = 0;
    while(counter1 != size1 && counter2 != size2){
        if(comp(array1[counter1], array2[counter2])){
            mergeArray[mergeCounter++] = array1[counter1++];
        } else {
            mergeArray[mergeCounter++] = array2[counter2++];
        }
    }
    if(counter1 != size1){
        while(counter1 != size1){
            mergeArray[mergeCounter++] = array1[counter1++];
        }
    } else if(counter2 != size2){
        while(counter2 != size2){
            mergeArray[mergeCounter++] = array2[counter2++];
        }
    }
}

int main(){
    int numOfPeople = 0;
    std::cin >> numOfPeople;

    struct Date **dates = new Date*[numOfPeople * 2];
    struct Date birthDate;
    struct Date deathDate;

    int numOfValidDates = 0;
    bool isValid = false;

    for(int i = 0; i < numOfPeople; ++i){
        std::cin >> birthDate.day >> birthDate.month >> birthDate.year;
        birthDate.isBirthDate = true;
        std::cin >> deathDate.day >> deathDate.month >> deathDate.year;
        deathDate.isBirthDate = false;
        isValid = DateUtilities::changeToValidTimeFrame(birthDate, deathDate);
        if(isValid){
            dates[numOfValidDates++] = new Date(birthDate);
            dates[numOfValidDates++] = new Date(deathDate);
        }
    }

    mergeSort<Date*>(dates, numOfValidDates, [](Date *&obj1, Date *&obj2)->bool{
        return obj1->isBirthDate;
    });

    mergeSort<Date*>(dates, numOfValidDates, [](Date *&obj1, Date *&obj2)->bool{
        return ( obj1->year < obj2->year || obj1->year == obj2->year && obj1->month < obj2->month ||
                obj1->year == obj2->year && obj1->month == obj2->month && obj1->day < obj2->day || 
                obj1->year == obj2->year && obj1->month == obj2->month && obj1->day == obj2->day);
    });

    int maxNumberOfLiving = 0;
    int curNumberOfLiving = 0;
    for(int i = 0; i < numOfValidDates; ++i){
        dates[i]->isBirthDate ? ++curNumberOfLiving : --curNumberOfLiving;
        if(maxNumberOfLiving < curNumberOfLiving){
            maxNumberOfLiving = curNumberOfLiving;
        }
    }

    std::cout << maxNumberOfLiving << std::endl;

    for(int i = 0; i < numOfValidDates; ++i){
        delete dates[i];
    }
    delete[] dates;
    
    return 0;
}