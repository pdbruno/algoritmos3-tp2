#include <vector>
#include <queue>
#include <deque>
using namespace std;
typedef int Vertice;
typedef int Peso;
typedef vector<vector<int>> Grafo;
#define MAX_INT 2147483647


template<typename T, typename Container=std::deque<T>>
class iterable_queue : public std::deque<T,Container>
{
public:
    typedef typename Container::iterator iterator;
    typedef typename Container::const_iterator const_iterator;

    iterator begin() { return this->c.begin(); }
    iterator end() { return this->c.end(); }
    const_iterator begin() const { return this->c.begin(); }
    const_iterator end() const { return this->c.end(); }
};
