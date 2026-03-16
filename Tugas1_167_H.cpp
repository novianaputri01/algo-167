#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

struct produk{
	char nama[60];
	char kategori[30];
	double harga;
	int stok;
	float rating;
};

produk arr[100];
int n = 0;

void bacaFile(){
	FILE *pf = fopen("shopease_db.txt","r");
	
	if(pf == NULL){
		return;
	}
	
	while(fscanf(pf, " %[^|]|%[^|]|%lf|%d|%f\n",
		arr[n].nama,
		arr[n].kategori,
		&arr[n].harga,
		&arr[n].stok,
		&arr[n].rating) != EOF){
			
			n++;
		}
		fclose(pf);
	}

void simpanFile(){
	
	FILE *pf = fopen("shopease_db.txt","w");
	
	for(int i = 0; i < n; i++){
		fprintf(pf,"%s|%s|%.0lf|%d|%.1f\n",
		arr[i].nama,
		arr[i].kategori,
		arr[i].harga,
		arr[i].stok,
		arr[i].rating);
		}
	fclose(pf);
	}
	
void tambahProduk(){
	cout << "\n======== TAMBAH PRODUK ========\n"<<endl;
	cin.ignore();
	cout << "Nama Produk	: ";
	cin.getline(arr[n].nama,60);
	cout << "Kategori	: ";
	cin.getline(arr[n].kategori,30);
	cout << "Harga		: ";
	cin >> arr[n].harga;
	cout << "Stok		: ";
	cin >> arr[n].stok;
	cout << "Rating		: ";
	cin >> arr[n].rating;
	cout <<endl;
	
	n++;
	
	simpanFile();
	
	cout << "Selamat! Produk Yang Kamu Inginkan Berhasil Ditambahkan."<<endl; 
	}
	
void bubbleSortNama(){
	
	produk temp;
	for(int i = 0; i < n-1; i++){
		for(int j = 0; j < n-i-1; j++){
			if(strcmp(arr[j].nama, arr[j + 1].nama) > 0){
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				}
			
			}
		
		}
	
	}

void quickSortRating( int low, int high){
	int i = low;
	int j = high;
	float pivot = arr[(low+high)/2].rating;
	
	while(i <= j){
		while(arr[i].rating > pivot){
			i++;
			}
		
		while(arr[j].rating < pivot){
			j--;
			}
		if(i <= j){
			produk temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			
			i++;
			j--;
			}
		
		}
	if(low < j) quickSortRating(low, j);
	if(i < high) quickSortRating(i, high);
}

void tampilProduk(){
	
	int pilih;
	
	cout  << "\n======== TAMPILAN PRODUK ========\n"<<endl;
	cout << "\nMau Sorting Pakai Apa?\n"<<endl;
	cout << "1. Pakai Nama (Bubble Sort)\n";
	cout << "2. Pakai Rating (Quick Sort)\n";
	cout <<endl;
	cout << "Pilihanmu : ";
	cin >> pilih;
	
	if(pilih == 1) bubbleSortNama();
	if(pilih == 2) quickSortRating(0, n-1);
	
	cout <<"\nDAFTAR PRODUK\n";
	
	printf("-----------------------------------------------------------------\n");
	printf("%-20s %-15s %-10s %-10s %-10s\n",
	"Nama", "Kategori", "Harga", "Stok", "Rating");
	printf("-----------------------------------------------------------------\n");
	
	for(int i = 0; i < n; i++){
		printf ("%-20s %-15s %-10.0lf %-10d %-10.1f\n",
		arr[i].nama,
		arr[i].kategori,
		arr[i].harga,
		arr[i].stok,
		arr[i].rating);
		
		}
	}

void cariProduk(){
	char cari[60];
	int ditemukan = -1;
	
	cout  << "\n======== CARI PRODUK ========\n"<<endl;
	cout << "Ayo Masukkan Nama Produk : ";
	cin.ignore();
	cin.getline(cari,60);
	
	for(int i = 0; i < n; i++){
		if(strcmp(arr[i].nama, cari) == 0){
			ditemukan = i;
			break;
			}
		}
	
	if(ditemukan != -1){
		cout << "\nYES! Produk Ditemukan.\n"<<endl;
		cout << "Nama		: "<< arr[ditemukan].nama <<endl;
		cout << "Kategori	: "<< arr[ditemukan].kategori <<endl;
		cout << "Harga		: "<< arr[ditemukan].harga<<endl;
		cout << "Stok		: "<< arr[ditemukan].stok <<endl;
		cout << "Rating		: "<< arr[ditemukan].rating <<endl;
		
		}
		else{
			cout << "Yahh...Produk Yang Kamu Mau Belum Ada\n";
			
		}
	}
	
int main(){
	
	
	int menu;
	bacaFile();
	
	do{
		
		cout <<"\n======== ShopEase MENU ========\n"<<endl;
		cout << "1. Tambah Produk\n";
		cout << "2. Tampilkan Produk\n";
		cout << "3. Cari Produk\n";
		cout << "4. Keluar\n"<<endl;
		cout << "Pilihanmu : ";
		cin >> menu;
		
		
		switch(menu){
			case 1:
				tambahProduk();
				break;
			case 2:
				tampilProduk();
				break;
			case 3:
				cariProduk();
				break;
			case 4:
				simpanFile();
				cout << "Terima Kasih Telah Menggunakan ShopEase Kami\n";
		
			}
		
		}while(menu !=4);
}
