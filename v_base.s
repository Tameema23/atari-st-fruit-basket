        xdef	_set_video_base_asm

_set_video_base_asm:
        move.l 4(sp),d0          ; Load base address from stack
        move.b d0,$ffff8203      ; Mid byte (bits 8–15)
        swap d0                   ; Move high word to low word
        move.b d0,$ffff8201      ; High byte (bits 16–23)
        rts
