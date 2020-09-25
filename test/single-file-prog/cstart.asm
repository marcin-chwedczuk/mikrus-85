;       Run time start off for Small C.
;        cseg
        .module CSTART
        .area   CSTART (REL,CON) ;program area CRTSO is RELOCATABLE
        .list   (err, loc, bin, eqt, cyc, lin, src, lst, md)
        .nlist  (pag)
        .globl  cstartend
	;.globl 	cceq, ccgchar, cccmp

	lxi h,#0x3ffe ; Initialize stack on even address.
		      ; Stack grows downwards.
        sphl

        call    main    ; call main program

stop:
	hlt ; stop processor
	jmp stop

; fetch char from (HL) and sign extend into HL
ccgchar: mov     a,m
ccsxt:  mov     l,a
        rlc
        sbb     a
        mov     h,a
        ret

; DE == HL
;cceq:   call    cccmp
;        rz
;        dcx     h
;        ret
;
; signed compare of DE and HL
;   carry is sign of difference [set => DE < HL]
;   zero is zero/non-zero
cccmp:  mov     a,e
        sub     l
        mov     e,a
        mov     a,d
        sbb     h
        lxi     h,1             ;preset true
        jm      cccmp1
        ora     e               ;resets carry
        ret
;
cccmp1: ora     e
        stc
        ret

; store int from HL into (DE)
ccpint: mov     a,l
        stax    d
        inx     d
        mov     a,h
        stax    d
        ret

; fetch int from (HL)
ccgint: mov     a,m
        inx     h
        mov     h,m
        mov     l,a
        ret
;

; DE < HL [signed]
cclt:   call    cccmp
        rc
        dcx     h
        ret


; shift DE left arithmetically by HL, move to HL
ccasl:  xchg
ccasl1: dcr     e
        rm
        dad     h
        jmp     ccasl1

; "or" HL and DE into HL
ccor:   mov     a,l
        ora     e
        mov     l,a
        mov     a,h
        ora     d
        mov     h,a
        ret

; {DE = -DE}
ccdeneg:
        mov     a,d
        cma
        mov     d,a
        mov     a,e
        cma
        mov     e,a
        inx     d
        ret
; {BC = -BC}
ccbcneg:
        mov     a,b
        cma
        mov     b,a
        mov     a,c
        cma
        mov     c,a
        inx     b
        ret

; HL = DE / HL, DE = DE % HL
ccdiv:  mov     b,h
        mov     c,l
        mov     a,d
        xra     b
        push    psw
        mov     a,d
        ora     a
        cm      ccdeneg
        mov     a,b
        ora     a
        cm      ccbcneg
        mvi     a,16
        push    psw
        xchg
        lxi     d,0
ccdiv1: dad     h
        call    ccrdel
        jz      ccdiv2
        call    cccmpbd
        jm      ccdiv2
        mov     a,l
        ori     1
        mov     l,a
        mov     a,e
        sub     c
        mov     e,a
        mov     a,d
        sbb     b
        mov     d,a
ccdiv2: pop     psw
        dcr     a
        jz      ccdiv3
        push    psw
        jmp     ccdiv1
ccdiv3: pop     psw
        rp
        call    ccdeneg
        xchg
        call    ccdeneg
        xchg
        ret

; HL = DE - HL
ccsub:  mov     a,e
        sub     l
        mov     l,a
        mov     a,d
        sbb     h
        mov     h,a
        ret

; DE > HL [signed]
ccgt:   xchg
        call    cccmp
        rc
        dcx     h
        ret

; "and" HL and DE into HL
ccand:  mov     a,l
        ana     e
        mov     l,a
        mov     a,h
        ana     d
        mov     h,a
        ret

; {BC : DE}
cccmpbd:
        mov     a,e
        sub     c
        mov     a,d
        sbb     b
        ret

; {DE <r<r 1}
ccrdel: mov     a,e
        ral
        mov     e,a
        mov     a,d
        ral
        mov     d,a
        ora     e
        ret

; DE <= HL [signed]
ccle:   call    cccmp
        rz
        rc
        dcx     h
        ret

cstartend:
       .end
