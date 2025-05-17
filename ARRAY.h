/////////////////////////////////////////////////////MuhammadAsadMehdi(22i1120)////////////////////////////////
/////////////////////////////////////////////////////MubarizHaroon(22i1104)////////////////////////////////
#include <iostream>

template <typename T>
class ARRAY {
public:
    T* data;
    int count;
   int capacity;


  
    ARRAY() : count(0), capacity(2), data(new T[2]) {}
    ARRAY(const T& value1, const T& value2, const T& value3, const T& value4) : count(4), capacity(4), data(new T[4]) {
        data[0] = value1;
        data[1] = value2;
        data[2] = value3;
        data[3] = value4;
    }
 
    void push_back(const T& value) {
        if (count == capacity) {
            // If the array is full, double its capacity
            capacity *= 2;
            T* newData = new T[capacity];
            for (int i = 0; i < count; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }

        // Add the new element to the end
        data[count] = value;
        ++count;
    }

    // Emplace back function to construct elements in place
    template <typename... Args>
    void emplace_back(Args&&... args) {
        if (count == capacity) {
            // If the vector is full, double its capacity
            capacity *= 2;
            T* newData = new T[capacity];
            for (int i = 0; i < count; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }

        // Construct the new element in place
        new (&data[count]) T(forward<Args>(args)...);
        ++count;
    }

    // Function to access elements by index
    T& operator[](int index) {
        
        return data[index];
    }

    // Function to get the size of the vector
    int get_size() const {
        return count;
    }

    void erase(int index) {
      

        

        // Shift the remaining elements to fill the gap
        for (int i = index; i < count - 1; ++i) 
        {
            data[i] = move(data[i + 1]);
        }

        --count;
    }

};