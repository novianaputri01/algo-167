#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>

using namespace std;

struct Kendaraan { //bst,struct kendaraan utk menyimpan data
    string nopol, nama, status;
    Kendaraan *left, *right;//pointer kiri dan kanan utk bst

    Kendaraan(string np, string nm) {
        nopol = np;
        nama = nm;
        status = "Di Luar Parkiran"; //status awal kendaraan
        left = right = NULL;
    }
};

struct Undo { //stack, struct utk menyimpan riwayat
    string nopol, aksi;
    Undo *next; //next utk stack

    Undo(string np, string ak) {
        nopol = np;
        aksi = ak;
        next = NULL;
    }
};

struct Antrian { //queue, struct antrian utk kendaraan 
    string nopol;
    Antrian *next; //pointer next utk queue

    Antrian(string np) {
        nopol = np;
        next = NULL;
    }
};

Kendaraan *root = NULL; 

Undo *topUndo = NULL;

Antrian *depan = NULL;//queue depan dan belakang
Antrian *belakang = NULL;

const int MAX = 3; //kapasitas parkiran
int jumlahParkir = 0; //jml kendaraan diparkiran

void garis() {
    cout << "====================================================\n";
}

void header(string judul) {

    system("cls");

    cout << "          SISTEM PARKIR BANDARA GSA\n";
    garis();

    cout << judul << endl;
}

void kembali() {

    cout << "\n";
    garis();
    cout << "Tekan ENTER untuk kembali...";
    cin.get();
}


Kendaraan* tambahNode(Kendaraan* node, string np, string nama) { //fungsi bst tmbh node

    if(node == NULL) { //jika node kosong
        return new Kendaraan(np, nama);
    }

    if(np < node->nopol) {//masuk ke kiri
        node->left = tambahNode(node->left, np, nama);
    }

    else if(np > node->nopol) {//masuk ke kanan
        node->right = tambahNode(node->right, np, nama);
    }

    return node;
}

Kendaraan* cari(Kendaraan* node, string np) { //cari kendaraan

    if(node == NULL || node->nopol == np) {//jika data ditemukan kosong
        return node;
    }

    if(np < node->nopol) { //cari kiri
        return cari(node->left, np);
    }

    return cari(node->right, np); //cari kanan
}

void tampil(Kendaraan* node) { //tampil data inorder bst

    if(node != NULL) {

        tampil(node->left);

        cout << left
             << setw(15) << node->nopol
             << setw(20) << node->nama
             << setw(20) << node->status
             << endl;

        tampil(node->right);
    }
}

Kendaraan* minValue(Kendaraan* node) { //cari nilai terkecil bst

    while(node->left != NULL) {
        node = node->left;
    }

    return node;
}

Kendaraan* hapus(Kendaraan* root, string np) { //hapus node bst

    if(root == NULL) {
        return root;
    }

    if(np < root->nopol) { //cari kiri
        root->left = hapus(root->left, np);
    }

    else if(np > root->nopol) { //cari kanan
        root->right = hapus(root->right, np);
    }

    else { //jika data ditemukan

        if(root->left == NULL) { //jika tdk ada anak kiri

            Kendaraan* temp = root->right;
            delete root;
            return temp;
        }

        else if(root->right == NULL) { //jika tdk punya anak kanan

            Kendaraan* temp = root->left;
            delete root;
            return temp;
        }

        Kendaraan* temp = minValue(root->right); //cari pengganti node

        root->nopol = temp->nopol;
        root->nama = temp->nama;
        root->status = temp->status;

        root->right = hapus(root->right, temp->nopol);
    }

    return root;
}


void pushUndo(string np, string aksi) {

    Undo* baru = new Undo(np, aksi);

    baru->next = topUndo;
    topUndo = baru;
}

void undoAksi() { //undo aksi terakhir

    header("UNDO AKSI");
     cout <<endl;

    if(topUndo == NULL) { //jika stack kosong

        cout << "Tidak ada aksi untuk di-undo\n";
        kembali();
        return;
    }

    Undo* temp = topUndo;
    topUndo = topUndo->next;

    Kendaraan* k = cari(root, temp->nopol);

    if(k != NULL) { //undo kendaraan masuk

        if(temp->aksi == "masuk") {

            k->status = "Di Luar Parkiran";
            jumlahParkir--;

            cout << "Undo : Kendaraan keluar dari parkiran\n";
        }

        else if(temp->aksi == "keluar") { //undo keluar

            k->status = "Di Parkiran";
            jumlahParkir++;

            cout << "Undo : Kendaraan masuk kembali ke parkiran\n";
        }
    }

    delete temp;

    kembali();
}

void enqueue(string np) { //tambah antrian

    Antrian* baru = new Antrian(np);

    if(belakang == NULL) { //jika kosong

        depan = belakang = baru;
    }

    else { //tambah belakang

        belakang->next = baru;
        belakang = baru;
    }
}

string dequeue() { //hapus antrian depan

    if(depan == NULL) {
        return "";
    }

    Antrian* temp = depan;

    string np = temp->nopol;

    depan = depan->next;

    if(depan == NULL) {
        belakang = NULL;
    }

    delete temp;

    return np;
}

void tampilAntrian() { //tampil antrian

    header("ANTRIAN PARKIR");
     cout <<endl;

    if(depan == NULL) {

        cout << "Antrian kosong\n";
    }

    else {

        Antrian* bantu = depan;
        int no = 1;

        garis();

        while(bantu != NULL) {

            cout << no << ". "
                 << bantu->nopol
                 << " menunggu giliran masuk parkiran\n";

            bantu = bantu->next;
            no++;
        }

        garis();
    }

    kembali();
}

void menuTambah() {

    header("TAMBAH KENDARAAN");
     cout <<endl;

    string np, nama;

    cout << "Nomor Polisi : ";
    getline(cin, np);

    cout << "Nama Pemilik : ";
    getline(cin, nama);

    root = tambahNode(root, np, nama);

    cout << "\nData kendaraan berhasil ditambahkan\n";

    kembali();
}

void menuTampil() {

    header("DATA KENDARAAN");
    cout <<endl;

    if(root == NULL) {

        cout << "Data kendaraan kosong\n";
    }

    else {

        cout << left
             << setw(15) << "No Polisi"
             << setw(20) << "Nama"
             << setw(20) << "Status"
             << endl;

        garis();

        tampil(root);

        garis();
    }

    kembali();
}

void menuMasuk() {

    header("KENDARAAN MASUK");
     cout <<endl;

    string np;

    cout << "Nomor Polisi : ";
    getline(cin, np);

    Kendaraan* k = cari(root, np);

    if(k == NULL) {

        cout << "Kendaraan tidak ditemukan\n";
    }

    else if(k->status == "Di Parkiran") {

        cout << "Kendaraan sudah di parkiran\n";
    }

    else {

        if(jumlahParkir < MAX) {

            k->status = "Di Parkiran";
            jumlahParkir++;

            pushUndo(np, "masuk");

            cout << "\nKendaraan berhasil masuk\n";
        }

        else {

            enqueue(np);

            cout << "\nParkiran penuh, kendaraan masuk antrian\n";
        }
    }

    kembali();
}

void menuKeluar() {

    header("KENDARAAN KELUAR");
     cout <<endl;

    string np;

    cout << "Nomor Polisi : ";
    getline(cin, np);

    Kendaraan* k = cari(root, np);

    if(k == NULL) {

        cout << "Kendaraan tidak ditemukan\n";
    }

    else if(k->status == "Di Luar Parkiran") {

        cout << "Kendaraan tidak ada di parkiran\n";
    }

    else {

        k->status = "Di Luar Parkiran";
        jumlahParkir--;

        pushUndo(np, "keluar");

        cout << "\nKendaraan berhasil keluar\n";

        if(depan != NULL) {

            string next = dequeue();

            Kendaraan* baru = cari(root, next);

            if(baru != NULL) {

                baru->status = "Di Parkiran";
                jumlahParkir++;
            }

            cout << "Kendaraan antrian masuk parkiran\n";
        }
    }

    kembali();
}

void menuHapus() {

    header("HAPUS KENDARAAN");
    cout <<endl;

    string np;

    cout << "Nomor Polisi : ";
    getline(cin, np);

    if(cari(root, np) == NULL) {

        cout << "Kendaraan tidak ditemukan\n";
    }

    else {

        root = hapus(root, np);

        cout << "\nData kendaraan berhasil dihapus\n";
    }

    kembali();
}

int main() {

    int pilih;

    do {

        header("MENU UTAMA");
         cout <<endl;

        cout << "1. Tambah Kendaraan\n";
        cout << "2. Tampil Kendaraan\n";
        cout << "3. Kendaraan Masuk\n";
        cout << "4. Kendaraan Keluar\n";
        cout << "5. Hapus Kendaraan\n";
        cout << "6. Undo\n";
        cout << "7. Tampil Antrian\n";
        cout << "8. Keluar\n";

        garis();

        cout << "Pilih Menu : ";
        cin >> pilih;
        cin.ignore();

        switch(pilih) {

            case 1:
                menuTambah();
                break;

            case 2:
                menuTampil();
                break;

            case 3:
                menuMasuk();
                break;

            case 4:
                menuKeluar();
                break;

            case 5:
                menuHapus();
                break;

            case 6:
                undoAksi();
                break;

            case 7:
                tampilAntrian();
                break;

            case 8:

                header("PROGRAM SELESAI");
                 cout <<endl;

                cout << "Terima kasih sudah menggunakan program\n";
                break;

            default:

                cout << "Menu tidak tersedia\n";
                kembali();
        }

    } while(pilih != 8);

    return 0;
}
