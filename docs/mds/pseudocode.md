# Pseudocode Smart Campus Booking System

## Deklarasi data

```text
STRUCTURE Booking
    idPemesanan   : STRING
    namaPemesan   : STRING
    namaRuang     : STRING
    kapasitasRuang: INTEGER
    jumlahPeserta : INTEGER
    durasiMenit   : INTEGER
    prioritas     : STRING
ENDSTRUCTURE

DECLARE daftarPemesanan AS VECTOR OF Booking
```

ID disimpan sebagai `STRING` agar nol di depannya tidak hilang. ID dibuat otomatis dengan format lima digit, dimulai dari `00001`.

## Program utama

```text
PROGRAM Main
BEGIN
    DECLARE pilihan AS INTEGER

    REPEAT
        DISPLAY "=== SMART CAMPUS BOOKING SYSTEM ==="
        DISPLAY "1. Tambah Data Pemesanan"
        DISPLAY "2. Tampilkan Semua Pemesanan"
        DISPLAY "3. Hitung Statistik & Rekursif Durasi"
        DISPLAY "4. Urutkan Pemesanan (Sorting Manual)"
        DISPLAY "5. Cari Pemesanan (Searching Manual)"
        DISPLAY "6. Keluar"
        INPUT pilihan
        BERSIHKAN SISA BARIS INPUT

        SWITCH pilihan
            CASE 1:
                CALL TambahPemesanan(daftarPemesanan)
            CASE 2:
                CALL TampilkanData(daftarPemesanan)
            CASE 3:
                CALL HitungStatistik(daftarPemesanan)
            CASE 4:
                CALL BubbleSortDurasi(daftarPemesanan)
            CASE 5:
                INPUT targetID
                CALL LinearSearchID(daftarPemesanan, targetID)
            CASE 6:
                DISPLAY "Terima kasih!"
            DEFAULT:
                DISPLAY "Pilihan tidak valid!"
        ENDSWITCH
    UNTIL pilihan == 6
ENDPROGRAM
```

## Membuat ID pemesanan

```text
FUNCTION BuatIDPemesanan(jumlahData) RETURNS STRING
BEGIN
    nomorID = jumlahData + 1
    UBAH nomorID MENJADI STRING DENGAN LEBAR 5 KARAKTER
        DAN TAMBAHKAN '0' DI DEPAN JIKA PERLU
    RETURN nomorID
ENDFUNCTION
```

## Menambah pemesanan

```text
PROCEDURE TambahPemesanan(daftarPemesanan)
BEGIN
    DECLARE booking AS Booking

    booking.idPemesanan = BuatIDPemesanan(daftarPemesanan.SIZE)

    INPUT booking.namaPemesan
    INPUT booking.namaRuang
    INPUT booking.kapasitasRuang
    INPUT booking.jumlahPeserta
    INPUT booking.durasiMenit

    IF booking.jumlahPeserta >= 20 THEN
        booking.prioritas = "Tinggi"
    ELSE
        booking.prioritas = "Normal"
    ENDIF

    TAMBAHKAN booking KE daftarPemesanan
    DISPLAY "Data pemesanan berhasil ditambahkan."
    CALL CekKapasitasDanPrioritas(booking.kapasitasRuang,
                                  booking.jumlahPeserta)
ENDPROCEDURE
```

## Mengecek kapasitas dan prioritas

```text
PROCEDURE CekKapasitasDanPrioritas(kapasitas, jumlahPeserta)
BEGIN
    IF jumlahPeserta > kapasitas THEN
        DISPLAY "Status: Permintaan melebihi kapasitas!"
    ELSE
        DISPLAY "Status: Kapasitas mencukupi."
    ENDIF

    IF jumlahPeserta >= 20 THEN
        DISPLAY "Prioritas: Tinggi (Kegiatan Besar)"
    ELSE
        DISPLAY "Prioritas: Normal"
    ENDIF
ENDPROCEDURE
```

## Menampilkan seluruh pemesanan

```text
PROCEDURE TampilkanData(daftarPemesanan)
BEGIN
    IF daftarPemesanan.SIZE == 0 THEN
        DISPLAY "Data masih kosong!"
        RETURN
    ENDIF

    FOR i FROM 0 TO daftarPemesanan.SIZE - 1 DO
        DISPLAY "Data ke-", i + 1
        DISPLAY daftarPemesanan[i].idPemesanan
        DISPLAY daftarPemesanan[i].namaPemesan
        DISPLAY daftarPemesanan[i].namaRuang
        DISPLAY daftarPemesanan[i].kapasitasRuang
        DISPLAY daftarPemesanan[i].jumlahPeserta
        DISPLAY daftarPemesanan[i].durasiMenit
        DISPLAY daftarPemesanan[i].prioritas
    ENDFOR
ENDPROCEDURE
```

## Menghitung total durasi secara rekursif

```text
FUNCTION HitungTotalDurasiRekursif(daftarPemesanan, n) RETURNS INTEGER
BEGIN
    IF n <= 0 THEN
        RETURN 0
    ELSE
        RETURN daftarPemesanan[n - 1].durasiMenit
               + HitungTotalDurasiRekursif(daftarPemesanan, n - 1)
    ENDIF
ENDFUNCTION
```

## Menghitung statistik

```text
PROCEDURE HitungStatistik(daftarPemesanan)
BEGIN
    jumlahData = daftarPemesanan.SIZE

    IF jumlahData == 0 THEN
        DISPLAY "Data masih kosong!"
        RETURN
    ENDIF

    totalDurasi = HitungTotalDurasiRekursif(daftarPemesanan, jumlahData)
    rataRata = totalDurasi / jumlahData
    maxDurasi = daftarPemesanan[0].durasiMenit
    minDurasi = daftarPemesanan[0].durasiMenit

    FOR i FROM 1 TO jumlahData - 1 DO
        IF daftarPemesanan[i].durasiMenit > maxDurasi THEN
            maxDurasi = daftarPemesanan[i].durasiMenit
        ENDIF
        IF daftarPemesanan[i].durasiMenit < minDurasi THEN
            minDurasi = daftarPemesanan[i].durasiMenit
        ENDIF
    ENDFOR

    DISPLAY "Total Durasi (Rekursif): ", totalDurasi, " menit"
    DISPLAY "Rata-rata Durasi: ", rataRata, " menit"
    DISPLAY "Durasi Tertinggi: ", maxDurasi, " menit"
    DISPLAY "Durasi Terendah: ", minDurasi, " menit"
ENDPROCEDURE
```

## Mengurutkan pemesanan dengan Bubble Sort

```text
PROCEDURE BubbleSortDurasi(daftarPemesanan)
BEGIN
    jumlahData = daftarPemesanan.SIZE

    FOR i FROM 0 TO jumlahData - 2 DO
        FOR j FROM 0 TO jumlahData - i - 2 DO
            IF daftarPemesanan[j].durasiMenit
               > daftarPemesanan[j + 1].durasiMenit THEN
                SWAP daftarPemesanan[j] WITH daftarPemesanan[j + 1]
            ENDIF
        ENDFOR
    ENDFOR

    DISPLAY "Data berhasil diurutkan berdasarkan durasi."
ENDPROCEDURE
```

## Mencari pemesanan dengan Linear Search

```text
PROCEDURE LinearSearchID(daftarPemesanan, targetID)
BEGIN
    FOR i FROM 0 TO daftarPemesanan.SIZE - 1 DO
        IF daftarPemesanan[i].idPemesanan == targetID THEN
            DISPLAY "Data ditemukan di indeks: ", i
            DISPLAY "ID pemesanan: ", daftarPemesanan[i].idPemesanan
            DISPLAY "Nama pemesan: ", daftarPemesanan[i].namaPemesan
            DISPLAY "Nama ruang: ", daftarPemesanan[i].namaRuang
            DISPLAY "Durasi: ", daftarPemesanan[i].durasiMenit, " menit"
            RETURN
        ENDIF
    ENDFOR

    DISPLAY "Data tidak ditemukan!"
ENDPROCEDURE
```
