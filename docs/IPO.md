# IPO Smart Campus Booking System

IPO menjelaskan **Input**, **Process**, dan **Output** dari Smart Campus Booking System.

## 1. IPO Sistem

| Input | Process | Output |
|---|---|---|
| Pilihan menu (1–6) | Membaca pilihan dan menjalankan fitur yang sesuai. Menu ditampilkan kembali sampai pengguna memilih 6. | Menu utama, hasil fitur yang dipilih, atau pesan pilihan tidak valid. |
| Nama pemesan, nama ruang, kapasitas ruang, jumlah peserta, dan durasi pemesanan | Membuat ID pemesanan otomatis lima digit berdasarkan jumlah data, menentukan prioritas, lalu menyimpan data sebagai `Booking`. | Konfirmasi data berhasil ditambahkan, ID pemesanan saat ditampilkan, dan status kapasitas serta prioritas. |
| Data pemesanan yang tersimpan | Menelusuri daftar pemesanan. | Seluruh rincian pemesanan, atau pesan bahwa data masih kosong. |
| Data durasi setiap pemesanan | Menjumlahkan durasi secara rekursif, menghitung rata-rata, lalu mencari durasi terbesar dan terkecil. | Total durasi, rata-rata durasi, durasi tertinggi, dan durasi terendah. |
| Daftar pemesanan dan durasi masing-masing | Mengurutkan data secara ascending berdasarkan durasi menggunakan Bubble Sort. | Daftar pemesanan tersusun dari durasi terpendek ke terpanjang dan pesan bahwa pengurutan berhasil. |
| ID pemesanan yang dicari | Membandingkan ID target dengan ID setiap data secara berurutan menggunakan Linear Search. | Indeks dan rincian singkat data jika ditemukan, atau pesan bahwa data tidak ditemukan. |

## 2. Rincian IPO per Fitur

### A. Tambah Data Pemesanan

**Input**

- Nama pemesan
- Nama ruang
- Kapasitas ruang
- Jumlah peserta
- Durasi pemesanan dalam menit

**Process**

1. Membuat ID otomatis dengan format lima digit, dimulai dari `00001`.
2. Menentukan prioritas `Tinggi` jika jumlah peserta minimal 20; selain itu `Normal`.
3. Menambahkan data pemesanan ke daftar.
4. Membandingkan jumlah peserta dengan kapasitas ruang.

**Output**

- Konfirmasi data berhasil ditambahkan.
- Status kapasitas mencukupi atau permintaan melebihi kapasitas.
- Prioritas kegiatan.

### B. Tampilkan Semua Pemesanan

**Input**

- Daftar pemesanan yang tersimpan.

**Process**

- Menelusuri daftar dan membaca setiap field pada data pemesanan.

**Output**

- Rincian semua pemesanan; atau pesan `Data masih kosong!` jika belum ada data.

### C. Hitung Statistik Durasi

**Input**

- Durasi semua pemesanan yang tersimpan.

**Process**

1. Menghitung total durasi dengan fungsi rekursif.
2. Menghitung rata-rata dengan membagi total durasi dengan jumlah data.
3. Mencari nilai durasi maksimum dan minimum.

**Output**

- Total durasi, rata-rata durasi, durasi tertinggi, dan durasi terendah.
- Pesan `Data masih kosong!` jika belum ada pemesanan.

### D. Urutkan Pemesanan

**Input**

- Daftar pemesanan beserta durasinya.

**Process**

- Membandingkan durasi data yang bersebelahan dan menukarnya dengan Bubble Sort sampai urut menaik.

**Output**

- Daftar pemesanan terurut berdasarkan durasi dari yang paling singkat.
- Pesan bahwa pengurutan berhasil.

### E. Cari Pemesanan

**Input**

- ID pemesanan yang ingin dicari.

**Process**

- Membandingkan ID target dengan ID pada setiap elemen daftar secara berurutan.

**Output**

- Indeks, ID, nama pemesan, nama ruang, dan durasi jika data ditemukan.
- Pesan `Data tidak ditemukan!` jika ID tidak ada dalam daftar.
