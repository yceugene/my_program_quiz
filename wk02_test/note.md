# 2020q3 Homework2 (quiz2)
contributed by < ``yceugene`` >

## 1. ASCII 編碼
* 題意: 在明確界定 7 位元編碼的字元隸屬於 ASCII 的情況下，判斷指定的記憶體範圍內是否全是有效的 ASCII 字元。
* 觀念: 只需要判斷數值大小範圍是否藉於: 0~127，(若超過就不是有效的 ASCII 字元)。
* 完整 ASCII table 可參考: [ASCII Code - The extended ASCII table](https://www.ascii-code.com/)、[ASCII table , ascii codes](https://theasciicode.com.ar/ascii-printable-characters/at-sign-atpersand-ascii-code-64.html)

範例程式 1: 輸入字串記憶體位址和字串長度，針對字串長度，透過迭代**依序比較每個字元**的數值大小。
``` c
#include <stddef.h>
bool is_ascii(const char str[], size_t size)
{
    if (size == 0)
        return false;
    for (int i = 0; i < size; i++)
        if (str[i] & 0x80) /* i.e. (unsigned) str[i] >= 128 */
            return false;
    return true;
}
```

範例程式 2: 較快的版本，作法和前一段程式類似，但改成: **每次處理 64 bits 的資料 (即 word size)**:

``` c
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
bool is_ascii(const char str[], size_t size)
{
    if (size == 0)
        return false;
    int i = 0;
    while ((i + 8) <= size) {
        uint64_t payload;
        memcpy(&payload, str + i, 8);
        if (payload & MMM)
            return false;
        i += 8;
    }
    while (i < size) {
        if (str[i] & 0x80)
            return false;
        i++;
    }
    return true;
}
```
* 這邊 ``MMM`` 應填上: ``0x8080808080808080``
* 觀念:
    * 在第一支程式碼中，是逐一比對每個 char ，看值的大小是否超出 128 的範圍: ``str[i] & 0x80`` 這行的作用是將 char 和 ``1000 0000(二進制)`` 做 ``AND`` 運算，意思就是只留下 char 的最高位元，其他部分都變為 0。
    * 新的程式碼要在允許情況下，一次比對 64 位元的資料，意思就是一次處理 8 個 char，套用上面的做法，程式會逐一將將每 8 個 char，一併和 ``0x8080808080808080`` 做 ``AND`` 運算。
    * 為何用到 memcpy?


## 2. 開發解析器 (parser)
* 題意: 以不使用分支的方式，將十六進位表示的字串轉為數值 (不區分大小寫)。例如 `0xF` (大寫 `F` 字元) 和 `0xf` (小寫 `f` 字元) 都該轉換為數值 `15`。
* 已知 `'in'` 一定隸屬於 \`0`\``, `1`, `2`, …, `9` 及 `a`, `b`, `c`, …, `f` (小寫) 及 `A`, `B`, `C`, …, `F` (大寫) 這些字元。預期 `hexchar2val('F')` 和 `hexchar2val('f')` 回傳 `15`，且 `hexchar2val('0')` 回傳 `0`，其他輸入都有對應的數值。
* 程式碼:
    ``` c
    uint8_t hexchar2val(uint8_t in)
    {
        const uint8_t letter = in & MASK;
        const uint8_t shift = (letter >> AAA) | (letter >> BBB);
        return (in + shift) & 0xf;
    }
    ```
* 作答:
    * MASK: 0x40 (用來保留字串的第 5 個 bit 的值)
    * AAA: 3 (結合 AAA 和 BBB 來計算出數值 9 或 0)
    * BBB: 6
* 觀察:
先觀察 **數字字串**、**小寫字母**和**大寫字母**的二進制表示，以及其轉換後數值的二進制表示:

| 數字字串   | 字串的 16 進制表示 | 字串的二進制表示| => | 轉換後的數值(二進制表示) |
| -------- | -------- | -------- | -------- | -------- |
| `'0'` | `0x30` | `0011 0000` | => | `0000` |
| `'1'` | `0x31` | `0011 0001` | => | `0001` |
| `'2'` | `0x32` | `0011 0002` | => | `0002` |
| `'3'` | `0x33` | `0011 0003` | => | `0003` |
| `'4'` | `0x34` | `0011 0004` | => | `0004` |
| `'5'` | `0x35` | `0011 0005` | => | `0005` |
| `'6'` | `0x36` | `0011 0006` | => | `0006` |
| `'7'` | `0x37` | `0011 0007` | => | `0007` |
| `'8'` | `0x38` | `0011 0008` | => | `0008` |
| `'9'` | `0x39` | `0011 0009` | => | `0009` |

| 小寫字母   | 16 進制表示 | 字串的二進制表示| => | 轉換後的數值(二進制表示) |
| -------- | -------- | -------- | -------- | -------- |
| `'a'` | `0x61` | `0110 0001` | => | `1010` |
| `'b'` | `0x62` | `0110 0002` | => | `1011` |
| `'c'` | `0x63` | `0110 0003` | => | `1100` |
| `'d'` | `0x64` | `0110 0004` | => | `1101` |
| `'e'` | `0x65` | `0110 0005` | => | `1110` |
| `'f'` | `0x66` | `0110 0006` | => | `1111` |

| 大寫字母   | 16 進制表示 | 字串的二進制表示| => | 轉換後的數值(二進制表示) |
| -------- | -------- | -------- | -------- | -------- |
| `'A'` | `0x41` | `0100 0001` | => | `1010` |
| `'B'` | `0x42` | `0100 0002` | => | `1011` |
| `'C'` | `0x43` | `0100 0003` | => | `1100` |
| `'D'` | `0x44` | `0100 0004` | => | `1101` |
| `'E'` | `0x45` | `0100 0005` | => | `1110` |
| `'F'` | `0x46` | `0100 0006` | => | `1111` |

* 歸納三種字串的轉換如下:
    * **數字字串**:
    轉二進制表示時，其右邊 4 個 bits 恰好就是最終轉換出的數值大小。

    * **小寫字母**
    轉二進制表示時，其右邊 4 個 bits 轉成數值後再加 `9`，恰好就是最終轉換出的數值大小。(另外左半邊 4 個 bits 全為 `0110`)

    * **大寫字母**:
    轉二進制表示時，其右邊 4 個 bits 轉成數值後再加 `9`，恰好就是最終轉換出的數值大小。(另外左半邊 4 個 bits 全為 `0100`)

* 分析:
    * 程式碼最後一行回傳 ``(in + shift) & 0xf``，表示回傳時只考慮了``in + shift`` 二進制中的右邊 4 個 bits，這代表 ``in + shift`` 的右半部即為最終數值的二進制表示。
    * 再搭配上述表格，我們可以如下分析:
        * 針對數值字串轉二進制時，我們只需要把數值字串的左半邊清除成 `0000`，即可得到結果。因次在處理數值字串時， `shift` 須為 `0000`，程式才會輸出正確結果。
        * 針對英文母轉二進制時，我們需要把字串右半部加上 `9`，左半邊清除成 `0000`，即可得到結果。因次在處理字母字串時，不論大寫或小寫字母， `shift` 都必須是 `1001`，程式才會輸出正確結果。(剩餘目標是思考如何讓 `shift` 為 `1001`)
    * 考慮大小寫問題: 根據上述表格我們觀察到 "小寫字母的二進制表示中，左半邊全為 `0110`； 大寫字母的二進制表示中，左半邊全為 `0100`。

* 搭配程式碼，整個轉換過程可以這樣理解:
    * 把字母都視為大寫: 因此在``letter = in & MASK`` 這一行裡，MASK 為 `0100 0000`。
    * 轉換字母字串時，``shift`` 要設為數值 9 (即 `1001`)；轉換數字字串時，``shift`` 要設為數值 `0` (即 `0000`)。因此在``shift = (letter >> AAA) | (letter >> BBB)``這一行中: AAA 和 BBB 必須為 `3` 和 `6`(順序顛倒也可以)。
    * 最後回傳數值時，只留下右邊 4 個 bits，左邊 4 個 bits 要清為 0，因此回傳 ``(in + shift) & 0xf``。

## 3. 除法運算
* 題意:
    * 對已知的除數 `d (或 D)` 和被除數 `n` 做計算，求出餘數 `n - quotient * D`。
    * 利用乘法運算、位移操作、預先計算，來代替除法運算
* 程式碼:
``` c
const uint32_t D = 3;
#define M ((uint64_t)(UINT64_C(XXX) / (D) + 1))

/* compute (n mod d) given precomputed M */
uint32_t quickmod(uint32_t n)
{   uint64_t quotient = ((__uint128_t) M * n) >> 64;
    return n - quotient * D;
}
```
* 作答
XXX = 0xFFFFFFFFFFFFFFFF

* 程式原理:
    * 要先計算出商數 `quotient` 才能計算餘數。而`quotient`就是 `n/D` 的整數部分。

    * 根據提示`n/D` 可以表示成 $\frac{n}{D}=n \times \frac{\frac{2^{N}}{D}}{2^{N}}$，因此可將計算拆解成:
        * 預先計算: $2^{N} / d$
        * 計算: n * $2^{N} / d$ ，再將結果向右 shift `N bits`。 (搭配 `quotient = ((__uint128_t) M * n) >> 64;` 可知 `N` 為 `64`。
* 處理預先計算會 overflow 的問題:
已知 `N` 為 `64`，且 `M` 的型別為 `uint64_t`(上限為 $2^{64}-1$)，所以 `M` 不能直接設為 $2^{N} / d$。因此這裡把 M 設為 $(2^{N}-1)/d + 1$，因此 `XXX = 0xFFFFFFFFFFFFFFFF`。

## 4. (延伸測驗 3)，
* 題意: 判斷某個數值能否被指定的除數所整除
* 在 `D` 和 `M` 都沿用的狀況下，程式碼如下:
``` c
bool divisible(uint32_t n)
{
    return n * M <= YYY;
}
```

## 5. 英文字母大小寫轉換
`strlower` 的 in-place 實作如下:
``` c
#include <ctype.h>
#include <stddef.h>
/* in-place implementation for converting all characters into lowercase. */
void strlower(char *s, size_t n)
{
    for (size_t j = 0; j < n; j++) {
        if (s[j] >= 'A' && s[j] <= 'Z')
            s[j] ^= 1 << 5;
        else if ((unsigned) s[j] >= '\x7f') /* extended ASCII */
            s[j] = tolower(s[j]);
    }
}
```
實作向量化的 `strlower`:
``` c
#include <ctype.h>
#include <stddef.h>
#include <stdint.h>

#define PACKED_BYTE(b) (((uint64_t)(b) & (0xff)) * 0x0101010101010101u)

/* vectorized implementation for in-place strlower */
void strlower_vector(char *s, size_t n)
{
    size_t k = n / 8;
    for (size_t i = 0; i < k; i++, s += 8) {
        uint64_t *chunk = (uint64_t *) s;
        if ((*chunk & PACKED_BYTE(VV1)) == 0) { /* is ASCII? */
            uint64_t A = *chunk + PACKED_BYTE(128 - 'A' + VV2);
            uint64_t Z = *chunk + PACKED_BYTE(128 - 'Z' + VV3);
            uint64_t mask = ((A ^ Z) & PACKED_BYTE(VV4)) >> 2;
            *chunk ^= mask;
        } else
            strlower(s, 8);
    }

    k = n % 8;
    if (k)
        strlower(s, k);
}
```

## 6.  LeetCode 137. Single Number II
``` c
int singleNumber(int *nums, int numsSize)
{
    int lower = 0, higher = 0;
    for (int i = 0; i < numsSize; i++) {
        lower ^= nums[i];
        lower &= KKK;
        higher ^= nums[i];
        higher &= JJJ;
    }
    return lower;
}
```
