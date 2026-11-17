# Pseudocode — Smart Campus Booking System UGM

> Source: `main.cpp`
> Conventions: `←` is assignment, `//` is a comment. String literals such as `"Rendah"` / `"Sedang"` / `"Tinggi"` are kept exactly as they appear in the program (Low / Medium / High).

---

## 1. Constants and Data Structure

```
CONSTANT MAX ← 100                       // maximum number of records per array

STRUCTURE Booking
    bookerName   : STRING
    ID           : STRING                // e.g. "00001", or "OV-00001" for rejected logs
    roomID       : INTEGER               // 1..7
    roomName     : STRING
    roomCapacity : INTEGER
    memberCount  : INTEGER
    duration     : INTEGER               // minutes
    priority     : STRING                // "Rendah" | "Sedang" | "Tinggi" | "-"
    purpose      : STRING
    capacityOK   : BOOLEAN
END STRUCTURE
```

---

## 2. Helper Functions

### 2.1 Generate Booking ID

```
FUNCTION generateBookingID(count) RETURNS STRING
    number ← count + 1
    RETURN number written with width 5, left-padded with '0'
           // 1 → "00001", 12 → "00012"
END FUNCTION
```

### 2.2 Determine Priority from Duration

```
FUNCTION determinePriority(duration) RETURNS STRING
    IF duration < 20 THEN
        RETURN "Rendah"
    ELSE IF duration <= 60 THEN
        RETURN "Sedang"
    ELSE
        RETURN "Tinggi"
    END IF
END FUNCTION
```

### 2.3 Priority Score (used for sorting)

```
FUNCTION priorityScore(priority) RETURNS INTEGER
    IF priority = "Tinggi" THEN RETURN 3
    IF priority = "Sedang" THEN RETURN 2
    RETURN 1                             // "Rendah" or anything else
END FUNCTION
```

---

## 3. Add Booking (Menu 1)

```
PROCEDURE addBooking(bookings, count, MAX, overLog, overCount)
    // count and overCount are passed BY REFERENCE (changes persist)

    IF count >= MAX THEN
        DISPLAY "Cannot accept booking, maximum capacity reached"
        RETURN
    END IF

    roomNames      ← ["Ruang Diskusi 1", "Ruang Diskusi 2", "Ruang Diskusi 3",
                      "Ruang Creative 1", "Aula Utama", "Ruang Creative 2", "Ruang Rapat"]
    roomCapacities ← [10, 20, 25, 35, 100, 40, 30]

    // --- Step 1: booker name ---
    DISPLAY "Nama Pemesan: "
    DISCARD leftover characters up to and including newline in input buffer
    READ whole line INTO bookings[count].bookerName

    // --- Step 2: ID ---
    bookings[count].ID ← generateBookingID(count)

    // --- Step 3: choose room ---
    DISPLAY "Pilihan ruangan:"
    FOR i FROM 0 TO 6 DO
        DISPLAY (i + 1), roomNames[i], roomCapacities[i]
    END FOR
    DISPLAY "Pilih ruangan (1-7): "
    READ choice

    IF choice < 1 OR choice > 7 THEN
        CLEAR input error state
        DISCARD rest of the input line
        DISPLAY "Pilihan ruangan tidak valid."
        RETURN
    END IF

    bookings[count].roomID       ← choice
    bookings[count].roomName     ← roomNames[choice - 1]
    bookings[count].roomCapacity ← roomCapacities[choice - 1]

    // --- Step 4: member count + capacity check ---
    DISPLAY "Jumlah anggota: "
    READ bookings[count].memberCount
    DISCARD rest of the input line

    bookings[count].capacityOK ← (bookings[count].memberCount <= bookings[count].roomCapacity)

    IF NOT bookings[count].capacityOK THEN
        DISPLAY ERROR "Booking rejected: member count exceeds room capacity"

        IF overCount < MAX THEN
            overLog[overCount]          ← COPY of bookings[count]
            overLog[overCount].ID       ← "OV-" + generateBookingID(overCount)
            overLog[overCount].duration ← 0
            overLog[overCount].priority ← "-"
            overLog[overCount].purpose  ← "Ditolak (Over Capacity)"
            overCount ← overCount + 1
            DISPLAY "Over-capacity attempt has been logged"
        END IF

        RETURN                           // count is NOT incremented
    END IF

    // --- Step 5: duration, priority, purpose ---
    DISPLAY "Durasi pemesanan (menit): "
    READ bookings[count].duration
    DISCARD rest of the input line

    bookings[count].priority ← determinePriority(bookings[count].duration)

    DISPLAY "Kegunaan/keperluan pemesanan: "
    READ whole line INTO bookings[count].purpose

    DISPLAY "Booking accepted. ID:", bookings[count].ID,
            "Priority:", bookings[count].priority

    count ← count + 1                    // booking is now officially stored
END PROCEDURE
```

---

## 4. Display All Bookings (Menu 2) — inside `main`

```
IF count = 0 THEN
    DISPLAY "Belum ada pemesanan yang terdaftar."
END IF

FOR i FROM 0 TO count - 1 DO
    DISPLAY ID, bookerName, roomName, memberCount, duration, priority, purpose
    IF bookings[i].capacityOK THEN
        DISPLAY "Kapasitas: mencukupi"
    ELSE
        DISPLAY "Kapasitas: tidak mencukupi"
    END IF
END FOR
```

---

## 5. Linear Search by ID (Menu 3)

```
PROCEDURE linearSearchID(bookings, count, targetID)
    FOR i FROM 0 TO count - 1 DO
        IF bookings[i].ID = targetID THEN
            DISPLAY "Data found at index:", i
            DISPLAY ID, bookerName, roomName, duration, priority, purpose
            RETURN
        END IF
    END FOR

    DISPLAY "Data tidak ditemukan!"
END PROCEDURE
```

---

## 6. Sort Queue per Room (Menu 4)

### 6.1 Sort procedure (Bubble Sort with 3-level comparison)

```
PROCEDURE sortQueuePerRoom(bookings, count)
    IF count = 0 THEN
        DISPLAY "Data masih kosong!"
        RETURN
    END IF

    FOR i FROM 0 TO count - 2 DO
        FOR j FROM 0 TO count - i - 2 DO
            needSwap ← FALSE

            IF bookings[j].roomID > bookings[j+1].roomID THEN
                needSwap ← TRUE                                   // level 1: room ascending

            ELSE IF bookings[j].roomID = bookings[j+1].roomID THEN
                scoreA ← priorityScore(bookings[j].priority)
                scoreB ← priorityScore(bookings[j+1].priority)

                IF scoreA < scoreB THEN
                    needSwap ← TRUE                               // level 2: higher priority first
                ELSE IF scoreA = scoreB AND bookings[j].ID > bookings[j+1].ID THEN
                    needSwap ← TRUE                               // level 3: older ID first (FIFO)
                END IF
            END IF

            IF needSwap THEN
                temp           ← bookings[j]
                bookings[j]    ← bookings[j+1]
                bookings[j+1]  ← temp
            END IF
        END FOR
    END FOR

    DISPLAY "Data sorted by room queue (High -> Low priority)"
    displayQueuePerRoom(bookings, count)
END PROCEDURE
```

### 6.2 Display the queue (expects sorted data)

```
PROCEDURE displayQueuePerRoom(bookings, count)
    activeRoom  ← -1
    queueNumber ← 1

    FOR i FROM 0 TO count - 1 DO
        IF bookings[i].roomID ≠ activeRoom THEN       // a new room group starts
            activeRoom  ← bookings[i].roomID
            queueNumber ← 1
            DISPLAY "=== ", bookings[i].roomName, " ==="
        END IF

        DISPLAY "Antrian ke-", queueNumber, "(ID:", bookings[i].ID, ")"
        DISPLAY bookerName, priority, duration, memberCount, purpose
        queueNumber ← queueNumber + 1
    END FOR
END PROCEDURE
```

---

## 7. Duration Statistics (Menu 5)

### 7.1 Total duration — RECURSIVE

```
FUNCTION calcTotalDuration(bookings, n) RETURNS INTEGER
    IF n <= 0 THEN                                    // base case
        RETURN 0
    END IF
    RETURN bookings[n - 1].duration + calcTotalDuration(bookings, n - 1)
END FUNCTION
```

### 7.2 Average duration

```
FUNCTION calcAverageDuration(bookings, n) RETURNS REAL
    IF n <= 0 THEN RETURN 0.0
    RETURN (REAL) calcTotalDuration(bookings, n) / n
END FUNCTION
```

### 7.3 Maximum and minimum duration — ITERATIVE

```
FUNCTION calcMaxDuration(bookings, n) RETURNS INTEGER
    IF n <= 0 THEN RETURN 0
    maxVal ← bookings[0].duration
    FOR i FROM 1 TO n - 1 DO
        IF bookings[i].duration > maxVal THEN
            maxVal ← bookings[i].duration
        END IF
    END FOR
    RETURN maxVal
END FUNCTION

FUNCTION calcMinDuration(bookings, n) RETURNS INTEGER
    IF n <= 0 THEN RETURN 0
    minVal ← bookings[0].duration
    FOR i FROM 1 TO n - 1 DO
        IF bookings[i].duration < minVal THEN
            minVal ← bookings[i].duration
        END IF
    END FOR
    RETURN minVal
END FUNCTION
```

### 7.4 Display statistics

```
PROCEDURE displayStatistics(bookings, count)
    IF count <= 0 THEN
        DISPLAY "Belum ada data pemesanan apapun."
        RETURN
    END IF

    DISPLAY "Total Durasi      :", calcTotalDuration(bookings, count), "Menit"
    DISPLAY "Rata Rata Durasi  :", calcAverageDuration(bookings, count), "Menit"
    DISPLAY "Durasi Tertinggi  :", calcMaxDuration(bookings, count), "Menit"
    DISPLAY "Durasi Terendah   :", calcMinDuration(bookings, count), "Menit"
END PROCEDURE
```

---

## 8. Display Over-Capacity Log (Menu 6)

```
PROCEDURE displayOverCapacity(overLog, overCount)
    DISPLAY header

    IF overCount = 0 THEN
        DISPLAY "Belum ada data pemesanan yang melebihi kapasitas."
        RETURN
    END IF

    FOR i FROM 0 TO overCount - 1 DO
        excess ← overLog[i].memberCount - overLog[i].roomCapacity
        DISPLAY "Data ke-", i + 1
        DISPLAY overLog[i].ID, bookerName, roomName, roomCapacity
        DISPLAY memberCount, "(Kelebihan", excess, "orang)"
        DISPLAY overLog[i].purpose                    // "Ditolak (Over Capacity)"
    END FOR
END PROCEDURE
```

---

## 9. Main Program

```
PROCEDURE main
    bookings ← ARRAY[MAX] OF Booking
    overLog  ← ARRAY[MAX] OF Booking
    count      ← 0
    overCount  ← 0
    choice     ← 0

    REPEAT
        DISPLAY main menu (options 1 to 7)
        DISPLAY "Pilih (1-7): "

        READ choice
        IF reading failed (input is not a number) THEN
            CLEAR input error state
            DISCARD rest of the input line
            DISPLAY "Input harus berupa angka! Silakan coba lagi."
            CONTINUE                                  // jumps to the UNTIL check
        END IF

        CASE choice OF
            1 : addBooking(bookings, count, MAX, overLog, overCount)
            2 : display all bookings                  // see section 4
            3 : READ targetID
                linearSearchID(bookings, count, targetID)
            4 : sortQueuePerRoom(bookings, count)
            5 : displayStatistics(bookings, count)
            6 : displayOverCapacity(overLog, overCount)
            7 : DISPLAY farewell message
            OTHERWISE : DISPLAY "Pilihan tidak valid."
        END CASE

    UNTIL choice = 7
END PROCEDURE
```
