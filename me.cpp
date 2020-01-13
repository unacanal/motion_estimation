#include <stdio.h>
#include <stdlib.h>

#define WIDTH  352
#define HEIGHT 288
#define FRAMES 300

#define BYTE unsigned char

BYTE* get_luma(FILE* in, int w, int h, int f);

int main()
{
	/* motion estimation program */

	// 1. Read a YUV file
	FILE* in = fopen("./yuv420/akiyo_cif.yuv", "rb+"); // read binary mode, yuv420 file
	FILE* out = fopen("luma.yuv", "wb+");

	// 2. Read luminance(Y) from the file
	BYTE* luma = get_luma(in, WIDTH, HEIGHT, FRAMES); // 8 bit, 0 ~ 255

	fwrite(luma, sizeof(BYTE), WIDTH*HEIGHT*FRAMES, out);

	// 3. Read search range from previous frame
	// 4. Read macro block from current frame
	// 5. motion estimation
	// 6. Save result

	return 0;
}

// 1 frame = luma (4) + chroma (2)
BYTE* get_luma(FILE* in, int w, int h, int f)
{
	BYTE* buffer = (BYTE*)malloc(w * h);
	BYTE* skip = (BYTE*)malloc(w * h / 2); // skip chroma part
	BYTE* luma = (BYTE*)malloc(w * h * f);

	for (int i = 0; i < f; i++)
	{
		fread(buffer, sizeof(BYTE), (w * h), in); // read w*h bytes from each frame == luma in each frame
		for (int j = 0; j < w * h; j++) // j: 0 ~ 352*288-1
		{
			luma[w * h * i + j] = buffer[j];
		}
		fread(skip, sizeof(BYTE), (w * h / 2), in);
	}
	free(buffer);
	free(skip);

	return luma;
}