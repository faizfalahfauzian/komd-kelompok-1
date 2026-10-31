    // Declaration //

STRUCTURE Booking 
    idPemesanan : STRING / INTEGER 
    namaPemesan : STRING 
    namaRuang : STRING kapasitas : INTEGER 
    jumlahPeserta: INTEGER 
    durasi : INTEGER (menit) 
    prioritas : STRING / INTEGER 
 ENDSTRUCTURE 
    
  DECLARE daftarPemesanan AS ARRAY OF Booking 
  DECLARE jumlahData AS INTEGER = 0

      // Main Algorithm //

PROGRAM MainMenu 
BEGIN 
  DECLARE pilihan AS INTEGER 
  REPEAT 
      DISPLAY "=== SMART CAMPUS BOOKING SYSTEM ===" 
      DISPLAY "1\. Tambah Data Pemesanan" 
      DISPLAY "2\. Tampilkan Semua Pemesanan" 
      DISPLAY "3\. Hitung Statistik & Rekursif Durasi" 
      DISPLAY "4\. Urutkan Pemesanan (Sorting Manual)" 
      DISPLAY "5\. Cari Pemesanan (Searching Manual)" 
      DISPLAY "6\. Keluar" 
      INPUT pilihan 
                                                                                                                      //
      SWITCH pilihan 
          CASE 1: CALL TambahPemesanan() 
          CASE 2: CALL TampilkanData() 
          CASE 3: CALL HitungStatistik() 
          CASE 4: CALL SortingData() 
          CASE 5: CALL SearchingData() 
          CASE 6: DISPLAY "Terima kasih!" 
          DEFAULT: DISPLAY "Pilihan tidak valid!" 
      ENDSWITCH 
  UNTIL pilihan == 6 
  END


      //  Fungsi Pengecekan Kapasitas dan Prioritas //
    
  PROCEDURE CekKapasitasDanPrioritas(kapasitas, jumlahPeserta) 
  BEGIN 
      IF jumlahPeserta > kapasitas THEN 
          DISPLAY "Status: Permintaan melebihi kapasitas!" 
      ELSE 
          DISPLAY "Status: Kapasitas mencukupi." 
      ENDIF 
                                                                                                                      //
      IF jumlahPeserta >= 20 THEN
          DISPLAY "Prioritas: Tinggi (Kegiatan Besar)" 
      ELSE 
          DISPLAY "Prioritas: Normal" 
      ENDIF 
  ENDPROCEDURE

      // Fungsi Hitung Total Durasi (Fungsi Rekursif) //

  FUNCTION HitungTotalDurasiRekursif(n) RETURNS INTEGER 
  BEGIN 
      // Base case 
      IF n <= 0 THEN 
          RETURN 0
      ELSE 
          // Recursive step 
          RETURN daftarPemesanan[n-1].durasi + HitungTotalDurasiRekursif(n - 1) 
      ENDIF 
  ENDFUNCTION

      // Fungsi Perhitungan Statistik //

  PROCEDURE HitungStatistik() 
  BEGIN 
      IF jumlahData == 0 THEN 
          DISPLAY "Data masih kosong!" RETURN 
      ENDIF 
                                                                                                                      //
      DECLARE totalDurasi AS INTEGER 
      totalDurasi = HitungTotalDurasiRekursif(jumlahData) 
      DECLARE rataRata AS FLOAT = totalDurasi / jumlahData 
                                                                                                                      //
      DECLARE maxDurasi AS INTEGER = daftarPemesanan.durasi 
      DECLARE minDurasi AS INTEGER = daftarPemesanan.durasi 
                                                                                                                      //
      FOR i FROM 1 TO jumlahData - 1 DO 
          IF daftarPemesanan[i].durasi &gt; maxDurasi THEN 
              maxDurasi = daftarPemesanan[i].durasi 
          ENDIF 
          IF daftarPemesanan[i].durasi &lt; minDurasi THEN 
          minDurasi = daftarPemesanan[i].durasi 
          ENDIF 
      ENDFOR 
                                                                                              //                         
      DISPLAY "Total Durasi (Rekursif): ", totalDurasi 
      DISPLAY "Rata-rata Durasi: ", rataRata 
      DISPLAY "Durasi Tertinggi: ", maxDurasi 
      DISPLAY "Durasi Terendah: ", minDurasi 
  ENDPROCEDURE

        // Fungsi Sorting Manual (Bubble Sort - Berdasarkan Durasi) //

  PROCEDURE BubbleSortDurasi() 
  BEGIN 
      FOR i FROM 0 TO jumlahData - 2 DO 
          FOR j FROM 0 TO jumlahData - i - 2 DO 
              IF daftarPemesanan[j].durasi > daftarPemesanan[j+1].durasi THEN 
                  SWAP daftarPemesanan[j] WITH daftarPemesanan[j+1] 
              ENDIF 
          ENDFOR 
      ENDFOR 
      DISPLAY "Data berhasil diurutkan berdasarkan durasi." 
  ENDPROCEDURE

      // Fungsi Searching Manual (Linear Search - ID Pemesanan) //
      
PROCEDURE LinearSearchID(targetID) 
BEGIN 
    DECLARE ketemu AS BOOLEAN = FALSE 
    FOR i FROM 0 TO jumlahData - 1 DO 
       IF daftarPemesanan[i].idPemesanan == targetID THEN 
          DISPLAY "Data Ditemukan di indeks: ", i 
          DISPLAY "Nama Pemesan: ", daftarPemesanan[i].namaPemesan 
          ketemu = TRUE 
          BREAK 
        ENDIF 
    ENDFOR 
                                                                                                                      //
    IF NOT ketemu THEN 
        DISPLAY "Data tidak ditemukan!" 
    ENDIF 
ENDPROCEDURE
  

  

  
