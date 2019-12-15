#include <iostream>
#include <string>

int main() {
    short N;
    std::string str, chars = "";
    std::cin >> N;
    std::cin.clear(); std::cin.ignore();

    for (short i = 0; i < N; ++i) {
        std::string str_temp;
        std::getline(std::cin, str_temp);
        //std::cout << "str_temp: " << str_temp << std::endl;
        str += str_temp;
    }

    //std::cout << "length: " << str.length() << std::endl;
    for (short j = 15; j < str.length(); j += 16) {
        if (!(str[j] == 'X' && (str[j - 1] == 'O' || str[j - 1] == 'I'))) {
            chars += str[j];  
            //std::cout << "j: " << j << " char: " << str[j] << std::endl;
        }
    }
        
    if (chars.length() == 10 && chars.substr(0, 9).compare("TRIANGULO") == 0) {
        short size = (int)chars[9] - 64;
        for (short i = 0; i < size; ++i)
            std::cout << std::string(i + 1, '*') << std::endl;
    }
    else if (chars.length() == 9 && chars.substr(0, 8).compare("CUADRADO") == 0) {
        short size = (int)chars[8] - 64;
        std::cout << size << std::endl;
        for (short i = 0; i < size; ++i) 
            std::cout << std::string(size, '*') << std::endl;
    }
    else if (chars.length() == 9 && chars.substr(0, 8).compare("PIRAMIDE") == 0) {
        short size = (int)chars[8] - 64;
        std::string piramid = std::string((size * 2) - 1, ' ');
        for (short i = 0, s = (((size * 2) - 1) / 2), t = (((size * 2) - 1) / 2); i < size; ++i, ++s, --t) {
            piramid[s] = '*';
            piramid[t] = '*';
            std::cout << piramid << std::endl;
        }
    }
    
    return 0;
}