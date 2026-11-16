#include <iostream>
#include <string>
using namespace std;

struct pemesanan { //custom data type untuk pemesanan atau dideclare sebagai ps 
    string namaPemesan; 
    int ID;
    int IDruang;
    string namaruangan;
    int kapasitasruangan;
    int jumlahAnggota;
    int durasi;
    string prioritas;
    bool statuskapasitas;
};

void datapemesanan(pemesanan ps[], int& jumlah, const int maks) { //menggunakan tipe data void karna tidak mengembalikan nilai saat di call di fungsi main 
   //int& jumlah (pass by reference) digunakan untuk mengubah nilai jumlah di fungsi main, sehingga setiap kali pemesanan baru ditambahkan, jumlah akan diperbarui secara langsung.
   
   
    if (jumlah >= maks) { //berfungsi saat banyak data yang disimpan melebihi kapasitas atau overload. 
        cout << "Tidak dapat menerima pesanan, karna pesanan sudah melebihi kapasitas maksimum.\n";
        return;
    }

    const string namaRuang[] = {
        "Ruang Diskusi 1", "Ruang Diskusi 2", "Ruang Diskusi 3",
        "Ruang Creative 1", "Aula Utama", "Ruang Creative 2", "Ruang Rapat"
    };
    const int kapasitas[] = {10, 20, 25, 35, 100, 40, 30};
    int pilihanRuang;

    cout << "Nama Pemesan: ";
    cin >> ps[jumlah].namaPemesan;
    cout << "Masukkan ID pemesanan: ";
    cin >> ps[jumlah].ID;

    cout << "Pilih ruangan (1-7):\n";
    for (int i = 0; i < 7; ++i) {
        cout << i + 1 << ". " << namaRuang[i] << " (kapasitas " << kapasitas[i] << ")\n";
    }
    cin >> pilihanRuang;
    if (pilihanRuang < 1 || pilihanRuang > 7) {
        cout << "Pilihan ruangan tidak valid.\n";
        return;
    }

    ps[jumlah].IDruang = pilihanRuang;
    ps[jumlah].namaruangan = namaRuang[pilihanRuang - 1];
    ps[jumlah].kapasitasruangan = kapasitas[pilihanRuang - 1];
    cout << "Jumlah anggota: ";
    cin >> ps[jumlah].jumlahAnggota;

    ps[jumlah].statuskapasitas = ps[jumlah].jumlahAnggota <= ps[jumlah].kapasitasruangan;
    if (!ps[jumlah].statuskapasitas) {
        cerr << "\n[ERROR] Pesanan ditolak karena jumlah anggota (" << ps[jumlah].jumlahAnggota << ") melebihi kapasitas ruangan ("  << ps[jumlah].kapasitasruangan << ")!\nSilahkan coba lagi.\n\n";
        return;
    }
    cout << "Durasi pemesanan (menit): ";
    cin >> ps[jumlah].durasi;
    
    cin.ignore();

    cout << "Prioritas/kegunaan: ";
    getline (cin, ps[jumlah].prioritas);

    ps[jumlah].statuskapasitas = ps[jumlah].jumlahAnggota <= ps[jumlah].kapasitasruangan;
    if (ps[jumlah].statuskapasitas) {
        cout << "Pesanan diterima.\n";
    } else {
        cout << "Pesanan ditolak di karenakan jumlah anggota melebihi kapasitas ruangan.\n";
    }
    ++jumlah;
}

void cariPemesanan(const pemesanan ps[], int jumlahPemesanan) {
    int idCari;
    bool ditemukan = false;

    cout << "Masukkan ID pemesanan: ";
    if (!(cin >> idCari)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cerr << "Input ID harus berupa angka!\n\n";
        return;
    }

    for (int i = 0; i < jumlahPemesanan; ++i) {
        if (ps[i].ID == idCari) {
            cout << "\nPemesanan ditemukan:\n"
                 << "- Nama Pemesan : " << ps[i].namaPemesan << "\n"
                 << "- Ruangan      : " << ps[i].namaruangan << "\n"
                 << "- Durasi       : " << ps[i].durasi << " menit\n\n";
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << "Pemesanan dengan ID " << idCari << " tidak ditemukan.\n\n";
    }
}

void tampilkanDaftar(const pemesanan ps[], int jumlahPemesanan) {
    // tampil daftar pemesanan
    for (int i = 0; i < jumlahPemesanan; ++i) {
        cout << "Data ke-" << i + 1 << "\n"
             << "- ID           : " << ps[i].ID << "\n"
             << "- Nama pemesan : " << ps[i].namaPemesan << "\n"
             << "- Ruangan      : " << ps[i].namaruangan << "\n"
             << "- Anggota      : " << ps[i].jumlahAnggota << "\n"
             << "- Durasi       : " << ps[i].durasi << " menit\n"
             << "- Prioritas    : " << ps[i].prioritas << "\n\n";
    }
}

void bubbleSortDurasi(pemesanan ps[], int jumlahPemesanan) {
    // Bubble Sort - urut pemesanan berdasarkan durasi
    if (jumlahPemesanan == 0) {
        cout << "Data masih kosong!\n\n";
        return;
    }

    for (int i = 0; i < jumlahPemesanan - 1; ++i) {
        for (int j = 0; j < jumlahPemesanan - i - 1; ++j) {
            if (ps[j].durasi > ps[j + 1].durasi) {
                pemesanan temp = ps[j];
                ps[j] = ps[j + 1];
                ps[j + 1] = temp;
            }
        }
    }

    cout << "\nData berhasil diurutkan berdasarkan durasi.\n\n";
    tampilkanDaftar(ps, jumlahPemesanan); 
}

void linearSearchID(const pemesanan ps[], int jumlahPemesanan, int targetID) {
    // Linear Search - mencari pemesanan berdasarkan ID
    for (int i = 0; i < jumlahPemesanan; ++i) {
        if (ps[i].ID == targetID) {
            cout << "\nData ditemukan di indeks: " << i << "\n"
                 << "- ID pemesanan : " << ps[i].ID << "\n"
                 << "- Nama pemesan : " << ps[i].namaPemesan << "\n"
                 << "- Nama ruang   : " << ps[i].namaruangan << "\n"
                 << "- Durasi       : " << ps[i].durasi << " menit\n\n";
            return;
        }
    }

    cout << "Data tidak ditemukan!\n\n";
}

int hitungTotalDurasi(pemesanan ps[], int jumlahPemesanan) {
    if (jumlahPemesanan <= 0) {
        return 0;
    }
    return ps[jumlahPemesanan - 1].durasi + hitungTotalDurasi(ps, jumlahPemesanan - 1);
}

double hitungRataRataDurasi(pemesanan ps[], int jumlahPemesanan) {
    if (jumlahPemesanan <= 0) {
        return 0.0;
    }
    return (double)hitungTotalDurasi(ps, jumlahPemesanan) / jumlahPemesanan;
}

int hitungDurasiTertinggi(pemesanan ps[], int jumlahPemesanan) {
    if (jumlahPemesanan <= 0) {
        return 0;
    }
    int durasiTertinggi = ps[0].durasi;
    for (int i = 1; i < jumlahPemesanan; i++) {
        if (ps[i].durasi > durasiTertinggi) {
            durasiTertinggi = ps[i].durasi;
        }
    }
    return durasiTertinggi;
}

int hitungDurasiTerendah(pemesanan ps[], int jumlahPemesanan) {
    if (jumlahPemesanan <= 0) {
        return 0;
    }
    int durasiTerendah = ps[0].durasi;
    for (int i = 1; i < jumlahPemesanan; i++) {
        if (ps[i].durasi < durasiTerendah) {
            durasiTerendah = ps[i].durasi;
        }
    }
    return durasiTerendah;
}

void tampilkanStatistik(pemesanan ps[], int jumlahPemesanan) {
    if (jumlahPemesanan <= 0) {
        cout << "Belum ada data pemesanan apapun. \n";
        return;
    }
    cout << "================================\n";
    cout << "Analisis Statistik & Total Durasi\n";
    cout << "Total Durasi: " << hitungTotalDurasi(ps, jumlahPemesanan) << " Menit." << endl;
    cout << "Rata Rata Durasi: " << hitungRataRataDurasi(ps, jumlahPemesanan) << " Menit." << endl;
    cout << "Durasi Tertinggi: " << hitungDurasiTertinggi(ps, jumlahPemesanan) << " Menit." << endl;
    cout << "Durasi Terendah: " << hitungDurasiTerendah(ps, jumlahPemesanan) << " Menit." << endl;
    cout << "================================\n";
}

int main() {
    const int maks = 100;
    pemesanan ps[maks];
    int jumlahPemesanan = 0;
    int pilihan = 0;

    do {
        cout << "================================\n";
        cout << "\tSMART CAMPUS BOOKING SYSTEM UGM\n";
        cout << "1. Tambah pemesanan\n";
        cout << "2. Tampilkan semua pemesanan\n";
        cout << "3. Cari pemesanan berdasarkan ID\n";
        cout << "4. Urutkan Data Pemesanan (Manual Sort)\n";
        cout << "5. Cari Data Pemesanan (Manual Search)\n";
        cout << "6. Analisis Statistik & Total Durasi (Rekursif)\n";
        cout << "7. Keluar\n";
        cout << "Pilih (1-7): ";
        if (!(cin >> pilihan)) {
            cerr << "Input harus berupa angka.\n";
            return 1;
        }

        if (pilihan == 1) {
            datapemesanan(ps, jumlahPemesanan, maks);
        } else if (pilihan == 2) {
            for (int i = 0; i < jumlahPemesanan; ++i) {
                cout << "ID: " << ps[i].ID << ", Pemesan: " << ps[i].namaPemesan
                     << ", Ruangan: " << ps[i].namaruangan << ", Anggota: "
                     << ps[i].jumlahAnggota << ", Durasi: " << ps[i].durasi
                     << " menit, Prioritas: " << ps[i].prioritas << ", Kapasitas: "
                     << (ps[i].statuskapasitas ? "mencukupi" : "tidak mencukupi") << '\n';
            }
        } else if (pilihan == 3) {
            int idCari;
            bool ditemukan = false;
            cout << "Masukkan ID pemesanan: ";
            cin >> idCari;
            for (int i = 0; i < jumlahPemesanan; ++i) {
                if (ps[i].ID == idCari) {
                    cout << "Pemesanan ditemukan: " << ps[i].namaPemesan << " - "
                         << ps[i].namaruangan << ", " << ps[i].durasi << " menit\n";
                    ditemukan = true;
                    break;
                }
            }
            if (!ditemukan) {
                cout << "Pemesanan tidak ditemukan.\n";
            }
        } else if (pilihan == 4) {
                bubbleSortDurasi(ps, jumlahPemesanan);
        } else if (pilihan == 5) {
            int targetID;
            cout << "Masukkan ID pemesanan: ";
            if (!(cin >> targetID)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cerr << "Input ID harus berupa angka!\n\n";
            } else {
                linearSearchID(ps, jumlahPemesanan, targetID);
            }
        } else if (pilihan == 6) {
            tampilkanStatistik(ps, jumlahPemesanan);
        } else if (pilihan == 7) {
            cout << "Terima kasih telah menggunakan sistem ini... Jangan lupa untuk memesan lagi yaaa.\n";
        } else if (pilihan != 7) {
            cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 7);

    return 0;
}