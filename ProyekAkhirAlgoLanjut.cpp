#include <iostream> //Digunakan untuk menjalankan perintah input dan output. seperti cin, cout.
#include <conio.h> // Digunakan untuk membuat antarmuka dengan pengguna. seperti getch
#include <stdlib.h> // fungsi system, rand, malloc, exit
#include <string.h> // Digunakan untuk membaca String
#include <time.h> // fungsi time
#include <ctime> // fungsi time

using namespace std;

/* UNTUK SEMUA MOBIL */
typedef struct {
    int nmr_seri;
    char merk[50];
    char nama[50];
    char harga[50];
    int tahun_produksi;
} ISI_MOBIL;


struct MOBIL {
    ISI_MOBIL isi;
    struct MOBIL *next;
};

const string filename = "showroommobil.txt";

typedef struct MOBIL Mobil;
Mobil *database_mobil = NULL;

void judul(){
    cout << "|====================================================================================================================|" << endl;
    cout << "|                                   PROJECT AKHIR ALGORITMA & PEMROGRAMAN LANJUT                                     |" << endl;
    cout << "|                               * PROGRAM DATABASE SHOWROOM MOBIL 'CARROLL AUTOS' *                                  |" << endl;
    cout << "|--------------------------------------------------------------------------------------------------------------------|" << endl;
    cout << "|                                     - QUR'ANA AULIA HARLIANTY (123220183) -                                        |" << endl;
    cout << "|                                    - YOHANES FEBRYAN KANA NYOLA (123220198) -                                      |" << endl;
    cout << "|                                  - ZAIM MUHAMMAD TSAQIF ADINEGARA (1232201200) -                                   |" << endl;
    cout << "|====================================================================================================================|" << endl << endl;
}

// untuk waktu
void waktu() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    cout << "Tanggal: " << ltm->tm_mday << " Bulan: " << 1 + ltm->tm_mon << " Tahun: " << 1900 + ltm->tm_year << endl;
    cout << "Jam  : " << ltm->tm_hour << ":";
    cout << ltm->tm_min << ":";
    cout << ltm->tm_sec << endl;
}

// Jumlah Mobil
int jumlah_mobil() {
    int idx = 0;
    Mobil *x = database_mobil;
    while(x != NULL) {
        idx++;
        x = x->next;//"->" berfungsi untuk memanggil pointer, sama halnya titik di struct
    }
    return idx;
}

// Penambahan mobil baru
void tambah_mobil(ISI_MOBIL isi) {

    Mobil *temp = (Mobil *) malloc(sizeof(Mobil) * 255);
    temp->isi = isi;
    temp->next = NULL;

    if (database_mobil == NULL) {
        database_mobil = temp;
    } else if (database_mobil->next == NULL) {
        database_mobil->next = temp;
    } else {
        Mobil *x = database_mobil;
        while (x->next != NULL) {
            x = x->next;
        }
        x->next = temp;
    }
}

// Tampilkan data mobil
void tampilkan_mobil(ISI_MOBIL isi) {

    cout << "Nomor Seri     : " << isi.nmr_seri << endl;
    cout << "Merk Mobil     : " << isi.merk << endl;
    cout << "Nama Mobil     : " << isi.nama << endl;
    cout << "Harga Mobil    : " << isi.harga << endl;
    cout << "Tahun Produksi : " << isi.tahun_produksi << endl;
    cout << endl;
}

// Daftar mobil (rekursif) = ini itu sama spt perulangan for cuma klo rekursif manggil fungsinya sendiri
void daftar_mobil(ISI_MOBIL isi[], int banyakMobil, int idx) {
    if(idx < banyakMobil) {
        tampilkan_mobil(isi[idx]);
        idx++;
        daftar_mobil(isi, banyakMobil, idx);
    }
}


// Hapus mobil / tidak boleh kosong / null
void hapus_semua_mobil() {
    Mobil *q = database_mobil;
    if(q == NULL) {
        return;
    }

    while (q->next != NULL) {
        Mobil *temp = q->next;
        free(temp);
        q->next = q->next->next;
        q = q->next;
    }
}

// File Handling
// Penulisan ke dalam file
void simpan_database_mobil() {
    FILE *outfile;
    outfile = fopen("showroommobil.txt", "w");
    if (outfile == NULL) {
        cout << "\nError! Silakan coba lagi\n";
    } else {
        Mobil *x = database_mobil;
        while (x != NULL) {
            fprintf(outfile, "%d;%s;%s;%s;%d\n",
                    x->isi.nmr_seri,
                    x->isi.merk,
                    x->isi.nama,
                    x->isi.harga,
                    x->isi.tahun_produksi
            );
            x = x->next;
        }

        fclose(outfile);
    }

}

// Pembacaan file
void buka_database_mobil() {
    FILE *infile;
    infile = fopen("showroommobil.txt", "r");
    if (infile == NULL) {
        cout << "\nError! Silakan coba lagi\n";
    } else {
        ISI_MOBIL mobil;
        hapus_semua_mobil();
        while (
                fscanf(infile, "%d%*c%[^;]%*c%[^;]%*c%[^;]%*c%d%*c",
                       &mobil.nmr_seri,
                       mobil.merk,
                       mobil.nama,
                       mobil.harga,
                       &mobil.tahun_produksi
                ) != EOF) {
            tambah_mobil(mobil);
        }
        fclose(infile);
    }

}
// BERHENTI DISINI //


// Fungsi input mobil
void tampilan_input_mobil() {

    char ulang;

    ISI_MOBIL mobil;

    do {
        system("cls");
        cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "                                          INPUT DATA MOBIL BARU                                                        " << endl;
        cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
        cout << endl;

        cout << "Nomor Seri      : ";
        cin >> mobil.nmr_seri;
        cout << endl;

        cout << "Merk Mobil     : ";
        fflush(stdin);
        cin.getline(mobil.merk, 50);
        cout << endl;

        cout << "Nama Mobil   : ";
        fflush(stdin);
        cin.getline(mobil.nama, 50);
        cout << endl;

        cout << "Harga Mobil  : ";
        fflush(stdin);
        cin.getline(mobil.harga, 50);
        cout << endl;

        cout << "Tahun Produksi   : ";
        cin >> mobil.tahun_produksi;
        cout << endl;

        tambah_mobil(mobil);
        simpan_database_mobil();

        cout << "Input lagi? (y/n): ";
        cin >> ulang;

    } while (ulang != 'n');
}

// Output daftar mobil
void tampilan_daftar_mobil() {

    system("cls");
    cout << "------------------------------------------------------------" << endl;
    cout << "                          DAFTAR MOBIL                      " << endl;
    cout << "------------------------------------------------------------" << endl;

    int banyakmobil = jumlah_mobil();
    ISI_MOBIL temp;

    ISI_MOBIL isi[banyakmobil];
    int idx = 0;
    Mobil *x = database_mobil;
    while(x != NULL) {
        isi[idx++] = x->isi;
        x = x->next;
    }
    
// Sorting bubble sort
    int i, j;
    for (i = 0; i < banyakmobil - 1; i++) {
        for (j = 0; j < banyakmobil - i - 1; j++) {
            if (isi[j].nmr_seri > isi[j+1].nmr_seri) {
                temp = isi[j];
                isi[j] = isi[j + 1];
                isi[j + 1] = temp;
            }
        }
    }

    daftar_mobil(isi, banyakmobil, 0);
    getch();

}

// Tampilan cari mobil
void tampilan_cari_mobil() {
    int kode_cari;

    system("cls");
    cout << "Masukkan kode mobil yang dicari: ";
    cin >> kode_cari;
    cout << endl;

    bool ketemu = false;
    Mobil *x = database_mobil;
    while(x != NULL) {

        if(x->isi.nmr_seri == kode_cari) {
            tampilkan_mobil(x->isi);
            ketemu = true;
        }
        x = x->next;
    }

    if(!ketemu) {
        cout << "Mobil dengan nomor seri \"" << kode_cari << "\" tidak ditemukan" << endl;
    }

    getch();
}


// Print out edit mobil
void tampilan_edit_mobil() {
    int kode_cari;

    system("cls");
    cout << "Masukkan nomor seri mobil yang ingin diedit: ";
    cin >> kode_cari;
    cout << endl;

    bool ketemu = false;
    Mobil *x = database_mobil;
    while(x != NULL) {

        if(x->isi.nmr_seri == kode_cari) {
            cout << "Merk Mobil     : ";
            fflush(stdin);
            cin.getline(x->isi.merk, 50);
            cout << endl;

            cout << "Nama Mobil   : ";
            fflush(stdin);
            cin.getline(x->isi.nama, 50);
            cout << endl;

            cout << "Harga Mobil  : ";
            fflush(stdin);
            cin.getline(x->isi.harga, 50);
            cout << endl;

            cout << "Tahun Produksi   : ";
            cin >> x->isi.tahun_produksi;
            cout << endl;

            ketemu = true;
        }

        x = x->next;
    }
    
    if(!ketemu) {
        cout << "Mobil dengan nomor seri \"" << kode_cari << "\" tidak ditemukan" << endl;
    } else {
        simpan_database_mobil();
        cout << "Data tersimpan!";
    }
    getch();

}


// Print out hapus mobil
void tampilan_hapus_mobil() {
    int kode_cari;

    system("cls");
    cout << "Masukkan nomor seri yang ingin dihapus: ";
    cin >> kode_cari;
    cout << endl;

    bool ketemu = false;
    Mobil *q = database_mobil;
    while (q->next != NULL) {
        if (q->isi.nmr_seri == kode_cari) {
            Mobil *temp = NULL;
                temp = q->next;
                free(temp);
                q->next = q->next->next;
            ketemu = true;
            break;
        } else if (q->next->isi.nmr_seri == kode_cari) {
            q->next = NULL;
            ketemu = true;
            break;
        }
        q = q->next;
    }
    if(!ketemu) {
            cout << "Mobil dengan nomor seri \"" << kode_cari << "\" tidak ditemukan" << endl;
    } else {
        simpan_database_mobil();
        cout << "Data berhasil dihapus!";
    }
    getch();
}
// STOP DI SINI //


// Fungsi login
void login() {
    string pass, user;
    bool ulangi_login;
    do {
        judul();
        cout << "====================================================================================================================" << endl;
        cout << "                                   Selamat Datang di Showroom Mobil 'CARROLL AUTOS'                                 " << endl;
        cout << "====================================================================================================================" << endl;
        waktu();
        cout << endl;
        cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "                                              Anda Login Sebagai Admin                                              " << endl;
        cout << "--------------------------------------------------------------------------------------------------------------------" << endl << endl;
        cout << "Username\t: ";
        cin >> user;
        cout << "Password\t: ";
        cin >> pass;

        if(((user == "nana" || user == "Nana" || user == "NANA" ) &&  ( pass == "123220183")) || ((user == "zaim" || user == "Zaim" || user == "ZAIM" ) &&  ( pass == "123220200")) || ((user == "ryan" || user == "Ryan" || user == "RYAN" ) &&  ( pass == "123220198"))){
            cout << "login berhasil!" << endl;
            system("pause");
            system("cls");
            ulangi_login = false;

        } else {
            cout << "login gagal!" << endl;
            ulangi_login = true;
            system("pause");
            system("cls");
        }
    } while (ulangi_login);
}


// Main program
int main() {

    login();
    buka_database_mobil();
    int pilih;

    do {
        system("cls");
        cout << "---------------------------------------------------------------------------------------------------------------" << endl;
        cout << "                                           DATABASE SHOWROOM MOBIL                                             " << endl;
        cout << "---------------------------------------------------------------------------------------------------------------" << endl;
        cout << endl;

        cout << "1. Input Data Mobil " << endl;
        cout << "2. Lihat Daftar Mobil" << endl;
        cout << "3. Cari Data Mobil" << endl;
        cout << "4. Edit Data Mobil" << endl;
        cout << "5. Hapus Data Mobil" << endl;
        cout << "6. Keluar" << endl;
        cout << "Silahkan Pilih Menu 1-6 ! = ";
        cin >> pilih;
        cout << endl;


        switch (pilih) {
            case 1: {
                tampilan_input_mobil();
                break;
            }

            case 2: {
                tampilan_daftar_mobil();
                break;
            }

            case 3: {
                tampilan_cari_mobil();
                break;
            }

            case 4: {
                tampilan_edit_mobil();
                break;
            }

            case 5: {
                tampilan_hapus_mobil();
                break;
            }

            case 6: {
                system("exit");
                break;
            }

            default: {
                cout << "Pilihan Anda tidak tersedia!";
                break;
            }
        }
    } while (pilih != 6);

    return 0;
}