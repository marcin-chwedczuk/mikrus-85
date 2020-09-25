#!/bin/bash

shopt -s expand_aliases  # Enables alias expansion.

alias as8085=/Users/mc/devel/git/asXXXX/asxv5pxx/asxmak/linux/exe/as8085
alias aslink=/Users/mc/devel/git/asXXXX/asxv5pxx/asxmak/linux/exe/aslink
alias scc8080=/Users/mc/devel/git/SmallC-85/smallC/scc8080

rm *.hlr *.lst *.rel *.sym *.ihx *.bin

scc8080 -t -a main.c && \
  as8085 -gloaxsff main.s && \
  as8085 -gloaxsff cstart.asm && \
  aslink -f eeprom || exit 1

echo "BUILDING DONE."

export PATH="/usr/local/opt/binutils/bin:$PATH"
gobjcopy --input-target=ihex --output-target=binary eeprom-img.ihx eeprom-img.bin

echo "CREATING BIN FILE DONE."
