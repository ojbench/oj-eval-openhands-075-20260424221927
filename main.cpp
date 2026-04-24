
#include <iostream>
#include "str.hpp"
#include <vector>
#include <cassert>

int main() {
    str s1;
    assert(s1.len() == 0);

    str s2('a');
    assert(s2.len() == 1);
    assert(s2[0] == 'a');

    str s3("hello");
    assert(s3.len() == 5);
    assert(s3[0] == 'h');

    const char* p = "world";
    str s_p(std::move(p)); 
    str s_p2("world"); 
    

    str s4 = s3;
    assert(s4.len() == 5);
    assert(s4[0] == 'h');

    s1 = "world";
    assert(s1.len() == 5);
    assert(s1[0] == 'w');

    std::vector<str> v = {str("1"), str("2"), str("3")};
    str s5(", ");
    str s6 = s5.join(v);
    // s6 should be "1, 2, 3"
    assert(s6.len() == 7);
    
    str s7 = str("12345").slice(0, 2);
    assert(s7.len() == 2);
    assert(s7[0] == '1');
    assert(s7[1] == '2');

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
