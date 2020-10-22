#include "number.hpp"

number::number(int a) {
	sign = (a >= 0) ? true : false;
        a = abs(a);

        if (a == 0) {
	    numerator.push_back(0);
	}

        while(a > 0) {
            numerator.push_back(a % 10);
            a /= 10;
        }

        std::reverse(numerator.begin(), numerator.end());
        denominator.push_back(1);
}

number::number() {
    numerator.push_back(0);
    denominator.push_back(1);
}

number number::operator +( const number &obj) const {
    number result;
    result.denominator = multiply2v(denominator, obj.denominator);
    std::vector<int> v2 = multiply2v(denominator, obj.numerator);
    std::vector<int> v1 = multiply2v(numerator, obj.denominator);

    if (sign == obj.sign) {
	result.sign = sign;
	result.numerator = sum2v(v1, v2);
    } else {
	result.numerator = diff2v(v1, v2);
	
	if (!sign) {
	    result.sign = (isSmaller(v1, v2)) ?  true : false;
	} else {
	    result.sign = (isSmaller(v2,v1)) ? true : false;
	}
    }

    std::vector<int> g = gcd(result.denominator, result.numerator);
    if (g.size() > 4) {
	result.denominator = divide2v(result.denominator, g);
	result.numerator = divide2v(result.numerator, g);
    }

    return result;
}

number number::operator -(const number &obj) const {
    number objj = obj;
    objj.sign = !obj.sign;
    return (operator+(objj));
}

number number::operator -() const {
    number result;
    result.numerator = numerator;
    result.denominator = denominator;
    result.sign = !sign;

    return result;
}

number number::operator * (const number &obj) const {
    number result;
    
    result.denominator = multiply2v(denominator, obj.denominator);
    result.numerator = multiply2v(numerator, obj.numerator);
    result.sign = ((sign == obj.sign) || (result.numerator.size() == 1 && result.numerator[0] == 0)) ? true : false;
   
    std::vector<int> g = gcd(result.denominator, result.numerator);
    if (g.size() > 4) {
	result.denominator = divide2v(result.denominator, g);
	result.numerator = divide2v(result.numerator, g);
    }

    return result;
}

number number::operator / (const number &obj) const {
    number result;

    result.denominator = multiply2v(denominator, obj.numerator);
    result.numerator = multiply2v(numerator, obj.denominator);
    result.sign = ((sign == obj.sign) || (result.numerator.size() == 1 && result.numerator[0] == 0)) ? true : false;
    
    std::vector<int> g = gcd(result.denominator, result.numerator);
    if (g.size() > 4) {
	result.denominator = divide2v(result.denominator, g);
	result.numerator = divide2v(result.numerator, g);
    }

    return result;
}

bool number::operator == ( number obj) const {
    std::vector<int> v1 = multiply2v(numerator, obj.denominator);
    std::vector<int> v2 = multiply2v(denominator, obj.numerator);
    std::vector<int> r = diff2v(v1, v2);
    
    return (r.size() == 1 && r[0] == 0) ? true : false;
}

bool number::operator != ( number obj) const  {
    return !(operator == (obj)); 
}

bool number::operator < ( number obj) const {
    if (sign && !obj.sign)
	return false;
    if (!sign && obj.sign)
	return true;

    std::vector<int> v1 = multiply2v(numerator, obj.denominator);
    std::vector<int> v2 = multiply2v(denominator, obj.numerator);

    if (sign && obj.sign) {
	if (isSmaller(v1, v2) && (operator != (obj)))
	    return true;
	return false;
    }
    if (isSmaller(v2, v1) && (operator != (obj)))
	return true;

    return false;
    
}

bool number::operator > ( number obj) const {
    return (!(operator < (obj)) && (operator != (obj)));
}

bool number::operator <= ( number obj) const {
    return ((operator < (obj)) || (operator == (obj)));
}

bool number::operator >= ( number obj) const {
    return ((operator > (obj)) || (operator == (obj)));
}

number number::power(number &x, int y) const {
    number tmp;
    if (y == 0)
	return (number (1));

    tmp = power(x, y/2);

    if (y % 2 == 0)
	return (tmp * tmp);
    else
    {
	if (y > 0)
	    return (x * tmp * tmp);
	else
	    return ((tmp * tmp) / x);
    }
}

number number::power(int p) const {
    number x;
    x.numerator = numerator;
    x.denominator = denominator;
    x.sign = sign;
    number result(1);

    if (x == 1 || x == -1) {
	result = 1;

    } else {
	result = power(x, abs(p));
      }

    result.sign = (p % 2 == 0) ? true : sign;
    if (p < 0)
	result.numerator.swap(result.denominator);
    
    return result;
}

number number::sqrt(int p) const {
    number n;
    n.numerator = numerator;
    n.denominator = denominator;
    n.sign = true; 

    if(n == 0) {
	return (number (0));
    }
    
    unsigned digits = (numerator.size() - denominator.size()) + 1;
    if (digits % 2 != 0)
	digits += 1;

    digits /= 2;
    number min_boundary = (number (10)).power(digits - 1);
    number step = min_boundary;
    number x (1);
    number y(1);

    if (n <= 1) {
	 y = y / (10 * (abs(p) + 1));
	 x = x + 1;
    } else {
	 x = min_boundary;
	
	while ((x*x) < n) {
    	     x = (x + step);    
	}
    }
       
    number two(2);
    number e(1);
    e.denominator.clear();
    e.denominator.push_back(1);
    e.denominator.push_back(0);
    
    for(int i = 0; i < abs(p); i++) {
	e.denominator.push_back(0);
    }

    while((x - y) > e) {
	y = n/x;
	x = (x + y) / two;
    }

    return x;

}

std::vector<int> multiply2v(const std::vector<int> &v1, const std::vector<int> &v2) {
    
    unsigned len1 = v1.size();
    unsigned len2 = v2.size();
    std::vector<int> result (len1 + len2, 0);

    int pos1 = 0;
    int pos2 = 0;

    for(int i = len1 - 1; i >= 0; i--) {
        int carry = 0;
        int n1 = v1[i];
        pos2 = 0;

        for(int j = len2 - 1; j >= 0; j--) {
            int n2 = v2[j];
            int sum = n1 * n2 + result[pos1 + pos2] + carry;
            carry = sum / 10;
            result[pos1 + pos2] = sum % 10;
            pos2++;
        }

        if (carry > 0) {
            result[pos1 + pos2] += carry;
        }

        pos1++;
    }

    int i = result.size() - 1;
    while(i >= 0 && result[i] == 0) {
        i--;
    }
    if (i == -1) {
        std::vector<int> r (1, 0);
        return r;
    }

    result.resize(i + 1);
    std::reverse(result.begin(), result.end());

    return result;
}


std::vector<int> diff2v( std::vector<int> v1,  std::vector<int> v2) {
    unsigned length = std::max(v1.size(), v2.size());
    int diff;
    std::vector<int> result;
    if (isSmaller(v1,v2))
	v1.swap(v2);

    while (v1.size() < length)
	v1.insert(v1.begin(), 0);

    while (v2.size() < length)
	v2.insert(v2.begin(), 0);

    for (int i = length - 1; i >= 0; i--) {
	diff = v1[i] - v2[i];
	if (diff >= 0)
	    result.push_back(diff);
	else {
	    int j = i - 1;
	    while (j >= 0) {
		v1[j] = (v1[j] - 1) % 10;
		if (v1[j] != 9)
		    break;
		else {
		    j--;
		}
	    }
	    result.push_back(diff + 10);
	}
    }

    int i = result.size() - 1;
    while( i >= 0 && result[i] == 0)
	i--;

    if ( i == -1 ) {
	std::vector<int> r (1, 0);
	return r;
    }
    
    result.resize( i + 1 );
    std::reverse(result.begin(), result.end());
    return result;
}

std::vector<int> sum2v( std::vector<int> v1,  std::vector<int> v2) {
    unsigned length = std::max(v1.size(), v2.size());
    int carry = 0;
    int sum = 0;
    std::vector<int> result;

    while (v1.size() < length)
	v1.insert(v1.begin(), 0);

    while (v2.size() < length)
	v2.insert(v2.begin(), 0);

    for(int i = length - 1; i >= 0; i--) {
	sum = v1[i] + v2[i] + carry;
	carry = sum / 10;
	result.push_back(sum % 10);
    }

    if (carry) {
	result.push_back(carry);
    }

    int i = result.size() - 1;
    while (i >= 0 && result[i] == 0)
	i--;
    
    if ( i == -1) {
	std::vector<int> r (1, 0);
	return r;
    }

    result.resize(i + 1);
    std::reverse(result.begin(), result.end());
    return result;
}

bool isSmaller( std::vector<int> &v1, std::vector<int> &v2) {
    if (v1.size() < v2.size())
	return true;
    if(v2.size() < v1.size())
	return false;
   
    for(unsigned i = 0; i < v1.size(); i++) {
	if (v1[i] < v2[i])
	    return true;
	if (v2[i] < v1[i])
	    return false;
     }

    return true;
}

std::vector<int> gcd(std::vector<int> u, std::vector<int> v) {
    if (u == v)
	return u;
    if (u.size() == 1 && u[0] == 0 )
	return v;
    if (v.size() == 1 && v[0] == 0 )
	return u;

    if (u.back() % 2 == 0) {
	if (v.back() % 2 != 0) {
	    return gcd(dividev(u, 2), v);
	} else {
	    std::vector<int> two {2};
	    return multiply2v(gcd(dividev(u, 2), dividev(v,2)), two);
	}
    }

    if (v.back() % 2 == 0) {
	return gcd(u, dividev(v, 2));
    }

    if (!isSmaller(u, v)) {
	return gcd(dividev(diff2v(u, v), 2), v);
    }

    return gcd(dividev(diff2v(v, u), 2), u);
}


std::vector<int> dividev(std::vector<int> v, int divisor) {
    std::vector<int> result;
    if (v.size() == 1) {
	result.push_back(v[0] / divisor);
	return result;
    }
    unsigned index = 0;
    int tmp = v[0];

    while (tmp < divisor) {
	index++;
	if (index <= v.size() - 1)
	    tmp = (tmp * 10) + v[index]; 
    }

    while(v.size() > index) {
	result.push_back(tmp / divisor);
	index++;
	if(index <= v.size() - 1)
	    tmp = ((tmp % divisor) * 10) + v[index];
    }

    if (result.size() == 0)
	result.push_back(0);
	
    return result;
}

std::vector<int> divide2v(std::vector<int> u, std::vector<int> v) {
    if (v.size() == 1) {
	return (dividev(u, v[0]));
    }
    
    std::vector<int> result;
    std::vector<int> tmp (u.begin(), u.begin() + v.size());
    unsigned index_out = v.size();
    unsigned range = (u.size() - v.size()) + 1;
    int times = 0;
    
    for (unsigned i = 0; i < range; i++) {
	if (isSmaller(v, tmp)) {
		while(isSmaller(v, tmp)) {
		tmp = diff2v(tmp, v);
		times++;
	    }
	} else {
	    if (tmp[0] == 0) { tmp.erase(tmp.begin()); }
	}

	result.push_back(times);
	times = 0;
	if (!isSmaller(v, tmp)) {
	    if (index_out < u.size())
		tmp.push_back(u[index_out++]);
	}
    }

    if (result[0] == 0)
	result.erase(result.begin());

    return result;   
}
