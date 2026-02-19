#include <iostream>
using namespace std;

int main()
{
	int n; // mendeklarasikan n
	cout << "Masukkan jumlah yang kamu mau: "; //masukkan jumlah angka yang mau dihitung
	cin >> n;
	
	int arr[100]; //array 
	int *ptr = arr; //pointer
	
	for(int i = 0;i < n; i++) //input dgn pointer
	{
		cout << "Masukkan angka ke-" << i+1 << "          : ";
		cin >> *(ptr + i);
		cout <<endl;
	}
	
	cout << "Isi array             :"; // melihat isi array
	for(int i = 0; i < n; i++)
	{
		cout << *(ptr + i) << " ";
	}
	
	cout <<endl;
	
	int max = *ptr;
	int min = *ptr;
	int jumlah = 0;
	
	for(int i = 0; i < n; i++)
	{
		if(*(ptr + i) > max) //cari max
		max = *(ptr + i);
		
		if(*(ptr + i) < min) //cari min
		min = *(ptr + i);
		
		jumlah +=  *(ptr + i); //jumlah
		}
		
	 float rata = (float)jumlah / n; //rata - rata
	 
	 cout << "Nilai maksimum adalah :"<< max <<endl;
	 cout << "Nilai minimum adalah  :"<< min <<endl;
	 cout << "Jumlahnya yaitu       :"<< jumlah <<endl;
	 cout << "Rata - rata           :"<< rata <<endl;
	
	}
