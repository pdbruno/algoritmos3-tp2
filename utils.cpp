using namespace std;

template<class T>
void print(T &printable) {
    cout << printable << endl;
}

template<class T>
void print_vector(vector<T> &vector) {
    for (T i: vector)
        std::cout << i << ' ';
    std::cout << "!" << endl;
}