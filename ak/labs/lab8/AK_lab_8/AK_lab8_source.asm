.586P

.model FLAT, STDCALL

.data

const1  DD  7.0
const2  DD  39.0
const3  DD  3.4
const4  DD  8.5
const5  DD  9.4
const6  DD  3.8

varA    DD  7.1
varC    DD  5.2
varD    DD  1.6

answer  DD  7.0

.code
START:
    finit               ; initialize the FPU

    fld     [varC]
    fmul    [const1]    ; 7 * c

    fld     [varA]
    fmul    [varC]      ; a * c

    fsincos
    fdivp               ; tg(a * c)

    fld     [const2]    ; 39
    fmul    [varD]      ; 39 * d
    fld     [const3]    ; 3.4
    fsubp               ;
    fsqrt               ; sqrt (39 * d - 3.4)

    faddp
    faddp               ; numerator on top

    fld     [varC]
    fmul    [const4]    ; c * 8.5

    fld     [varC]
    fdiv    [const5]    ; c / 9.4

    fsubp               ; c * 8.5 - c / 9.4

    fld     [varD]
    fmul    [const6]    ; 3.8 * d

    faddp               ; denominator on top

    fdivp
    fst     [answer]

    lea EBX, answer

    RET

END START