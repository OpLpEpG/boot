# boot
bootloader
## board:
```
bluepill
```
## targets:
```
guiconfig - setup project, drivers 
```
## memory:
```
0x0800 0000- begin Bootloader
                    Bootloader 
0x0800 0BFF- end Bootloader
0x0800 0C00- begin User Consts
                    User Consts
0x0800 0FFF- end User Consts
0x0800 1000- begin Programm
                    Programm
0x0801 FFFF- end   Programm

```
