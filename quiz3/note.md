# 2020q3 Homework3 (quiz3)
contributed by < ``yceugene`` >

## 1.有號整數的跨平台 ASR 實作
```c
int asr_i(signed int m, unsigned int n)
{
    const int logical = (((int) -1) OP1) > 0;
    unsigned int fixu = -(logical & (OP2));
    int fix = *(int *) &fixu;
    return (m >> n) | (fix ^ (fix >> n));
}
```

* 第 1 行是為了判斷編譯器的右移型態, 已知 -1 的二補數表示為 ``0xFFFFFFFF`` ，若``0xFFFFFFFF``在右移後得到正數，表示編譯器為邏輯右移（最高位補 0）；反之則為算術右移（符號位元右移），而位移結果的正負號判斷就是和 0 比大小，因此 ``OP1 = >>1``。（logical = 0 或 1 代表編譯器為邏輯右移或算術右移）
* 第 ２ 行是為了判斷 m 的正負號，只有當 m 為負數時才需考慮位移的正確性（正數位移，兩種右移型態都會從最高位元補 0，不影響結果正確性）。


    | 右移型態 | m 的正負號| 正確性 |
    | -------- | -------- | -------- |
    | 邏輯右移，即 ``logical==1`` | ``(m < 0)==1 `` | 錯誤|
    | 邏輯右移，即 ``logical==1`` | ``(m < 0)==0`` | 正確|
    | 算術右移，即 ``logical==0`` | ``(m < 0)==1`` | 正確 |
    | 算術右移，即 ``logical==0`` | ``(m < 0)==0`` | 正確 |

    由上表可知，我們只需要考慮邏輯右移且 ``m < 0`` 的情況，在此種情況下 ``fixu == 0xFFFFFFFF``, 其他三種情況下 ``fixu == 0x00000000``
* 第 3 行 ``int fix = *(int *) &fixu;`` 是將 fluxu 無號數）轉為 flux(有號數)
* 第 4 行是為了針對上述錯誤情況（負數的邏輯位移）做修正，從最高位元開始，將補 0 的位元全部改為 1。
* 解答：
    ``OP1 = >>1``
    ``OP2 = （m < 0）``

## 2.實作 Power of Four 的判斷
```c
bool isPowerOfFour(int num)
{
    return num > 0 && (num & (num - 1))==0 &&
           !(__builtin_ctz(num) OPQ);
}
```
想法： 若一個數字 num 為 4 的冪次方，則其二進制表示式中會有以下特性：
* 由於 num 必為 2 的冪次方，因此其二進制中恰有 1 個位元值為 1，其餘位元值為 0，而``(num & (num - 1))==0`` 就是用來判斷這個條件。
* num 的二進制中，位元值為 1 的位元，從該位元由其右邊一個 bit 一路向右延伸到底，一共會經過偶數個值為 0 的 bit，而 ``（__builtin_ctz(num) = & 0x1）`` 就是用來判斷 num 二進制式末尾是否有偶數個值為 0 的 bit。

* 解答：
    * ``OPQ = & 0x1``
## 3.population count
```
int numberOfSteps (int num)
{
    return num ? AAA + 31 - BBB : 0;
}
```
