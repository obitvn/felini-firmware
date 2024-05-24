
https://www.yii666.com/blog/318106.html
https://www.bilibili.com/video/BV17V4y1Z7dg/?spm_id_from=333.999.0.0

Cài các plugin VSCode sau
![[../Linux Embedded/image/Pasted image 20230510092356.png]]

Sau đó, tải và cài [mysys2](https://www.msys2.org/)
![[../Linux Embedded/image/Pasted image 20230516113027.png]]

add mysys 2 vào path, gồm 2 cái sau
![[../Linux Embedded/image/Pasted image 20230510143616.png]]

![[../Linux Embedded/image/Pasted image 20230510143624.png]]
**Tìm " MSYS2 MSYS** " từ thanh menu Start và chạy
![[../Linux Embedded/image/Pasted image 20230510143650.png]]
Sau đó chạy lần lượt các lệnh dưới đây
```
pacman -Syu
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-gdb mingw-w64-x86_64-cmake mingw-w64-x86_64-make
pacman -S mingw-w64-x86_64-toolchain
pacman -S mingw-w64-x86_64-clang
pacman -S mingw-w64-x86_64-yasm mingw-w64-x86_64-nasm
pacman -S mingw-w64-x86_64-freetype
```
Nếu bạn gặp các lời nhắc sau trong quá trình cài đặt, hãy nhấn Enter để cài đặt tất cả

```c
Enter a selection (default=all):
```

Nếu bạn gặp các lời nhắc sau trong quá trình cài đặt, hãy nhập "Y" để tiếp tục cài đặt

```c
:: Proceed with installation? [Y/n]
```

**Sau khi hoàn tất cài đặt, chạy " MSYS MinGW x64** " từ menu Start . Bây giờ bạn có thể gọi make hoặc gcc để xây dựng phần mềm cho Windows.
![[../Linux Embedded/image/Pasted image 20230510143836.png]]
Xác minh môi trường

```c
gcc --version
```
![[../Linux Embedded/image/Pasted image 20230510143859.png]]

Tải [SDL2-devel-2.26.5-mingw.zip](https://github.com/libsdl-org/SDL/releases/download/release-2.26.5/SDL2-devel-2.26.5-mingw.zip)
sau đó copy include, lib vào folder của mysys (Để fix lỗi thiếu sdl2)
![[../Linux Embedded/image/Pasted image 20230516132311.png]]
![[../Linux Embedded/image/Pasted image 20230516132342.png]]