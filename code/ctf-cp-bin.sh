#!/bin/bash
echo "COPY CTF BINARY TO LIBRARY AFTER COMPILE"
REV01SRC="./_build/libraries/future_badge_ctf/future_badge_ctf.a"
REV01DST="./libraries/future_badge_ctf/src/esp32/libfuture_badge_ctf.a"
REV02SRC="./_build/libraries/future_badge_ctf_r2/future_badge_ctf_r2.a"
REV02DST="./libraries/future_badge_ctf_r2/src/esp32/libfuture_badge_ctf_r2.a"
if test -f "$REV01SRC"; then
    echo "cp -f $REV01SRC $REV01DST"
    cp -f $REV01SRC $REV01DST
fi
if test -f "$REV02SRC"; then
    echo "cp -f $REV02SRC $REV02DST"
    cp -f $REV02SRC $REV02DST
fi
