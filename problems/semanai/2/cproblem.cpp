#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double n, k;
    cin >> n >> k;
    const double red = 2;
    const double green = 5;
    const double blue = 8;
    int red_need = ceil((red * n) / k);
    int green_need = ceil((green * n) / k);
    int blue_need = ceil((blue * n) / k);
    cout << red_need + green_need + blue_need << endl;


    return 0;
}