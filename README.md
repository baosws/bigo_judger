# Tool chấm offline cho Big-O Coding.

Tool này hiện đã được test trên Ubuntu 18.04 và Ubuntu trên Windows 10.

## Cần cài thêm gì để xài:
- make
- g++
- java
```
sudo apt update
sudo apt upgrade
sudo apt install make g++ default-jdk
```
Với **Windows** cần cài Ubuntu (app Ubuntu thôi chứ không phải nguyên cái hệ điều hành nha) trước rồi cài thêm mấy cái ở trên.

## Cài tool
```
make
make install
```

## Sử dụng

### Đầu tiên di chuyển vào thư mục chứa sol các thứ (không cần cũng được, nhưng lát hồi sẽ phải nhập địa chỉ solution với test dài hơn).
Ví dụ cần chấm bài Chores buổi Sorting Blue ở *Dropbox/TA Big-O Orange/BigO_Orange_Lecture11_DP_LCS (Part II)/4. Advanced Fruits - SPOJ (BTVN Bai 1)*
- Ubuntu:
```
cd ~/"Dropbox/TA Big-O Orange/BigO_Orange_Lecture11_DP_LCS (Part II)/4. Advanced Fruits - SPOJ (BTVN Bai 1)"
```
- Windows: Dropbox nằm ở */mnt/c/Users/<tên User>/Dropbox* nên phải thêm cái đó vào đầu:
```
cd "/mnt/c/Users/Bao/Dropbox/TA Big-O Orange/BigO_Orange_Lecture11_DP_LCS (Part II)/4. Advanced Fruits - SPOJ (BTVN Bai 1)"
```

### Chấm thôi. Bước này tùy điều kiện mà làm khác nhau.
Trong folder này có 3 solution là  *Solution_AC.cpp, Solution_AC.java, Solution_AC.py*. Thư mục test tên là *data* (mặc định các cặp input, answer có đuôi là *in* và *ans*). Checker tên là *checker.cpp*:

- Chấm *Solution_AC.cpp*:
```
judge Solution_AC.cpp -T tests
```

- Chấm cả 3 sol trên:

```
judge Solution* -T data
```

- Chấm thêm time limit 0.5s:

```
judge Solution.* -T data -t 0.5
```

- Chấm với checker:

```
judge Solution.* -T data -C checker.cpp
```

### Các option nhảm nhí khác:
Có thể coi help bằng:

```
judge -h
```

| Option | Ý nghĩa |
|--------|---------|
|-d| Xem output sai gì so với đáp án/checker (mặc định thì không cho xem) |
|-c| Xem compilation errors |
|-r| Xem runtime errors |
|-I arg| Nếu input không có đuôi mặc định là *in* thì thêm cái này. Ví dụ '-I inp' |
|-A arg| Nếu answer không có đuôi mặc định là *ans* thì thêm cái này. Ví dụ '-A out' |
|-O options | Option cho checker |
