# Smart Campus Room & Study Space Booking Simulator

> **Proyek Akhir Praktikum Pemrograman C++ — Kelompok 1**  
> Aplikasi Konsol C++ untuk Simulator Pemesanan Ruang Belajar & Fasilitas Kampus berbasis Array of Struct, Algoritma Rekursif, Serta Sorting & Searching Manual.

---

## Table of Contents
1. [Tentang Proyek](#-tentang-proyek)
2. [Fitur Utama](#-fitur-utama)
3. [Struktur Data Struct](#-struktur-data-struct)
4. [Anggota Kelompok & Pembagian Tugas](#-anggota-kelompok--pembagian-tugas)
5. [Spesifikasi Sistem & Aturan Algoritma](#-spesifikasi-sistem--aturan-algoritma)
6. [Panduan Kompilasi & Jalankan Program](#-panduan-kompilasi--jalankan-program)
7. [Panduan Penggunaan Menu Konsol](#-panduan-penggunaan-menu-konsol)
8. [Skenario Pengujian Test Cases](#-skenario-pengujian-test-cases)
9. [Struktur Repositori](#-struktur-repositori)

---

## Tentang Project

**Smart Campus Room & Study Space Booking Simulator** adalah program berbasis console C++ yang dirancang untuk mengelola, menganalisis, mengurutkan, dan mencari data pemesanan ruang belajar di lingkungan kampus secara terstruktur.

Program ini dibuat untuk memenuhi Tugas Akhir Praktikum Pemrograman dengan menerapkan konsep dasar C++ seperti *array of struct*, fungsi modular, logika percabangan, perulangan, fungsi rekursif, serta algoritma pengurutan (*sorting*) dan pencarian (*searching*) tanpa bergantung pada pustaka standar *Standard Template Library (STL)*.

---

## Fitur Utama

- **Pengelolaan Data Pemesanan (CRUD Dasar):** Menambah data pemesanan ruang baru dan menampilkan seluruh daftar pemesanan terdaftar secara rapi.
- **Validasi Kapasitas & Penentuan Prioritas (`IF-ELSE`):** Mengecek apakah jumlah peserta melebihi kapasitas ruangan dan mengklasifikasikan tingkat prioritas pemesanan (misalnya: Prioritas Tinggi untuk kegiatan besar dengan jumlah peserta 20 orang atau lebih).
- **Analisis & Perhitungan Statistik:**
  - Menghitung **Total Durasi** pemesanan menggunakan **Fungsi Rekursif**.
  - Menghitung **Rata-rata Durasi** pemesanan seluruh ruang.
  - Menentukan pemesanan dengan **Durasi Terpanjang (Maksimum)** dan **Durasi Terpendek (Minimum)**.
- **Pengurutan Data Manual (Manual Sorting):** Mengurutkan daftar pemesanan berdasarkan **Durasi Pemesanan** atau **ID Pemesanan** menggunakan algoritma *Bubble Sort* atau *Selection Sort* tanpa fungsi STL.
- **Pencarian Data Manual (Manual Searching):** Mencari pemesanan spesifik berdasarkan **ID Pemesanan** atau **Nama Ruang** menggunakan algoritma *Linear Search* atau *Binary Search*.
- **Deteksi Fitur Tantangan (Edge Cases):** Mendeteksi dan memberikan peringatan otomatis jika terdapat permintaan pemesanan yang melebihi kapasitas maksimum ruang (*overcapacity*).

---

## Struktur Data Struct

Setiap entitas pemesanan disimpan dalam struktur data `Booking` dengan komponen minimal sebagai berikut:

```cpp
struct Booking {
    string idPemesanan;    // ID unik pemesanan (contoh: "BK001")
    string namaPemesan;   // Nama mahasiswa atau organisasi pemesan
    string namaRuang;     // Nama atau nomor ruang belajar (contoh: "RK.201", "Lab-A")
    int kapasitasRuang;   // Kapasitas maksimal ruangan (orang)
    int jumlahPeserta;    // Jumlah peserta yang direncanakan (orang)
    int durasiMenit;      // Durasi pemesanan dalam satuan menit
    string prioritas;     // Kategori prioritas ("Tinggi" atau "Normal")
};
```

Seluruh data pemesanan dikelola dalam sebuah **Array of Struct** (`Booking daftarPemesanan[MAX_DATA]`).

---

## Anggota Kelompok & Pembagian Tugas

Proyek ini disusun oleh **Kelompok 1**:

| No | Nama Anggota | Peran | Tanggung Jawab Utama |
|---|---|---|---|  
| 1 | **Faiz Falah Fauzian** | Koordinator / Anggota 1 | Analisis masalah, penyusunan IPO & Pseudocode, perancangan Menu Utama konsol, dan integrasi seluruh modul C++. |
| 2 | **Muhammad Faiz Harry Saputra** | Anggota 2 | Deklarasi `struct` & `array of struct`, fungsi Input/Output data, percabangan `IF-ELSE`, dan perulangan. |
| 3 | **Malik Irhamsyah Perani** | Anggota 3 | Modularisasi fungsi, fungsi perhitungan statistik (Total, Rata-rata, Min/Max), dan implementasi **Fungsi Rekursif**. |
| 4 | **Muhammad Fahri Ramadhan** | Anggota 4 | Implementasi algoritma *Sorting* & *Searching* manual tanpa STL, pengujian fungsi, serta *debugging*. |
| 5 | **Beverly Marsya Yufuai** | Anggota 5 | Penyusunan laporan PDF, penyusunan 5 *test case*, *screenshot* pengujian, dan penyiapan berkas akhir. |

---

## Spesifikasi Sistem & Aturan Algoritma

1. **Bahasa Pemrograman:** C++ (Standar C++11 ke atas).
2. **Antarmuka:** *Console-based Interactive Menu*.
3. **Tanpa Library STL Tambahan:** Algoritma pengurutan (*Bubble/Selection Sort*) dan pencarian (*Linear/Binary Search*) diimplementasikan dari nol tanpa menggunakan pustaka `<algorithm>` STL seperti `std::sort` atau `std::binary_search`.
4. **Fungsi Rekursif Murni:** Perhitungan total durasi pemesanan memanfaatkan teknik rekursi dengan *base case* yang jelas (mengembalikan 0 jika `n <= 0`, dan menambahkan durasi elemen saat ini dengan pemanggilan rekursif `n-1`).

---

## Panduan Kompilasi & Jalankan Program

### Persyaratan
- Compiler C++ seperti **GCC/g++**, **Clang**, atau **MSVC**.
- Terminal / Command Prompt / PowerShell.

### Langkah-Langkah Kompilasi dan Eksekusi

1. **Buka Terminal di Direktori Proyek**:
   Arahkan terminal ke folder tempat file `main.cpp` disimpan.

2. **Kompilasi Source Code C++**:
   ```text
   g++ -std=c++11 -o smart_campus main.cpp
   ```

3. **Jalankan Program Executable**:
   - **Linux / macOS**:
     ```text
     ./smart_campus
     ```
   - **Windows**:
     ```text
     smart_campus.exe
     ```

---

## Panduan Penggunaan Menu Konsol

Tampilan menu utama program berulang hingga pengguna memilih opsi keluar:

```text
===================================================
 SMART CAMPUS ROOM & STUDY SPACE BOOKING SIMULATOR
===================================================
1. Tambah Data Pemesanan Ruang
2. Tampilkan Seluruh Data Pemesanan
3. Analisis Statistik & Total Durasi (Rekursif)
4. Urutkan Data Pemesanan (Manual Sort)
5. Cari Data Pemesanan (Manual Search)
6. Deteksi Peringatan Overcapacity
7. Keluar dari Program
===================================================
Pilih menu (1-7): 
```

---

## Skenario Pengujian Test Cases

Program ini diuji dengan minimal **5 Test Case** mencakup kondisi normal dan kondisi batas (*edge/boundary case*):

| ID Test | Deskripsi Skenario | Input Khusus | Ekspektasi Output |
|---|---|---|---|
| **TC01** | Input Data Normal | Ruang "RK.101", Kapasitas 10, Peserta 5, Durasi 60m | Data berhasil disimpan, status prioritas Normal. |
| **TC02** | Input Data Kegiatan Besar | Ruang "Aula Utama", Kapasitas 50, Peserta 35, Durasi 120m | Status prioritas berubah menjadi "Tinggi". |
| **TC03** | Boundary Case (Overcapacity) | Ruang "Diskusi 2", Kapasitas 4, Peserta 8, Durasi 45m | Program menampilkan peringatan batas kapasitas terlampaui. |
| **TC04** | Sorting Manual | Mengurutkan 5 data acak berdasarkan durasi | Data terurut secara ascending berdasarkan durasi (menit). |
| **TC05** | Searching Manual | Mencari ID Pemesanan "BK003" | Menampilkan rincian data pemesanan BK003 dengan tepat. |

---

## Struktur Repositori

```text
smart-campus-booking/
├── main.cpp                 # Source code utama aplikasi C++
├── README.md                # Dokumentasi repositori GitHub ini
├── docs/
│   └── Laporan_Kelompok_1.pdf  # Laporan lengkap proyek akhir
│   └── Pseudocode.md  # Pseudocode Program
│   └── Notes.md  # Catatan-catatan
└── screenshots/
    ├── menu_utama.png       # Screenshot eksekusi menu utama
    └── test_cases.png       # Screenshot hasil pengujian test case
```

---

## Lisensi & Atribusi
Proyek ini dikembangkan untuk kebutuhan akademis mata kuliah Praktikum Pemrograman di bawah panduan Dosen dan Asisten Praktikum. Seluruh kontribusi anggota kelompok tertera pada tabel kontribusi.
