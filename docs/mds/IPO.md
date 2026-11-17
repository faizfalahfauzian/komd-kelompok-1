# IPO (Input – Process – Output)
## Smart Campus Booking System UGM

IPO menjelaskan **apa yang masuk**, **apa yang diproses**, dan **apa yang keluar** dari setiap fitur program.

---

## 1. IPO Keseluruhan Program

| Komponen | Isi |
|---|---|
| **Input** | Pilihan menu (1–7), data pemesanan (nama, ruangan, jumlah anggota, durasi, kegunaan), ID untuk pencarian |
| **Process** | Validasi input → cek kapasitas → tentukan prioritas → simpan ke array → urutkan (bubble sort) → cari (linear search) → hitung statistik (rekursif & iteratif) |
| **Output** | Pesan konfirmasi/penolakan, daftar pemesanan, hasil pencarian, antrian per ruangan, statistik durasi, log pemesanan over capacity |

---

## 2. IPO Per Fitur

### 2.1 Menu Utama (`main`)

| | |
|---|---|
| **Input** | Angka pilihan menu `pilihan` (1–7) |
| **Process** | 1. Tampilkan menu.<br>2. Baca `pilihan`. Jika input bukan angka → bersihkan error (`cin.clear`), buang sisa baris (`cin.ignore`), ulangi menu.<br>3. `switch` ke fungsi sesuai pilihan.<br>4. Ulangi sampai `pilihan == 7`. |
| **Output** | Tampilan menu; pesan "Input harus berupa angka!" bila input salah; pesan "Pilihan tidak valid." bila angka di luar 1–7; pesan perpisahan saat keluar |

---

### 2.2 Menu 1 — Tambah Pemesanan (`datapemesanan`)

| | |
|---|---|
| **Input** | `namaPemesan` (string, satu baris), `pilihanRuang` (1–7), `jumlahAnggota` (int), `durasi` (int, menit), `kegunaan` (string, satu baris) |
| **Process** | 1. Cek apakah `jumlah >= maks (100)`. Jika ya → tolak.<br>2. Baca nama, buat ID 5 digit dari `jumlah + 1` (`buatIDPemesanan`).<br>3. Tampilkan 7 ruangan, baca pilihan. Jika di luar 1–7 → batal.<br>4. Isi nama ruangan & kapasitas dari array `namaRuang[]` dan `kapasitas[]`.<br>5. Baca `jumlahAnggota`, hitung `statuskapasitas = jumlahAnggota <= kapasitas`.<br>6. **Jika melebihi kapasitas** → tampilkan error, salin data ke array `overCapacity` (ID `OV-xxxxx`, durasi 0, prioritas "-"), lalu keluar tanpa menambah `jumlah`.<br>7. **Jika muat** → baca durasi, tentukan prioritas (`tentukanPrioritas`), baca kegunaan, simpan, lalu `++jumlah`. |
| **Output** | Salah satu dari:<br>• "Pesanan diterima. ID pemesanan: 0000X (Kategori Prioritas: …)"<br>• "[ERROR] Pesanan ditolak karena jumlah anggota (…) melebihi kapasitas ruangan (…)" + "[INFO] … dicatat ke sistem"<br>• "Pilihan ruangan tidak valid."<br>• "Tidak dapat menerima pesanan, karna pesanan sudah melebihi kapasitas maksimum." |

**Aturan penentuan prioritas (dari durasi):**

| Durasi (menit) | Prioritas | Skor (untuk sorting) |
|---|---|---|
| < 20 | Rendah | 1 |
| 20 – 60 | Sedang | 2 |
| > 60 | Tinggi | 3 |

**Daftar ruangan:**

| No | Ruangan | Kapasitas |
|---|---|---|
| 1 | Ruang Diskusi 1 | 10 |
| 2 | Ruang Diskusi 2 | 20 |
| 3 | Ruang Diskusi 3 | 25 |
| 4 | Ruang Creative 1 | 35 |
| 5 | Aula Utama | 100 |
| 6 | Ruang Creative 2 | 40 |
| 7 | Ruang Rapat | 30 |

---

### 2.3 Menu 2 — Tampilkan Semua Pemesanan (di dalam `main`)

| | |
|---|---|
| **Input** | Tidak ada input tambahan (memakai array `pemesanan` yang sudah terisi) |
| **Process** | Jika `jumlahPemesanan == 0` → pesan kosong. Selain itu, loop `i = 0 … jumlah-1` dan cetak semua field setiap pemesanan; status kapasitas diubah jadi teks "mencukupi" / "tidak mencukupi" dengan operator ternary |
| **Output** | Satu baris per pemesanan: ID, Pemesan, Ruangan, Anggota, Durasi, Prioritas, Kegunaan, Kapasitas. Atau "Belum ada pemesanan yang terdaftar." |

---

### 2.4 Menu 3 — Cari Data Pemesanan (`linearSearchID`)

| | |
|---|---|
| **Input** | `targetID` (string, contoh `00003`) |
| **Process** | Linear search: bandingkan `targetID` dengan `pemesanan[i].ID` dari indeks 0 sampai akhir. Berhenti di kecocokan pertama |
| **Output** | Jika ketemu: indeks array + ID, nama pemesan, ruangan, durasi, prioritas, kegunaan. Jika tidak: "Data tidak ditemukan!" |

---

### 2.5 Menu 4 — Urutkan Antrian Per Ruangan (`sortAntrianPerRuangan` + `tampilkanAntrianPerRuangan`)

| | |
|---|---|
| **Input** | Array `pemesanan` dan `jumlahPemesanan` (tidak ada input dari pengguna) |
| **Process** | 1. Jika data kosong → pesan.<br>2. **Bubble sort** dengan 3 tingkat perbandingan pada pasangan bersebelahan:<br>&nbsp;&nbsp;• **Tingkat 1:** `IDruang` kecil → besar.<br>&nbsp;&nbsp;• **Tingkat 2:** (ruangan sama) skor prioritas besar → kecil (Tinggi dulu).<br>&nbsp;&nbsp;• **Tingkat 3:** (ruangan & prioritas sama) ID kecil dulu (siapa daftar duluan, dia duluan / FIFO).<br>3. Tukar posisi memakai variabel `temp`.<br>4. Cetak hasil: header ruangan dicetak setiap `IDruang` berganti, nomor antrian di-reset ke 1. |
| **Output** | Pesan sukses + daftar antrian dikelompokkan per ruangan:<br>`=== Nama Ruangan ===` → `Antrian ke-1 (ID: …)`, nama, prioritas (durasi), anggota, kegunaan |

---

### 2.6 Menu 5 — Statistik & Total Durasi (`tampilkanStatistik`)

| | |
|---|---|
| **Input** | Array `pemesanan` dan `jumlahPemesanan` |
| **Process** | • `hitungTotalDurasi` → **rekursif**: `durasi[n-1] + hitungTotalDurasi(n-1)`, berhenti saat `n <= 0`.<br>• `hitungRataRataDurasi` → total ÷ jumlah (di-cast ke `double`).<br>• `hitungDurasiTertinggi` → loop mencari nilai maksimum.<br>• `hitungDurasiTerendah` → loop mencari nilai minimum. |
| **Output** | Total Durasi, Rata-Rata Durasi, Durasi Tertinggi, Durasi Terendah (semua dalam menit). Atau "Belum ada data pemesanan apapun." |

---

### 2.7 Menu 6 — Tampilkan Data Over Capacity (`tampilkanOverCapacity`)

| | |
|---|---|
| **Input** | Array `overCapacity` dan `jumlahOver` |
| **Process** | Jika kosong → pesan. Jika ada: loop semua data, hitung `selisih = jumlahAnggota - kapasitasruangan` untuk tiap data |
| **Output** | Per data: ID Log (`OV-xxxxx`), nama pemesan, ruangan & kapasitas maksimum, jumlah anggota + kelebihan berapa orang, status "Ditolak (Over Capacity)" |

---

### 2.8 Menu 7 — Keluar

| | |
|---|---|
| **Input** | Angka `7` |
| **Process** | Menampilkan pesan lalu kondisi `while (pilihan != 7)` bernilai false, loop berhenti |
| **Output** | "Terima kasih telah menggunakan sistem ini…" lalu program selesai (`return 0`) |

---

## 3. IPO Fungsi Pendukung

| Fungsi | Input | Process | Output |
|---|---|---|---|
| `buatIDPemesanan(jumlahData)` | int `jumlahData` | `jumlahData + 1`, diformat lebar 5 dan diisi `0` di depan (`setw(5)`, `setfill('0')`) via `stringstream` | string, mis. `"00001"` |
| `tentukanPrioritas(durasi)` | int `durasi` | if–else: `<20` / `<=60` / selainnya | `"Rendah"` / `"Sedang"` / `"Tinggi"` |
| `skorPrioritas(prioritas)` | string `prioritas` | Ubah teks jadi angka agar bisa dibandingkan | 3 / 2 / 1 |

---

## 4. Contoh Data Uji (untuk demo)

**Input:**

| ID | Pemesan | Ruang | Anggota | Durasi | Prioritas |
|---|---|---|---|---|---|
| 00001 | Andi | 3 (Diskusi 3) | 10 | 30 | Sedang |
| 00002 | Budi | 1 (Diskusi 1) | 8 | 90 | Tinggi |
| 00003 | Citra | 3 (Diskusi 3) | 12 | 120 | Tinggi |
| 00004 | Dewi | 1 (Diskusi 1) | 5 | 10 | Rendah |
| 00005 | Eko | 1 (Diskusi 1) | 6 | 45 | Sedang |

**Output Menu 4 (setelah sorting):**

```
=== Ruang Diskusi 1 ===
Antrian ke-1 → Budi  (00002, Tinggi)
Antrian ke-2 → Eko   (00005, Sedang)
Antrian ke-3 → Dewi  (00004, Rendah)

=== Ruang Diskusi 3 ===
Antrian ke-1 → Citra (00003, Tinggi)
Antrian ke-2 → Andi  (00001, Sedang)
```

**Output Menu 5:**

```
Total Durasi: 295 Menit.
Rata Rata Durasi: 59 Menit.
Durasi Tertinggi: 120 Menit.
Durasi Terendah: 10 Menit.
```

**Contoh over capacity:** pilih Ruang Diskusi 1 (kapasitas 10) dengan 15 anggota → ditolak, tercatat sebagai `OV-00001`, kelebihan **5 orang**.
