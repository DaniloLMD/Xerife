#include <iostream>
#include <vector>

using namespace std;

template <typename T>
int particao(vector<T>& v, int left, int right){
    int pivot = v[right];
    int index_do_ultimo_menor = left-1;

    for(int i = left; i < right; i++){
        if(v[i] < pivot){
            index_do_ultimo_menor++;
            swap(v[i], v[index_do_ultimo_menor]);
        }
    }

    swap(v[index_do_ultimo_menor+1], v[right]);

    return index_do_ultimo_menor+1;
}

template <typename T>
void QuickSort(vector<T>& v, int left, int right){
    if(left < right){
        int pivot = particao(v, left, right);

        QuickSort(v, left, pivot - 1);
        QuickSort(v, pivot + 1, right);
    }
}

int main(){

    vector<double> v = {1 , 8, 6 , 4, 3, 0, 2, 9, 5, 7};

    QuickSort(v, 0, v.size() - 1);

    cout << "v = ";
    for(int h: v) cout << h << " ";
    cout << endl;

    return 0;
}