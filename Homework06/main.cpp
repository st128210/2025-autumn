#include <iostream>

template <class T, size_t size>
class Array
{
    T array[size];
public:
    Array() {}

    Array(T* b)
    {
        for (size_t i = 0; i < size; i++)
            array[i] = b[i];
    }

    void show()
    {
        for (size_t i = 0; i < size; i++)
            std::cout << array[i] << " ";
        std::cout << std::endl;
    }

    T minimum()
    {
        T min_val = array[0];
        for (size_t i = 1; i < size; i++)
            if (array[i] < min_val)
                min_val = array[i];
        return min_val;
    }

    T& operator[](size_t index)
    {
        return array[index];
    }

    const T& operator[](size_t index) const
    {
        return array[index];
    }
};

int main()
{
    int int_data[] = { 5, 3, 8, 1, 9 };
    Array<int, 5> int_array(int_data);

    std::cout << "Integer array: ";
    int_array.show();
    std::cout << "Minimum: " << int_array.minimum() << std::endl;

    double double_data[] = { 3.14, 2.71, 1.41, 0.99 };
    Array<double, 4> double_array(double_data);

    std::cout << "Double array: ";
    double_array.show();
    std::cout << "Minimum: " << double_array.minimum() << std::endl;

    return 0;
}