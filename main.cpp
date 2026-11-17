#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <limits>
using namespace std;

struct Pemesanan { //custom data type untuk pemesanan atau dideclare sebagai ps 
    string namaPemesan; 
    string ID;
    int IDruang;
    string namaruangan;
    int kapasitasruangan;
    int jumlahAnggota;
    int durasi;
    string prioritas;
    bool statuskapasitas;
};

string buatIDPemesanan(int jumlahData) {
    stringstream formatID;
    formatID << setw(5) << setfill('0') << jumlahData + 1;
    return formatID.str();
}

void datapemesanan(Pemesanan pemesanan[], int& jumlah, const int maks) { 
   
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
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, pemesanan[jumlah].namaPemesan);
    
    pemesanan[jumlah].ID = buatIDPemesanan(jumlah);

    cout << "Pilih ruangan (1-7):\n";
    for (int i = 0; i < 7; ++i) {
        cout << i + 1 << ". " << namaRuang[i] << " (kapasitas " << kapasitas[i] << ")\n";
    }
    cin >> pilihanRuang;
    if (pilihanRuang < 1 || pilihanRuang > 7) {
        cout << "Pilihan ruangan tidak valid.\n";
        return;
    }

    pemesanan[jumlah].IDruang = pilihanRuang;
    pemesanan[jumlah].namaruangan = namaRuang[pilihanRuang - 1];
    pemesanan[jumlah].kapasitasruangan = kapasitas[pilihanRuang - 1];
    cout << "Jumlah anggota: ";
    cin >> pemesanan[jumlah].jumlahAnggota;

    pemesanan[jumlah].statuskapasitas = pemesanan[jumlah].jumlahAnggota <= pemesanan[jumlah].kapasitasruangan;
    if (!pemesanan[jumlah].statuskapasitas) {
        cerr << "\n[ERROR] Pesanan ditolak karena jumlah anggota (" << pemesanan[jumlah].jumlahAnggota << ") melebihi kapasitas ruangan ("  << pemesanan[jumlah].kapasitasruangan << ")!\nSilahkan coba lagi.\n\n";
        return;
    }
    cout << "Durasi pemesanan (menit): ";
    cin >> pemesanan[jumlah].durasi;
    
    cin.ignore();

    cout << "Prioritas/kegunaan: ";
    getline (cin, pemesanan[jumlah].prioritas);

    pemesanan[jumlah].statuskapasitas = pemesanan[jumlah].jumlahAnggota <= pemesanan[jumlah].kapasitasruangan;
    if (pemesanan[jumlah].statuskapasitas) {
        cout << "Pesanan diterima. ID pemesanan: " << pemesanan[jumlah].ID << "\n";
    } else {
        cout << "Pesanan ditolak di karenakan jumlah anggota melebihi kapasitas ruangan.\n";
    }
    ++jumlah;
}

void cariPemesanan(const Pemesanan pemesanan[], int jumlahPemesanan) {
    string idCari;
    bool ditemukan = false;

    cout << "Masukkan ID pemesanan: ";
    cin >> idCari;

    for (int i = 0; i < jumlahPemesanan; ++i) {
        if (pemesanan[i].ID == idCari) {
            cout << "\nPemesanan ditemukan:\n"
                 << "- Nama Pemesan : " << pemesanan[i].namaPemesan << "\n"
                 << "- Ruangan      : " << pemesanan[i].namaruangan << "\n"
                 << "- Durasi       : " << pemesanan[i].durasi << " menit\n\n";
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << "Pemesanan dengan ID " << idCari << " tidak ditemukan.\n\n";
    }
}

void tampilkanDaftar(const Pemesanan pemesanan[], int jumlahPemesanan) {
    // tampil daftar pemesanan
    for (int i = 0; i < jumlahPemesanan; ++i) {
        cout << "Data ke-" << i + 1 << "\n"
             << "- ID           : " << pemesanan[i].ID << "\n"
             << "- Nama pemesan : " << pemesanan[i].namaPemesan << "\n"
             << "- Ruangan      : " << pemesanan[i].namaruangan << "\n"
             << "- Anggota      : " << pemesanan[i].jumlahAnggota << "\n"
             << "- Durasi       : " << pemesanan[i].durasi << " menit\n"
             << "- Prioritas    : " << pemesanan[i].prioritas << "\n\n";
    }
}

void bubbleSortDurasi(Pemesanan pemesanan[], int jumlahPemesanan) {
    // Bubble Sort - urut pemesanan berdasarkan durasi
    if (jumlahPemesanan == 0) {
        cout << "Data masih kosong!\n\n";
        return;
    }

    for (int i = 0; i < jumlahPemesanan - 1; ++i) {
        for (int j = 0; j < jumlahPemesanan - i - 1; ++j) {
            if (pemesanan[j].durasi > pemesanan[j + 1].durasi) {
                Pemesanan temp = pemesanan[j];
                pemesanan[j] = pemesanan[j + 1];
                pemesanan[j + 1] = temp;
            }
        }
    }

    cout << "\nData berhasil diurutkan berdasarkan durasi.\n\n";
    tampilkanDaftar(pemesanan, jumlahPemesanan); 
}

void linearSearchID(const Pemesanan pemesanan[], int jumlahPemesanan, const string& targetID) {
    // Linear Search - mencari pemesanan berdasarkan ID
    for (int i = 0; i < jumlahPemesanan; ++i) {
        if (pemesanan[i].ID == targetID) {
            cout << "\nData ditemukan di indeks: " << i << "\n"
                 << "- ID pemesanan : " << pemesanan[i].ID << "\n"
                 << "- Nama pemesan : " << pemesanan[i].namaPemesan << "\n"
                 << "- Nama ruang   : " << pemesanan[i].namaruangan << "\n"
                 << "- Durasi       : " << pemesanan[i].durasi << " menit\n\n";
            return;
        }
    }

    cout << "Data tidak ditemukan!\n\n";
}

int hitungTotalDurasi(const Pemesanan pemesanan[], int jumlahPemesanan) {
    if (jumlahPemesanan <= 0) {
        return 0;
    }
    return pemesanan[jumlahPemesanan - 1].durasi + hitungTotalDurasi(pemesanan, jumlahPemesanan - 1);
}

double hitungRataRataDurasi(const Pemesanan pemesanan[], int jumlahPemesanan) {
    if (jumlahPemesanan <= 0) {
        return 0.0;
    }
    return (double)hitungTotalDurasi(pemesanan, jumlahPemesanan) / jumlahPemesanan;
}

int hitungDurasiTertinggi(const Pemesanan pemesanan[], int jumlahPemesanan) {
    if (jumlahPemesanan <= 0) {
        return 0;
    }
    int durasiTertinggi = pemesanan[0].durasi;
    for (int i = 1; i < jumlahPemesanan; i++) {
        if (pemesanan[i].durasi > durasiTertinggi) {
            durasiTertinggi = pemesanan[i].durasi;
        }
    }
    return durasiTertinggi;
}

int hitungDurasiTerendah(const Pemesanan pemesanan[], int jumlahPemesanan) {
    if (jumlahPemesanan <= 0) {
        return 0;
    }
    int durasiTerendah = pemesanan[0].durasi;
    for (int i = 1; i < jumlahPemesanan; i++) {
        if (pemesanan[i].durasi < durasiTerendah) {
            durasiTerendah = pemesanan[i].durasi;
        }
    }
    return durasiTerendah;
}

void tampilkanStatistik(const Pemesanan pemesanan[], int jumlahPemesanan) {
    if (jumlahPemesanan <= 0) {
        cout << "Belum ada data pemesanan apapun. \n";
        return;
    }
    cout << "================================\n";
    cout << "Analisis Statistik & Total Durasi\n";
    cout << "Total Durasi: " << hitungTotalDurasi(pemesanan, jumlahPemesanan) << " Menit." << endl;
    cout << "Rata Rata Durasi: " << hitungRataRataDurasi(pemesanan, jumlahPemesanan) << " Menit." << endl;
    cout << "Durasi Tertinggi: " << hitungDurasiTertinggi(pemesanan, jumlahPemesanan) << " Menit." << endl;
    cout << "Durasi Terendah: " << hitungDurasiTerendah(pemesanan, jumlahPemesanan) << " Menit." << endl;
    cout << "================================\n";
}

int main() {
    const int maks = 100;
    Pemesanan pemesanan[maks];
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

    switch (pilihan) {
        case 1:
            datapemesanan(pemesanan, jumlahPemesanan, maks);
            break;

        case 2:
            for (int i = 0; i < jumlahPemesanan; ++i) {
                cout << "ID: " << pemesanan[i].ID
                     << ", Pemesan: " << pemesanan[i].namaPemesan
                     << ", Ruangan: " << pemesanan[i].namaruangan
                     << ", Anggota: " << pemesanan[i].jumlahAnggota
                     << ", Durasi: " << pemesanan[i].durasi
                     << " menit, Prioritas: " << pemesanan[i].prioritas
                     << ", Kapasitas: "
                     << (pemesanan[i].statuskapasitas
                             ? "mencukupi"
                             : "tidak mencukupi")
                     << '\n';
            }
            break;

        case 3: {
            string idCari;
            bool ditemukan = false;

            cout << "Masukkan ID pemesanan: ";
            cin >> idCari;

            for (int i = 0; i < jumlahPemesanan; ++i) {
                if (pemesanan[i].ID == idCari) {
                    cout << "Pemesanan ditemukan: "
                         << pemesanan[i].namaPemesan << " - "
                         << pemesanan[i].namaruangan << ", "
                         << pemesanan[i].durasi << " menit\n";
                    ditemukan = true;
                    break;
                }
            }

            if (!ditemukan) {
                cout << "Pemesanan tidak ditemukan.\n";
            }
            break;
        }

        case 4:
            bubbleSortDurasi(pemesanan, jumlahPemesanan);
            break;

        case 5: {
            string targetID;

            cout << "Masukkan ID pemesanan: ";
            cin >> targetID;
            linearSearchID(pemesanan, jumlahPemesanan, targetID);
            break;
        }

        case 6:
            tampilkanStatistik(pemesanan, jumlahPemesanan);
            break;

        case 7:
            cout << "Terima kasih telah menggunakan sistem ini... "
                 << "Jangan lupa untuk memesan lagi yaaa.\n";
            break;

        default:
            cout << "Pilihan tidak valid.\n";
            break;
    }
} while (pilihan != 7);

return 0;

    return 0;
}
