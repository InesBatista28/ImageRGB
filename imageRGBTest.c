#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "imageRGB.h"
#include "instrumentation.h"

int main(int argc, char* argv[]) {
  program_name = argv[0];
  if (argc != 1) {
    error(1, 0, "Usage: imageRGBTest");
  }

  ImageInit();

  printf("1) ImageCreate\n");
  Image white_image = ImageCreate(100, 100);

  printf("2) ImageCreateChess(black)+ImageSavePBM\n");
  Image image_chess_1 = ImageCreateChess(150, 120, 30, 0x000000);
  ImageSavePBM(image_chess_1, "chess_image_1.pbm");

  printf("3) ImageCreateChess(red)+ImageSavePPM\n");
  Image image_chess_2 = ImageCreateChess(20, 20, 8, 0xff0000);
  ImageRAWPrint(image_chess_2);
  ImageSavePPM(image_chess_2, "chess_image_2.ppm");

  printf("4) ImageCreateChess(all black)\n");
  Image black_image = ImageCreateChess(100, 100, 100, 0x000000);
  ImageSavePBM(black_image, "black_image.pbm");

  printf("5) ImageCopy\n");
  Image copy_image = ImageCopy(image_chess_1);
  if (copy_image != NULL) {
    ImageSavePBM(copy_image, "copy_image.pbm");
  }

  printf("6) ImageLoadPBM\n");
  Image image_1 = ImageLoadPBM("img/feep.pbm");
  ImageRAWPrint(image_1);

  printf("7) ImageLoadPPM\n");
  Image image_2 = ImageLoadPPM("img/feep.ppm");
  ImageRAWPrint(image_2);

  printf("8) ImageCreatePalete\n");
  Image image_3 = ImageCreatePalete(4*32, 4*32, 4);
  ImageSavePPM(image_3, "palete.ppm");

  // ============================================================
  // ========== IMAGE ISEQUAL EXPERIMENTAL ANALYSIS =============
  // ============================================================

  printf("\n============================\n");
  printf("9) ImageIsEqual – Experimental Analysis\n");
  printf("============================\n");

  #define PRINT_EQ(label, eq) \
    printf("%s: equal=%d  PIXMEM=%lu  comparisons=%lu\n", \
           label, eq, InstrCount[0], InstrCount[0]/2);

  // ---------- BEST CASE ----------
  printf("\nTEST A: Best-case mismatch (first pixel)\n");

  Image A1 = ImageCreate(100,100);
  Image A2 = ImageCreate(100,100);
  ImageTestSetPixel(A2, 0, 0, BLACK);

  InstrReset();
  int eqA = ImageIsEqual(A1, A2);
  InstrPrint();
  PRINT_EQ("Mismatch@first", eqA);

  ImageDestroy(&A1);
  ImageDestroy(&A2);

  // ---------- WORST CASE ----------
  printf("\nTEST B: Worst-case identical\n");

  Image B1 = ImageCreate(100,100);
  Image B2 = ImageCopy(B1);

  InstrReset();
  int eqB = ImageIsEqual(B1, B2);
  InstrPrint();
  PRINT_EQ("Identical", eqB);

  ImageDestroy(&B1);
  ImageDestroy(&B2);

  // ---------- CONTROLLED MID CASE ----------
  printf("\nTEST C: Controlled mismatch (25%%, 50%%, 75%%)\n");

  uint32 w = 100, h = 100, total = w*h;
  uint32 poslist[3] = { total/4, total/2, 3*total/4 };
  const char *labelC[3] = { "Mismatch25%", "Mismatch50%", "Mismatch75%" };

  for (int k=0;k<3;k++) {
    uint32 idx = poslist[k];
    uint32 y = idx / w;
    uint32 x = idx % w;

    Image C1 = ImageCreate(w,h);
    Image C2 = ImageCreate(w,h);
    ImageTestSetPixel(C2, x, y, BLACK);

    InstrReset();
    int eqC = ImageIsEqual(C1, C2);
    InstrPrint();
    PRINT_EQ(labelC[k], eqC);

    ImageDestroy(&C1);
    ImageDestroy(&C2);
  }

  // ---------- RANDOM TEST ----------
  printf("\nTEST D: Random mismatches (10 trials)\n");

  for (int t = 1; t <= 10; t++) {
    Image R1 = ImageCreate(100,100);
    Image R2 = ImageCopy(R1);

    uint32 pos = rand() % (100*100);
    uint32 y = pos / 100;
    uint32 x = pos % 100;

    ImageTestSetPixel(R2, x, y, BLACK);

    char label[32];
    sprintf(label, "RandomTrial%d", t);

    InstrReset();
    int eqR = ImageIsEqual(R1, R2);
    InstrPrint();
    PRINT_EQ(label, eqR);

    ImageDestroy(&R1);
    ImageDestroy(&R2);
  }

  #undef PRINT_EQ

  // ========= CLEANUP =========
  ImageDestroy(&white_image);
  ImageDestroy(&black_image);
  if (copy_image != NULL) ImageDestroy(&copy_image);
  ImageDestroy(&image_chess_1);
  ImageDestroy(&image_chess_2);
  ImageDestroy(&image_1);
  ImageDestroy(&image_2);
  ImageDestroy(&image_3);

  return 0;
}
