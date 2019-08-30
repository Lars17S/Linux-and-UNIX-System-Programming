#include <iostream>
using namespace std;

int main() {
    short n, r, res;
    short Ll, Lr, p, q, i, j;
    short heat = 0;
    cin >> n;
    cin >> r;
    char* arr = new char[n];
    for (int k = 0; k < n; ++k) {
        cin >> arr[k];
    }

    Ll = -1;
    Lr = n;
    res = 0;
    while (Ll + 1 < Lr && heat < n) {
        p = Ll + r;
        q = Lr - r;
        i = p;
        j = q;
        // Calentados lado izquierdo = Ll + 1
        // Calentados lado derecho = n - Lr 
        // If (Ll) + ((n - Lr) + 1) >= n EXIT
        while (arr[i] != '1' && i > p - r + 1)
            --i;
        //if (arr[i] != '1' && i <= j) //i se detiene antes de llegar a una posible intersección, IMPOSIBLE
            //break;
        if(arr[i] == '1') {
            Ll = i + r - 1;
            heat = (Ll + 1) + (n - Lr);
            //cout << "i: " << i << "heat: " << heat << endl;
            ++res;
        }   

        if (heat >= n)
            break;

        while (arr[j] != '1' && j < q + r - 1) 
            ++j;
        if (arr[j] != '1') 
            break;
        else if(arr[j] == '1') {
            Lr = j - r + 1;
            heat = (Ll + 1) + (n - Lr);
            //cout << "j: " << j << "heat: " << heat << endl;
            ++res;
        }
        
    }

    if (res == 0)
        cout << -1 << endl;
    else 
        cout << res << endl;
    return 0;
}
