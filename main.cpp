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
    int kelebihan;         

// [DIUBAH] sekarang menerima array overload (ov) dan jumlahOverload
void datapemesanan(pemesanan ps[], int& jumlah, const int maks,
                   pemesanan ov[], int& jumlahOverload) {

    const string namaRuang[] = {
        "Ruang Diskusi 1", "Ruang Diskusi 2", "Ruang Diskusi 3",
        "Ruang Creative 1", "Aula Utama", "Ruang Creative 2", "Ruang Rapat"
    };
    const int kapasitas[] = {10, 20, 25, 35, 100, 40, 30};
    int pilihanRuang;

    // [BARU] data diisi dulu ke variabel sementara, baru dipindah ke
    // array normal (ps) atau array overload (ov) sesuai kapasitas
    pemesanan p;

    cout << "Nama Pemesan: ";
    cin >> p.namaPemesan;
    cout << "Masukkan ID pemesanan: ";
    cin >> p.ID;

    cout << "Pilih ruangan (1-7):\n";
    for (int i = 0; i < 7; ++i) {
        cout << i + 1 << ". " << namaRuang[i] << " (kapasitas " << kapasitas[i] << ")\n";
    }
    cin >> pilihanRuang;
    if (pilihanRuang < 1 || pilihanRuang > 7) {
        cout << "Pilihan ruangan tidak valid.\n";
        return;
    }

    p.IDruang = pilihanRuang;
    p.namaruangan = namaRuang[pilihanRuang - 1];
    p.kapasitasruangan = kapasitas[pilihanRuang - 1];
    cout << "Jumlah anggota: ";
    cin >> p.jumlahAnggota;

    p.statuskapasitas = p.jumlahAnggota <= p.kapasitasruangan;
    p.kelebihan = p.statuskapasitas ? 0 : p.jumlahAnggota - p.kapasitasruangan;

    // [BARU] cek ketersediaan tempat penyimpanan sesuai jenis pesanan
    if (p.statuskapasitas && jumlah >= maks) {
        cout << "Tidak dapat menerima pesanan, karna pesanan sudah melebihi kapasitas maksimum.\n";
        return;
    }
    if (!p.statuskapasitas && jumlahOverload >= maks) {
        cout << "Penyimpanan data overload sudah penuh.\n";
        return;
    }

    cout << "Durasi pemesanan (menit): ";
    cin >> p.durasi;

    cin.ignore();

    cout << "Prioritas/kegunaan: ";
    getline(cin, p.prioritas);

    if (p.statuskapasitas) {
        ps[jumlah] = p;
        ++jumlah;
        cout << "Pesanan diterima.\n";
    } else {
        // [BARU] sistem overload capacity: pesanan tidak dibuang, tapi disimpan terpisah
        ov[jumlahOverload] = p;
        ++jumlahOverload;
        cerr << "\n[OVERLOAD] Jumlah anggota (" << p.jumlahAnggota
             << ") melebihi kapasitas ruangan (" << p.kapasitasruangan
             << ") sebanyak " << p.kelebihan << " orang.\n"
             << "Pesanan tidak diproses, tetapi disimpan di data overload capacity.\n\n";
    }
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

// [BARU] menampilkan data pesanan yang overload capacity
void tampilkanOverload(const pemesanan ov[], int jumlahOverload) {
    if (jumlahOverload == 0) {
        cout << "Belum ada data overload capacity.\n\n";
        return;
    }
    cout << "========== DATA OVERLOAD CAPACITY ==========\n";
    for (int i = 0; i < jumlahOverload; ++i) {
        cout << "Data ke-" << i + 1 << "\n"
             << "- ID           : " << ov[i].ID << "\n"
             << "- Nama pemesan : " << ov[i].namaPemesan << "\n"
             << "- Ruangan      : " << ov[i].namaruangan << "\n"
             << "- Kapasitas    : " << ov[i].kapasitasruangan << " orang\n"
             << "- Anggota      : " << ov[i].jumlahAnggota << " orang\n"
             << "- Kelebihan    : " << ov[i].kelebihan << " orang\n"
             << "- Durasi       : " << ov[i].durasi << " menit\n"
             << "- Prioritas    : " << ov[i].prioritas << "\n\n";
    }
    cout << "Total pesanan overload: " << jumlahOverload << "\n";
    cout << "============================================\n\n";
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
    pemesanan ov[maks];          
    int jumlahPemesanan = 0;
    int jumlahOverload = 0;      
    int pilihan = 0;

    do {
        cout << "===================================================\n";
        cout << "\tSMART CAMPUS BOOKING SYSTEM UGM\n";
        cout << "1. Tambah pemesanan\n";
        cout << "2. Tampilkan semua pemesanan\n";
        cout << "3. Cari pemesanan berdasarkan ID\n";
        cout << "4. Urutkan Data Pemesanan (Manual Sort)\n";
        cout << "5. Cari Data Pemesanan (Manual Search)\n";
        cout << "6. Analisis Statistik & Total Durasi (Rekursif)\n";
        cout << "7. Data Overload Capacity\n";
        cout << "8. Keluar\n";                   
        cout << "===================================================\n";
        cout << "Pilih (1-8): ";
        if (!(cin >> pilihan)) {
            cerr << "Input harus berupa angka.\n";
            return 1;
        }

        if (pilihan == 1) {
            datapemesanan(ps, jumlahPemesanan, maks, ov, jumlahOverload);
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
        } else if (pilihan == 7) {                       // [BARU]
            tampilkanOverload(ov, jumlahOverload);
        } else if (pilihan == 8) {                       // [DIUBAH]
            cout << "Terima kasih telah menggunakan sistem ini... Jangan lupa untuk memesan lagi yaaa.\n";
        } else {
            cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 8);

    return 0;
}