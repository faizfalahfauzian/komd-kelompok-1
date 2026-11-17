#  Smart Campus Booking System - Tugas Akhir Kelompok 1 Praktikum Pemrograman KOMD

![C++](https://img.shields.io/badge/C%2B%2B-11%2B-00599C?logo=c%2B%2B&logoColor=white)
![Type](https://img.shields.io/badge/type-console%20app-lightgrey)
![Status](https://img.shields.io/badge/status-academic%20project-blue)

Aplikasi **console berbasis C++** untuk mengelola pemesanan ruangan kampus. Sistem memvalidasi kapasitas ruangan, menentukan prioritas pemesanan berdasarkan durasi, membentuk antrian per ruangan, dan menyajikan statistik durasi pemakaian.

---

##  Table of Contents

- [Fitur](#-fitur)
- [Aturan Sistem](#-aturan-sistem)
- [Cara Menjalankan](#-cara-menjalankan)
- [Contoh Penggunaan](#-contoh-penggunaan)
- [Struktur Proyek](#-struktur-proyek)
- [Konsep & Algoritma](#-konsep--algoritma)
- [Keterbatasan](#-keterbatasan)
- [Pengembangan Selanjutnya](#-pengembangan-selanjutnya)
- [Dokumentasi Tambahan](#-dokumentasi-tambahan)
- [Pembuat](#-pembuat)

---

##  Features

| Menu | Fitur | Keterangan |
|:---:|---|---|
| 1 | **Tambah pemesanan** | Input nama, ruangan, jumlah anggota, durasi, dan keperluan. ID dibuat otomatis (`00001`, `00002`, …) |
| 2 | **Tampilkan semua pemesanan** | Menampilkan seluruh pemesanan yang diterima |
| 3 | **Cari pemesanan** | Pencarian berdasarkan ID menggunakan *linear search* |
| 4 | **Urutkan antrian per ruangan** | Pengurutan dengan *bubble sort*: ruangan → prioritas → waktu pendaftaran |
| 5 | **Statistik & total durasi** | Total (rekursif), rata-rata, tertinggi, dan terendah |
| 6 | **Data over capacity** | Log percobaan pemesanan yang ditolak karena melebihi kapasitas |
| 7 | **Keluar** | Menutup program |

---

##  System Rules

### Daftar Ruangan

| No | Ruangan | Kapasitas |
|:---:|---|:---:|
| 1 | Ruang Diskusi 1 | 10 |
| 2 | Ruang Diskusi 2 | 20 |
| 3 | Ruang Diskusi 3 | 25 |
| 4 | Ruang Creative 1 | 35 |
| 5 | Aula Utama | 100 |
| 6 | Ruang Creative 2 | 40 |
| 7 | Ruang Rapat | 30 |

### Prioritas Berdasarkan Durasi

| Durasi | Prioritas |
|---|---|
| kurang dari 20 menit | Rendah |
| 20 – 60 menit | Sedang |
| lebih dari 60 menit | Tinggi |

### Aturan Lainnya

- Jika **jumlah anggota > kapasitas ruangan**, pemesanan **ditolak** dan dicatat di log *over capacity* dengan ID berawalan `OV-` (mis. `OV-00001`).
- Pemesanan yang ditolak **tidak** memakai nomor ID pemesanan resmi.
- Kapasitas penyimpanan maksimum: **100** pemesanan diterima dan **100** log over capacity.
- Urutan antrian per ruangan: **prioritas lebih tinggi dahulu**; jika prioritas sama, **ID lebih kecil (mendaftar lebih awal) dahulu**.

---

## How to Run

### Prasyarat

Compiler C++ yang mendukung C++11 atau lebih baru (misalnya **g++**, **clang++**, atau MinGW di Windows).

### Compile & Run

```bash
# 1. Clone repositori
git clone https://github.com/faizfalahfauzian/komd-kelompok-1.git
cd komd-kelompok-1

# 2. Compile
g++ -std=c++11 -Wall -o booking main.cpp

# 3. Jalankan
./booking          # Linux / macOS
booking.exe        # Windows
```

---

##  Contoh Penggunaan

### Menu utama

```
================================
	SMART CAMPUS BOOKING SYSTEM UGM
1. Tambah pemesanan
2. Tampilkan semua pemesanan
3. Cari Data Pemesanan (Manual Search)
4. Urutkan Antrian Per Ruangan (Prioritas Tinggi -> Rendah)
5. Analisis Statistik & Total Durasi (Rekursif)
6. Tampilkan Data Pemesanan Over Capacity
7. Keluar
Pilih (1-7):
```

### Pemesanan berhasil

```
Pilih (1-7): 1
Nama Pemesan: Andi
Pilihan ruangan:
1. Ruang Diskusi 1 (kapasitas 10)
2. Ruang Diskusi 2 (kapasitas 20)
3. Ruang Diskusi 3 (kapasitas 25)
4. Ruang Creative 1 (kapasitas 35)
5. Aula Utama (kapasitas 100)
6. Ruang Creative 2 (kapasitas 40)
7. Ruang Rapat (kapasitas 30)
Pilih ruangan (1-7): 3
Jumlah anggota: 10
Durasi pemesanan (menit): 30
Kegunaan/keperluan pemesanan: Diskusi kelompok
Pesanan diterima. ID pemesanan: 00001 (Kategori Prioritas: Sedang)
```

### Pemesanan ditolak (over capacity)

```
Pilih ruangan (1-7): 1
Jumlah anggota: 15

[ERROR] Pesanan ditolak karena jumlah anggota (15) melebihi kapasitas ruangan (10)!
[INFO] Data percobaan pemesanan over capacity telah dicatat ke sistem.
```

### Hasil pengurutan antrian (Menu 4)

```
=== Ruang Diskusi 1 ===
Antrian ke-1 (ID: 00002)
- Nama pemesan : Budi
- Prioritas    : Tinggi (90 menit)
...
Antrian ke-2 (ID: 00005)
- Nama pemesan : Eko
- Prioritas    : Sedang (45 menit)
...
=== Ruang Diskusi 3 ===
Antrian ke-1 (ID: 00003)
- Nama pemesan : Citra
- Prioritas    : Tinggi (120 menit)
...
```

### Statistik (Menu 5)

```
Total Durasi: 295 Menit.
Rata Rata Durasi: 59 Menit.
Durasi Tertinggi: 120 Menit.
Durasi Terendah: 10 Menit.
```

---

##  Struktur Proyek

```
.
├── main.cpp              # Seluruh kode program
├── README.md             # Dokumen ini
└── docs/
    ├── mds/
        ├── 1_pseudocode.md   # Pseudocode 
        ├── 2_IPO.md          # Input - Process - Output
        └── 3_Notes.md        # Catatan alur & cara kerja kode
    └── images/
    └── reports/
```

### Ringkasan Fungsi di `main.cpp`

| Fungsi | Peran |
|---|---|
| `buatIDPemesanan` | Membuat ID 5 digit dengan `stringstream`, `setw`, `setfill` |
| `tentukanPrioritas` | Mengubah durasi menjadi Rendah / Sedang / Tinggi |
| `skorPrioritas` | Mengubah teks prioritas menjadi skor 1–3 untuk sorting |
| `datapemesanan` | Alur input pemesanan + validasi kapasitas + pencatatan over capacity |
| `sortAntrianPerRuangan` | Bubble sort bertingkat, lalu menampilkan antrian |
| `tampilkanAntrianPerRuangan` | Mencetak antrian dikelompokkan per ruangan |
| `linearSearchID` | Mencari pemesanan berdasarkan ID |
| `hitungTotalDurasi` | Menjumlah durasi secara **rekursif** |
| `hitungRataRataDurasi`, `hitungDurasiTertinggi`, `hitungDurasiTerendah` | Statistik durasi |
| `tampilkanStatistik` | Menampilkan seluruh statistik |
| `tampilkanOverCapacity` | Menampilkan log pemesanan yang ditolak |

---

##  Concept and Algorithm

| Konsep | Penerapan |
|---|---|
| `struct` | `Pemesanan` menyimpan seluruh atribut satu pemesanan |
| Array of struct | Penyimpanan data pemesanan dan log over capacity |
| Pass by reference | `int& jumlah`, `int& jumlahOver` agar counter berubah di `main` |
| `const` parameter | Fungsi tampil/cari tidak mengubah data |
| Rekursi | `hitungTotalDurasi` |
| Bubble Sort | Pengurutan 3 tingkat (ruangan, prioritas, ID) |
| Linear Search | Pencarian ID |
| Input handling | `cin.clear()` dan `cin.ignore()` untuk input non-angka dan sisa buffer |

### Kompleksitas

| Operasi | Waktu |
|---|---|
| Tambah pemesanan | O(1) |
| Linear search | O(n) |
| Bubble sort | O(n²) |
| Total durasi (rekursif) | O(n) waktu, O(n) stack |
| Rata-rata / maks / min | O(n) |

---

## Constraints

- Data hanya disimpan di memori, sehingga **hilang saat program ditutup**.
- Input `jumlahAnggota` dan `durasi` **belum divalidasi** (nilai negatif/nol diterima, input huruf dapat mengganggu pembacaan berikutnya).
- Belum ada tanggal/jam, sehingga antrian hanya berdasarkan prioritas dan belum mendeteksi bentrok jadwal.
- Belum ada fitur ubah / batalkan pemesanan.
- Pencarian hanya mencakup pemesanan yang diterima (log `OV-` tidak ikut dicari), dan ID harus diketik lengkap 5 digit.
- Prioritas hanya ditentukan oleh durasi.

---

## Possible Development

- [ ] Validasi input (angka positif, ulangi sampai valid)
- [ ] Tambah tanggal & jam, serta pengecekan bentrok jadwal
- [ ] Simpan dan muat data dari file (`fstream`)
- [ ] Fitur ubah / batalkan pemesanan
- [ ] Ganti array statis dengan `std::vector`
- [ ] Ganti bubble sort dengan `std::sort` + comparator
- [ ] Pencarian berdasarkan nama pemesan atau ruangan

---

##  Dokumentasi Tambahan

Folder [`docs/`](docs/) berisi dokumentasi proyek:

- [Pseudocode](docs/mds/pseudocode.md)
- [IPO (Input – Process – Output)](docs/mds/IPO.md)
- [Catatan alur & cara kerja kode](docs/mds/Notes.md)
- [Screenshots and Test Cases](docs/images)
- [Laporan Project](docs/reports)

---

## 👤 Pembuat

**Faiz Falah Fauzian, Muhammad Fahri Ramadhan, Muhammad Faiz Harry Saputra, Beverly Yufuai**
Mahasiswa Ilmu Komputer, semester 1
Repository Project: (https://github.com/faizfalahfauzian/komd-kelompok-1)

---

## 📄 Lisensi

Proyek ini dibuat untuk keperluan Mata Kuliah Praktikum Pemrograman kelas KOMD
