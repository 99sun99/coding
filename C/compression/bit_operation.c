#include <string.h>
#include <stdio.h>
//https://www.liaohuqiu.net/cn/posts/bitmasp-and-lipo/
int bit_get(const unsigned char *bits, int pos);


/**
 设置缓冲区 bits 中处于位置 pos 的位的状态为 state - O(1)
 @param bits 缓冲区
 @param pos 位置 (缓冲区最左边的位置为 0 )
 @param state 状态值（必须为 0 或 1 ）
 */
void bit_set(unsigned char *bits, int pos, int state);


/**
 按位计算两个缓冲区 bits1 与 bits2 的异或值 - O(β) β 为每个缓冲区中位的个数
 @param bits1 缓冲区 1
 @param bits2 缓冲区 2
 @param bitsx 计算结果
 @param size 每个缓冲区位个位
 */
void bit_xor(const unsigned char *bits1, const unsigned char *bits2, unsigned char *bitsx, int size);


/**
 轮转缓冲区 bits（含 size 位），将位值向左移 count 位 -　O(nβ) β 为每个缓冲区中位的个数，n 为要轮转到左边的位数
 @param bits 缓冲区
 @param size 缓冲区位个位
 @param count 左移位数
 */
void bit_rot_left(unsigned char *bits, int size, int count);




int bit_get(const unsigned char *bits, int pos)
{
  unsigned char   mask;
  int             i;

  /// 设置位获取掩码 x=120  mask=128
  mask = 0x80;

  for (i = 0; i < (pos % 8); i++) {
    mask = mask >> 1;//不停除二
  }

  /// 获取位   mask最后0或者1，跟bits做&，看看是不是mask自己，查询状态 看mask对应的值在什么状态1or0；
  return (((mask & bits[(int)(pos / 8)]) == mask) ? 1 : 0);
}


void bit_set(unsigned char *bits, int pos, int state)
{
  unsigned char   mask;
  int             i;

  /// 设置位获取掩码
  mask = 0x80;

  for (i = 0; i < (pos % 8); i++) {
    mask = mask >> 1;
  }

  /// 设置位
  if (state) {
    bits[pos / 8] = bits[pos / 8] | mask;//设置状态，把第八位变成1，别的不管
  } else {
    bits[pos / 8] = bits[pos / 8] & (~mask);//清除状态，别的不管吧第八位变成0，摘面罩
  }

  return;
}


void bit_xor(const unsigned char *bits1, const unsigned char *bits2, unsigned char *bitsx, int size)
{
  int       i;

  /// 按位计算两个缓存区的异或值

  for (i = 0; i < size; i++) {

    if (bit_get(bits1, i) != bit_get(bits2, i)) {
      bit_set(bitsx, i, 1);
    } else {
      bit_set(bitsx, i, 0);
    }
  }

  return;
}



void bit_rot_left(unsigned char *bits, int size, int count)
{
  int       fbit = 0, lbit, i, j;

  /// 向左轮转缓冲区特定位数

  if (size > 0) {

    for (j = 0; j < count; j++) {

      for (i = 0; i <= ((size - 1) / 8); i++) {

        /// 获取即将被替换的位的值
        lbit = bit_get(&bits[i], 0);

        if (i == 0) {

          /// 将第一个位保存起来
          fbit = lbit;

        } else {

          /// 将前一个字节最右边的位移到当前字节的最左边
          bit_set(&bits[i - 1], 7, lbit);
        }

        /// 将特定位向左移动
        bits[i] = bits[i] << 1;
      }

      /// 将其最右边的位移动到首字节的最高位上

      bit_set(bits, size - 1, fbit);
    }
  }

  return;
}



int main(int argc, char **argv)
{
  unsigned char   bits1[8], bits2[8], bits3[8];
  int             i;

  /// 使用 64-bit 的位执行位操作

  for (i = 0; i < 8; i++) {

    bits1[i] = 0x00;
    bits2[i] = 0x00;
    bits3[i] = 0x00;

  }

  fprintf(stdout, "Initially\n");

  fprintf(stdout, "-> bits1: %02x %02x %02x %02x %02x %02x %02x %02x\n",
          bits1[0], bits1[1], bits1[2], bits1[3], bits1[4], bits1[5], bits1[6], bits1[7]);

  fprintf(stdout, "-> bits2: %02x %02x %02x %02x %02x %02x %02x %02x\n",
          bits2[0], bits2[1], bits2[2], bits2[3], bits2[4], bits2[5], bits2[6], bits2[7]);

  bit_set(bits1, 15, 1);
  bit_set(bits1, 16, 1);
  bit_set(bits1, 32, 1);
  bit_set(bits1, 63, 1);
  bit_set(bits2,  0, 1);
  bit_set(bits2, 15, 1);

  fprintf(stdout, "After setting bits 15, 16, 32, 63 of bits1 and bits 00, 15 of bits2\n");

  fprintf(stdout, "-> bits1: %02x %02x %02x %02x %02x %02x %02x %02x\n",
          bits1[0], bits1[1], bits1[2], bits1[3], bits1[4], bits1[5], bits1[6], bits1[7]);

  fprintf(stdout, "-> bits2: %02x %02x %02x %02x %02x %02x %02x %02x\n",
          bits2[0], bits2[1], bits2[2], bits2[3], bits2[4], bits2[5], bits2[6], bits2[7]);

  fprintf(stdout, "Bit 63 of bits1 is %d\n", bit_get(bits1, 63));
  fprintf(stdout, "Bit 62 of bits1 is %d\n", bit_get(bits1, 62));
  fprintf(stdout, "Bit 00 of bits2 is %d\n", bit_get(bits2,  0));
  fprintf(stdout, "Bit 01 of bits2 is %d\n", bit_get(bits2,  1));

  bit_xor(bits1, bits2, bits3, 32);

  fprintf(stdout, "bits3 is bits1 XOR bits2 (32 bits)\n");

  fprintf(stdout, "-> bits3: %02x %02x %02x %02x %02x %02x %02x %02x\n",
          bits3[0], bits3[1], bits3[2], bits3[3], bits3[4], bits3[5], bits3[6], bits3[7]);

  bit_xor(bits1, bits2, bits3, 64);

  fprintf(stdout, "bits3 is bits1 XOR bits2 (64 bits)\n");

  fprintf(stdout, "-> bits3: %02x %02x %02x %02x %02x %02x %02x %02x\n",
          bits3[0], bits3[1], bits3[2], bits3[3], bits3[4], bits3[5], bits3[6], bits3[7]);

  bit_rot_left(bits1, 64, 1);

  fprintf(stdout, "After rotating bits1 left x 1 (64 bits)\n");

  fprintf(stdout, "-> bits1: %02x %02x %02x %02x %02x %02x %02x %02x\n",
          bits1[0], bits1[1], bits1[2], bits1[3], bits1[4], bits1[5], bits1[6], bits1[7]);

  bit_rot_left(bits2, 64, 1);

  fprintf(stdout, "After rotating bits2 left x 1 (64 bits)\n");

  fprintf(stdout, "-> bits2: %02x %02x %02x %02x %02x %02x %02x %02x\n",
          bits2[0], bits2[1], bits2[2], bits2[3], bits2[4], bits2[5], bits2[6], bits2[7]);

  bit_rot_left(bits2, 16, 7);

  fprintf(stdout, "After rotating bits2 left x 7 (16 bits)\n");

  fprintf(stdout, "-> bits2: %02x %02x %02x %02x %02x %02x %02x %02x\n",
          bits2[0], bits2[1], bits2[2], bits2[3], bits2[4], bits2[5], bits2[6], bits2[7]);

  bit_rot_left(bits2, 8, 2);

  fprintf(stdout, "After rotating bits2 left x 2 (8 bits)\n");

  fprintf(stdout, "-> bits2: %02x %02x %02x %02x %02x %02x %02x %02x\n",
          bits2[0], bits2[1], bits2[2], bits2[3], bits2[4], bits2[5], bits2[6], bits2[7]);

  for (i = 0; i < 8; i++) {

    bits2[i] = 0x00;

  }

  bit_set(bits2,  0, 1);
  bit_set(bits2,  3, 1);
  bit_set(bits2,  8, 1);
  bit_set(bits2, 27, 1);

  fprintf(stdout, "After clearing and setting bits 0, 3, 8, 27 of bits2\n");

  fprintf(stdout, "-> bits2: %02x %02x %02x %02x %02x %02x %02x %02x\n",
          bits2[0], bits2[1], bits2[2], bits2[3], bits2[4], bits2[5], bits2[6], bits2[7]);

  bit_rot_left(bits2, 11, 6);

  fprintf(stdout, "After rotating bits2 left x 6 (11 bits)\n");

  fprintf(stdout, "-> bits2: %02x %02x %02x %02x %02x %02x %02x %02x\n",
          bits2[0], bits2[1], bits2[2], bits2[3], bits2[4], bits2[5], bits2[6], bits2[7]);

  for (i = 0; i < 8; i++) {

    bits2[i] = 0x00;

  }

  bit_set(bits2,  0, 1);
  bit_set(bits2,  3, 1);
  bit_set(bits2,  8, 1);
  bit_set(bits2, 27, 1);

  fprintf(stdout, "After clearing and setting bits 0, 3, 8, 27 of bits2\n");

  fprintf(stdout, "-> bits2: %02x %02x %02x %02x %02x %02x %02x %02x\n",
          bits2[0], bits2[1], bits2[2], bits2[3], bits2[4], bits2[5], bits2[6], bits2[7]);

  bit_rot_left(bits2, 28, 4);

  fprintf(stdout, "After rotating bits2 left x 4 (28 bits)\n");

  fprintf(stdout, "-> bits2: %02x %02x %02x %02x %02x %02x %02x %02x\n",
          bits2[0], bits2[1], bits2[2], bits2[3], bits2[4], bits2[5], bits2[6], bits2[7]);

  return 0;
}
