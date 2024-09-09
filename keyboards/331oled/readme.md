# 331oled

[QMK Docs](https://docs.qmk.fm/newbs)

1. Activate QMK pyenv
2. Compile
3. Flash onto RP2040 by holding the boot button then press the reset button then let go of reset.
4. Drop the .uf2 file into the board's directory

``` sh
# Compile
qmk compile -c -kb 331oled -km default
```
