#ifndef PAIR
#define PAIR

namespace ft
{
    template <class T1, class T2>
    struct pair
    {
        typedef T1 first_type;
        typedef T2 second_type;

        first_type first;
        second_type second;

        pair()
        {}

        template<class U, class V>
        pair (const pair<U,V>& pr)
        {
            first = pr.first;
            second = pr.second;
        }

        pair(const first_type& a, const second_type& b) :
        first(a),
        second(b)
        {}
    };
}

#endif