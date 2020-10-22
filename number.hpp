/* Here comes the class and toplevel function declarations (if needed). */
#include <vector>
#include <algorithm>
#include <stdlib.h>

class number {
 
    std::vector<int> numerator;
    std::vector<int> denominator;
    bool sign;
    
    public:
        number(int a);
        number ();
	number operator +( const number &obj ) const;
	number operator -( const number &obj ) const;
	number operator -() const;
	number operator * (const number &obj) const;
	number operator / (const  number &obj) const;

	bool operator == ( number obj) const ;
	bool operator != ( number obj) const;
	bool operator > ( number obj) const;
	bool operator < ( number obj) const;
	bool operator >= ( number obj) const;
	bool operator <= ( number obj) const;

	number power(number &n, int a) const;
	number power (int a) const;
        number sqrt (int a) const;

};

std::vector<int> gcd(std::vector<int> a, std::vector<int> b);
std::vector<int> dividev(std::vector<int> a, int divisor);
std::vector<int> multiply2v(const std::vector<int> &a, const std::vector<int> &b);
std::vector<int> sum2v(std::vector<int> a, std::vector<int> b);
std::vector<int> diff2v(std::vector<int> a, std::vector<int> b);
std::vector<int> divide2v(std::vector<int> a, std::vector<int>b);
bool isSmaller(std::vector<int> &a, std::vector<int> &b);

