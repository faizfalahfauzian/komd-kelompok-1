#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <limits>

using namespace std;

struct Pemesanan {
    string namaPemesan; 
    string ID;
    int IDruang;
    string namaruangan;
    int kapasitasruangan;
    int jumlahAnggota;
    int durasi;
    string prioritas; 
    string kegunaan;  
    bool statuskapasitas;
};

string buatIDPemesanan(int jumlahData) {
    stringstream formatID;
    formatID << setw(5) << setfill('0') << jumlahData + 1;
    return formatID.str();
}

string tentukanPrioritas(int durasi) {
    if (durasi < 20) {
        return "Rendah";
    } else if (durasi <= 60) {
        return "Sedang";
    } else {
        return "Tinggi";
    }
}
int skorPrioritas(const string& prioritas) {
    if (prioritas == "Tinggi") return 3;
    if (prioritas == "Sedang") return 2;
    return 1; 
}

void datapemesanan(Pemesanan pemesanan[], int& jumlah, const int maks, Pemesanan overCapacity[], int& jumlahOver) { 
    if (jumlah >= maks) { 
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
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Pilihan ruangan tidak valid.\n";
        return;
    }

    pemesanan[jumlah].IDruang = pilihanRuang;
    pemesanan[jumlah].namaruangan = namaRuang[pilihanRuang - 1];
    pemesanan[jumlah].kapasitasruangan = kapasitas[pilihanRuang - 1];
    
    cout << "Jumlah anggota: ";
    cin >> pemesanan[jumlah].jumlahAnggota;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    pemesanan[jumlah].statuskapasitas = pemesanan[jumlah].jumlahAnggota <= pemesanan[jumlah].kapasitasruangan;
    
    if (!pemesanan[jumlah].statuskapasitas) {
        cerr << "\n[ERROR] Pesanan ditolak karena jumlah anggota (" << pemesanan[jumlah].jumlahAnggota 
             << ") melebihi kapasitas ruangan (" << pemesanan[jumlah].kapasitasruangan << ")!\n";
        
        if (jumlahOver < maks) {
            overCapacity[jumlahOver] = pemesanan[jumlah]; 
            overCapacity[jumlahOver].ID = "OV-" + buatIDPemesanan(jumlahOver); 
            overCapacity[jumlahOver].durasi = 0;
            overCapacity[jumlahOver].prioritas = "-";
            overCapacity[jumlahOver].kegunaan = "Ditolak (Over Capacity)";
            jumlahOver++;
            cout << "[INFO] Data percobaan pemesanan over capacity telah dicatat ke sistem.\n\n";
        }
        return;
    }

    cout << "Durasi pemesanan (menit): ";
    cin >> pemesanan[jumlah].durasi;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    pemesanan[jumlah].prioritas = tentukanPrioritas(pemesanan[jumlah].durasi);

    cout << "Kegunaan/keperluan pemesanan: ";
    getline(cin, pemesanan[jumlah].kegunaan);

    cout << "Pesanan diterima. ID pemesanan: " << pemesanan[jumlah].ID 
         << " (Kategori Prioritas: " << pemesanan[jumlah].prioritas << ")\n";
    ++jumlah;
}

void tampilkanOverCapacity(const Pemesanan overCapacity[], int jumlahOver) {
    cout << "\n================================\n";
    cout << "DATA PEMESANAN OVER CAPACITY\n";
    cout << "================================\n";
    if (jumlahOver == 0) {
        cout << "Belum ada data pemesanan yang melebihi kapasitas.\n\n";
        return;
    }

    for (int i = 0; i < jumlahOver; ++i) {
        int selisih = overCapacity[i].jumlahAnggota - overCapacity[i].kapasitasruangan;
        cout << "Data ke-" << i + 1 << "\n"
             << "- ID Log         : " << overCapacity[i].ID << "\n"
             << "- Nama Pemesan   : " << overCapacity[i].namaPemesan << "\n"
             << "- Ruangan Dipilih: " << overCapacity[i].namaruangan << " (Maks: " << overCapacity[i].kapasitasruangan << " orang)\n"
             << "- Jumlah Anggota : " << overCapacity[i].jumlahAnggota << " orang (Kelebihan " << selisih << " orang)\n"
             << "- Status         : " << overCapacity[i].kegunaan << "\n\n";
    }
}

void tampilkanAntrianPerRuangan(const Pemesanan pemesanan[], int jumlahPemesanan) {
    int ruangAktif = -1;
    int noAntrian = 1;

    for (int i = 0; i < jumlahPemesanan; ++i) {
        // Cetak header baru setiap berganti ruangan
        if (pemesanan[i].IDruang != ruangAktif) {
            ruangAktif = pemesanan[i].IDruang;
            noAntrian = 1;
            cout << "=== " << pemesanan[i].namaruangan << " ===\n";
        }

        cout << "Antrian ke-" << noAntrian++ << " (ID: " << pemesanan[i].ID << ")\n"
             << "- Nama pemesan : " << pemesanan[i].namaPemesan << "\n"
             << "- Prioritas    : " << pemesanan[i].prioritas << " (" << pemesanan[i].durasi << " menit)\n"
             << "- Anggota      : " << pemesanan[i].jumlahAnggota << " orang\n"
             << "- Kegunaan     : " << pemesanan[i].kegunaan << "\n\n";
    }
}

void sortAntrianPerRuangan(Pemesanan pemesanan[], int jumlahPemesanan) {
    if (jumlahPemesanan == 0) {
        cout << "Data masih kosong!\n\n";
        return;
    }

    for (int i = 0; i < jumlahPemesanan - 1; ++i) {
        for (int j = 0; j < jumlahPemesanan - i - 1; ++j) {
            bool perluTukar = false;

            if (pemesanan[j].IDruang > pemesanan[j + 1].IDruang) {
                perluTukar = true;
            } else if (pemesanan[j].IDruang == pemesanan[j + 1].IDruang) {
                int skorA = skorPrioritas(pemesanan[j].prioritas);
                int skorB = skorPrioritas(pemesanan[j + 1].prioritas);

                if (skorA < skorB) {
                    perluTukar = true;
                } else if (skorA == skorB && pemesanan[j].ID > pemesanan[j + 1].ID) {
                    perluTukar = true;
                }
            }

            if (perluTukar) {
                Pemesanan temp = pemesanan[j];
                pemesanan[j] = pemesanan[j + 1];
                pemesanan[j + 1] = temp;
            }
        }
    }

    cout << "\nData berhasil diurutkan berdasarkan antrian per ruangan (Prioritas Tinggi -> Rendah).\n\n";
    tampilkanAntrianPerRuangan(pemesanan, jumlahPemesanan); 
}

void linearSearchID(const Pemesanan pemesanan[], int jumlahPemesanan, const string& targetID) {
    for (int i = 0; i < jumlahPemesanan; ++i) {
        if (pemesanan[i].ID == targetID) {
            cout << "\nData ditemukan di indeks: " << i << "\n"
                 << "- ID pemesanan : " << pemesanan[i].ID << "\n"
                 << "- Nama pemesan : " << pemesanan[i].namaPemesan << "\n"
                 << "- Nama ruang   : " << pemesanan[i].namaruangan << "\n"
                 << "- Durasi       : " << pemesanan[i].durasi << " menit\n"
                 << "- Prioritas    : " << pemesanan[i].prioritas << "\n"
                 << "- Kegunaan     : " << pemesanan[i].kegunaan << "\n\n";
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
    Pemesanan overCapacity[maks];
    int jumlahPemesanan = 0;
    int jumlahOver = 0;
    int pilihan = 0;

    do {
        cout << "================================\n";
        cout << "\tSMART CAMPUS BOOKING SYSTEM UGM\n";
        cout << "1. Tambah pemesanan\n";
        cout << "2. Tampilkan semua pemesanan\n";
        cout << "3. Cari Data Pemesanan (Manual Search)\n";
        cout << "4. Urutkan Antrian Per Ruangan (Prioritas Tinggi -> Rendah)\n";
        cout << "5. Analisis Statistik & Total Durasi (Rekursif)\n";
        cout << "6. Tampilkan Data Pemesanan Over Capacity\n";
        cout << "7. Keluar\n";
        cout << "Pilih (1-7): ";

        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input harus berupa angka! Silakan coba lagi.\n\n";
            continue;
        }

        switch (pilihan) {
            case 1:
                datapemesanan(pemesanan, jumlahPemesanan, maks, overCapacity, jumlahOver);
                break;

            case 2:
                if (jumlahPemesanan == 0) {
                    cout << "Belum ada pemesanan yang terdaftar.\n";
                }
                for (int i = 0; i < jumlahPemesanan; ++i) {
                    cout << "ID: " << pemesanan[i].ID
                         << ", Pemesan: " << pemesanan[i].namaPemesan
                         << ", Ruangan: " << pemesanan[i].namaruangan
                         << ", Anggota: " << pemesanan[i].jumlahAnggota
                         << ", Durasi: " << pemesanan[i].durasi << " menit"
                         << ", Prioritas: " << pemesanan[i].prioritas
                         << ", Kegunaan: " << pemesanan[i].kegunaan
                         << ", Kapasitas: "
                         << (pemesanan[i].statuskapasitas
                                 ? "mencukupi"
                                 : "tidak mencukupi")
                         << '\n';
                }
                break;

            case 3: {
                string targetID;

                cout << "Masukkan ID pemesanan: ";
                cin >> targetID;
                linearSearchID(pemesanan, jumlahPemesanan, targetID);
                break;
            }

            case 4:
                sortAntrianPerRuangan(pemesanan, jumlahPemesanan);
                break;

            case 5:
                tampilkanStatistik(pemesanan, jumlahPemesanan);
                break;

            case 6:
                tampilkanOverCapacity(overCapacity, jumlahOver);
                break;

            case 7:
                cout << "Terima kasih telah menggunakan sistem ini... Jangan lupa untuk memesan lagi yaaa.\n";
                break;

            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }
    } while (pilihan != 7);

    return 0;
}
