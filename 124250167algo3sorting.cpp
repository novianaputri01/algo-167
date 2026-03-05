#include <iostream>
using namespace std;

void tampilArray(string arr[], int n){ //fungsi untuk menampilkan isi array nama
	for(int i = 0; i < n; i++){ //perulangan mencetak semua elemen array
		cout << arr[i] <<endl; //tampil nama mhs
		}
	}
	
	void bubbleSort(string arr[], int n){ //mengurutkan sec. ascending
		for(int i = 0; i < n - 1; i++){ //perulangan luar utk jumlah sorting
			
			for(int j = 0; j < n - i - 1; j++){ //perulangan dalam utk membandingkan elemen
				
				if(arr[j] > arr[j + 1]){ //jika elemen sekarang lebih besar
					
					string temp = arr[j]; //tukar posisi dua elemen
					arr[j] = arr[j + 1]; //tukar posisi
					arr[j + 1] = temp; //tukar posisi
					}
				}
			}
		}
	
	int partition(string arr[],int low, int high){ //quick sort descending
		string pivot = arr[high]; //pivot diambil dr elemen akhir
		
		int i = low - 1; //i utk elemen lebih besar dr pivot
		
		for(int j = low; j < high; j++){ //perulangan utk membandingkan dgn pivot
			
			if(arr[j] > pivot){ //jika elemen lbh besar dr pivot //descencing
				i++;
				string temp = arr[i]; //tukar posisi
				arr[i] = arr[j]; //tukar posisi
				arr[j] = temp; //tukar posisi
				} 
			}
			string temp = arr[i + 1]; //tukar pivot ke posisi yg seharusny
			arr[i + 1] = arr[high];
			arr[high] = temp;
			
			return i + 1; //mengembalikan posisi pivot
		}
		
	void quickSort(string arr[], int low, int high){ //mengurtkan descending
		if(low < high){ //jika array msh bs dibagi
			int pi = partition(arr, low, high); //indeks pivot
			quickSort(arr, low, pi - 1); //rekursi bagian kiri pivot
			quickSort(arr, pi + 1, high); //rekursi kanan pivot
			}
		}
		
int main(){
	int n;
	
	cout << "========== MENU DAFTAR NAMA MAHASISWA ==========" << endl;
	cout <<endl;
	cout << "Masukkan jumlah mahasiswa yang kamu inginkan: ";//input jumlah mhs
	cin >> n;
	cout <<endl;
	
	string nama[n]; //input nama mhs dan deklarasi array
	for(int i = 0; i < n; i++){
		cout << "Masukkan nama mahasiswa ke-" << i+1 << ": ";
		cin >> nama[i];
		}
		
		string namaAsc[n]; //menyalin array untuk sorting lagi
		string namaDesc[n]; //menyalin array untuk sorting lagi
		
		for(int i = 0; i < n; i++){
			namaAsc[i] = nama[i];
			namaDesc[i] = nama[i];
			}
			
	bubbleSort(namaAsc, n); //sorting asc dengan bubblesort
	
	cout <<endl;
	cout << "Urutan Nama Secara Ascending (Bubble Sort): "<<endl;
	cout <<endl;
	tampilArray(namaAsc, n);
	
	quickSort(namaDesc, 0, n-1); //sorting desc dengan quick sort
	
	cout <<endl;
	cout << "Urutan Nama Secara Descending (Quick Sort): "<<endl;
	cout <<endl;
	tampilArray(namaDesc, n);
	
	
		
	return 0;
}
