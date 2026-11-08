#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <limits>

using namespace std;

struct Booking {
    string idPemesanan;    // ID unik pemesanan (contoh: "BK001")
    string namaPemesan;   // Nama mahasiswa atau organisasi pemesan
    string namaRuang;     // Nama atau nomor ruang belajar (contoh: "RK.201", "Lab-A")
    int kapasitasRuang;   // Kapasitas maksimal ruangan (orang)
    int jumlahPeserta;    // Jumlah peserta yang direncanakan (orang)
    int durasiMenit;      // Durasi pemesanan dalam satuan menit
    string prioritas;     // Kategori prioritas ("Tinggi" atau "Normal")
};

string buatIDPemesanan(int jumlahData) {
    stringstream formatID;
    formatID << setw(5) << setfill('0') << jumlahData + 1;
    return formatID.str();
}

void CekKapasitasDanPrioritas(int kapasitas, int jumlahPeserta){
    if (jumlahPeserta > kapasitas){
        cout << "Status: Permintaan melebihi kapasitas!" << endl;
    } else {
        cout << "Kapasitas mencukupi" << endl;
    }

    if (jumlahPeserta >= 20){
        cout << "Prioritas : Tinggi" << endl;
    } else {
        cout << "Prioritas : Normal" << endl;
    }
}

int HitungTotalDurasiRekursif(const vector<Booking>& daftarPemesanan, int n){
    if (n <= 0){
        return 0;
    } else {
        return daftarPemesanan[n-1].durasiMenit + HitungTotalDurasiRekursif(daftarPemesanan, n-1);
    }
}

void TambahPemesanan(vector<Booking>& daftarPemesanan) {
    Booking booking;

    booking.idPemesanan = buatIDPemesanan(daftarPemesanan.size());

    cout << "Nama pemesan: ";
    getline(cin, booking.namaPemesan);
    cout << "Nama ruang: ";
    getline(cin, booking.namaRuang);
    cout << "Kapasitas ruang: ";
    cin >> booking.kapasitasRuang;
    cout << "Jumlah peserta: ";
    cin >> booking.jumlahPeserta;
    cout << "Durasi (menit): ";
    cin >> booking.durasiMenit;

    booking.prioritas = booking.jumlahPeserta >= 20 ? "Tinggi" : "Normal";
    daftarPemesanan.push_back(booking);

    cout << "Data pemesanan berhasil ditambahkan." <<endl;
    CekKapasitasDanPrioritas(booking.kapasitasRuang, booking.jumlahPeserta);
}

void TampilkanData(const vector<Booking>& daftarPemesanan) {
    if (daftarPemesanan.empty()) {
        cout << "Data masih kosong!\n";
        return;
    }

    for (int i = 0; i < static_cast<int>(daftarPemesanan.size()); i++) {
        const Booking& booking = daftarPemesanan[i];
        cout << "\nData ke-" << i + 1 << '\n'
             << "ID pemesanan: " << booking.idPemesanan << '\n'
             << "Nama pemesan: " << booking.namaPemesan << '\n'
             << "Nama ruang: " << booking.namaRuang << '\n'
             << "Kapasitas ruang: " << booking.kapasitasRuang << '\n'
             << "Jumlah peserta: " << booking.jumlahPeserta << '\n'
             << "Durasi: " << booking.durasiMenit << " menit\n"
             << "Prioritas: " << booking.prioritas << '\n';
    }
}

void HitungStatistik(const vector<Booking>& daftarPemesanan) {
    int jumlahData = static_cast<int>(daftarPemesanan.size());
    if (jumlahData == 0) {
        cout << "Data masih kosong!\n";
        return;
    }

    int totalDurasi = HitungTotalDurasiRekursif(daftarPemesanan, jumlahData);
    double rataRata = static_cast<double>(totalDurasi) / jumlahData;
    int maxDurasi = daftarPemesanan[0].durasiMenit;
    int minDurasi = daftarPemesanan[0].durasiMenit;

    for (int i = 1; i < jumlahData; i++) {
        if (daftarPemesanan[i].durasiMenit > maxDurasi) {
            maxDurasi = daftarPemesanan[i].durasiMenit;
        }
        if (daftarPemesanan[i].durasiMenit < minDurasi) {
            minDurasi = daftarPemesanan[i].durasiMenit;
        }
    }

    cout << "Total Durasi (Rekursif): " << totalDurasi << " menit\n"
         << "Rata-rata Durasi: " << rataRata << " menit\n"
         << "Durasi Tertinggi: " << maxDurasi << " menit\n"
         << "Durasi Terendah: " << minDurasi << " menit\n";
}


void BubbleSortDurasi(vector<Booking>& daftarPemesanan) {
    int jumlahData = static_cast<int>(daftarPemesanan.size());
    for (int i = 0; i < jumlahData - 1; i++) {
        for (int j = 0; j < jumlahData - i - 1; j++) {
            if (daftarPemesanan[j].durasiMenit > daftarPemesanan[j + 1].durasiMenit) {
                Booking sementara = daftarPemesanan[j];
                daftarPemesanan[j] = daftarPemesanan[j + 1];
                daftarPemesanan[j + 1] = sementara;
            }
        }
    }
    cout << "Data berhasil diurutkan berdasarkan durasi.\n";
}

void LinearSearchID(const vector<Booking>& daftarPemesanan, const string& targetID) {
    for (int i = 0; i < static_cast<int>(daftarPemesanan.size()); i++) {
        if (daftarPemesanan[i].idPemesanan == targetID) {
            cout << "Data ditemukan di indeks: " << i << '\n'
                 << "ID pemesanan: " << daftarPemesanan[i].idPemesanan << '\n'
                 << "Nama pemesan: " << daftarPemesanan[i].namaPemesan << '\n'
                 << "Nama ruang: " << daftarPemesanan[i].namaRuang << '\n'
                 << "Durasi: " << daftarPemesanan[i].durasiMenit << " menit\n";
            return;
        }
    }
    cout << "Data tidak ditemukan!\n";
}

int main() {
    vector<Booking> daftarPemesanan;
    int pilihan;

    do {
        cout << "\n=== SMART CAMPUS BOOKING SYSTEM ===\n"
             << "1. Tambah Data Pemesanan\n"
             << "2. Tampilkan Semua Pemesanan\n"
             << "3. Hitung Statistik & Rekursif Durasi\n"
             << "4. Urutkan Pemesanan (Sorting Manual)\n"
             << "5. Cari Pemesanan (Searching Manual)\n"
             << "6. Keluar\n"
             << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (pilihan) {
            case 1:
                TambahPemesanan(daftarPemesanan);
                break;
            case 2:
                TampilkanData(daftarPemesanan);
                break;
            case 3:
                HitungStatistik(daftarPemesanan);
                break;
            case 4:
                BubbleSortDurasi(daftarPemesanan);
                break;
            case 5: {
                string targetID;
                cout << "Masukkan ID pemesanan yang dicari: ";
                cin >> targetID;
                LinearSearchID(daftarPemesanan, targetID);
                break;
            }
            case 6:
                cout << "Terima kasih!\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 6);

    return 0;
}

