#include <iostream>
using namespace std;

struct Buku{
	int nomor;
	string namaBuku;
	int harga;
	};

int main(){
	Buku data[6] = {
		{001,"Laskar Pelangi", 85000},
		{002,"Bumi", 105000},
		{003, "Dilan 1990", 95000},
		{004, "Perahu Kertas", 75000},
		{005, "Hujan", 100000},
		{006, "Mariposa", 75000}
		};
		
	int pilihan;
	cout << "===== MENU PENCARIAN BUKU =====" << endl;
	cout << endl;
	cout << "Metode Cari Buku :" <<endl;
	cout << "1. Sequential Search" << endl;
	cout << "2. Binary Search" << endl;
	cout << endl;
	cout << "Pilih Metode Cari Buku : ";
	cin >> pilihan;
	
	int cari;
	cout << "Masukkan nomor buku yang diinginkan : ";
	cin >> cari;
	cout <<endl;
	
	if (pilihan == 1){ //cari dengan sequential
		
		int i = 0;
		bool found = false;
		
		while ((i < 6) && (!found)) {
			if (data[i].nomor == cari){
				found = true;
			}else{
				i++;
			}
		}
		
	if (found){
	cout << "Buku Ditemukan!"<<endl;
	cout << "Judul = " << data[i].namaBuku <<endl;
	cout << "Harga = " << data[i].harga <<endl;
	}else{
	cout << "Maaf, Buku tidak ditemukan" <<endl;};
	}
	
	else if (pilihan == 2){ //binary search
		int awal = 0;
		int akhir = 5;
		int tengah;
		bool found = false;
		
		while (awal <= akhir && !found){
			tengah = (awal + akhir) / 2;
			
			if (data[tengah].nomor == cari)
			found =  true;
			else if (cari < data[tengah].nomor)
			akhir = tengah -1;
			else
			awal = tengah + 1;
			}
	if (found){
	cout << "Buku Ditemukan!"<<endl;
	cout << "Judul = " << data[tengah].namaBuku <<endl;
	cout << "Harga = " << data[tengah].harga <<endl;
	}else{
	cout << "Maaf, Buku tidak ditemukan" <<endl;};
		}
		
	return 0;
	}
	
