.module count_bits_in_nibble

_count_bits_in_nibble::
        ld      hl,#2
        add     hl,sp
        ld      a,(hl)
        ld      l,#0
        rrca
        jr      NC, SKIP1
        inc     l
SKIP1:
        rrca
        jr      NC, SKIP2
        inc     l
SKIP2:
        rrca
        jr      NC, SKIP3
        inc     l
SKIP3:
        rrca
        ret NC
        inc     l
        ret
