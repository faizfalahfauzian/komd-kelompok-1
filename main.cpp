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
        cout << "4. Keluar\n";
        cout << "Pilih (1-4): ";
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
            cout << "Terima kasih telah menggunakan sistem ini... Jangan lupa untuk memesan lagi yaaa.\n";
        }
        else if (pilihan != 4) {
            cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 4);

    return 0;
}