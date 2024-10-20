#include <string.h>
#include <math.h>
#include "OLED.h"

/********OLED����*********/
/**BվUP:����Ŷ�����****/

/**
 * ��    ����OLED��ʾͼ��(**Adam�޸�, Y������Ǹ���**)
 * ��    ����X ָ��ͼ�����Ͻǵĺ����꣬��Χ��0~127
 * ��    ����Y ָ��ͼ�����Ͻǵ������꣬��Χ��int_8
 * ��    ����Width ָ��ͼ��Ŀ�ȣ���Χ��0~128
 * ��    ����Height ָ��ͼ��ĸ߶ȣ���Χ��0~64
 * ��    ����Image ָ��Ҫ��ʾ��ͼ��
 * �� �� ֵ����
 * ˵    �������ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
 */
void OLED_ShowImage(uint8_t X, uint8_t Y0, uint8_t Width, uint8_t Height, const uint8_t *Image)
{
	int8_t Y = (int8_t)Y0; // XYֵΪ����ʱ,ֻҪͼƬ���в�������Ļ����ʾ,�ͻ����������;

	uint8_t i, j;
	/*������飬��ָ֤��ͼ�񲻻ᳬ����Ļ��Χ*/
	if (X > 127)
	{
		return;
	} // ���X����127���ӡ������,�������ӡ

	uint8_t k = 0, l = 0, temp_Height; //(����YΪ������ر���)
	if (Y < 0)						   // ���YС��0, �����ӡͼƬλ����Ļ�ڵĲ���;
	{
		temp_Height = Height; // ��¼ͼƬ�߶�
		Height += Y;		  // ͼƬ�ĸ� ��ȥY�����ֵ
		k = (-Y - 1) / 8 + 1; // ͼƬ��Byte�е��±�ƫ����;
		l = (-Y - 1) % 8 + 1; // Byteλ�ƻ�	//(8 + Y % 8)%8;//		OLED_ShowNum(0, 56, l, 3, 6);
		Y = 0;				  // ͼƬ��Ȼ����ĻY0��ʼ��ӡ
		if ((int8_t)Height < 1)
		{
			return;
		} // ���ӡ��ͼƬ��С��1ʱ,˵������Ҫ��ӡ;
	}
	else if (Y > 63)
	{
		return;
	} // ���Y����63���ӡ������,�������ӡ

	/*��ͼ�������������*/
	OLED_ClearArea(X, Y, Width, Height);

	/*����ָ��ͼ���漰�����ҳ*/
	/*(Height - 1) / 8 + 1��Ŀ����Height / 8������ȡ��*/
	uint8_t Height_ceil = (Height - 1) / 8 + 1;

	for (j = 0; j < Height_ceil; j++) // ��OLED_DisplayBuf���±����,(ͼ���漰�����ҳ)
	{
		/*����ָ��ͼ���漰�������*/
		for (i = 0; i < Width; i++)
		{
			/*�����߽磬��������ʾ*/
			if (X + i > 127)
			{
				break;
			}
			if (Y / 8 + j > 7)
			{
				return;
			}

			if (k) // ��һ��OLED_DisplayBuf���±�Ϊ����, ȡ����ͼ��Byte, ����λ�ƻ�����;
			{
				/*��ʾ��һByteͼ���ڵ�ǰҳ������*/
				OLED_DisplayBuf[Y / 8 + j][X + i] |= Image[(j + k - 1) * Width + i] >> ((l));

				/*�����߽磬��������ʾ*/
				/*ʹ��continue��Ŀ���ǣ���ǰByte����ͼƬʱ����һByte�ĺ������ݻ���Ҫ������ʾ*/
				if ((j + k) * 8 >= temp_Height)
				{
					continue;
				} // �����ǰ��Byte�Ѿ�������ͼ��,�򲻷���;

				/*��ʾ��ǰByteͼ���ڵ�ǰҳ������*/
				OLED_DisplayBuf[Y / 8 + j][X + i] |= Image[(j + k) * Width + i] << (8 - (l));
			}

			else // ��һ��ͼ��ByteΪ����, ��������OLED_DisplayBuf��֮��;
			{
				/*��ʾͼ���ڵ�ǰҳ������*/
				OLED_DisplayBuf[Y / 8 + j][X + i] |= Image[(j)*Width + i] << ((Y) % 8);

				/*�����߽磬��������ʾ*/
				/*ʹ��continue��Ŀ���ǣ���һҳ�����߽�ʱ����һҳ�ĺ������ݻ���Ҫ������ʾ*/
				if (Y / 8 + j + 1 > 7)
				{
					continue;
				}

				/*��ʾͼ������һҳ������*/
				OLED_DisplayBuf[Y / 8 + j + 1][X + i] |= Image[(j)*Width + i] >> (8 - (Y) % 8);
			}
		}
	}
}

/**
 * ��    ����OLED��ʾ���ֵ���
 * ��    ����X ָ���ַ������Ͻǵĺ����꣬��Χ��0~127
 * ��    ����Y ָ���ַ������Ͻǵ������꣬��Χ��0~63
 * ��    ����Hanzi ָ��Ҫ��ʾ���ַ�����Χ���ֿ��ַ�
 * ��    ����FontSize ָ�������С
 *           ��Χ��OLED_8X16		��8���أ���16����
 *                 OLED_6X8		��6���أ���8����
 * �� �� ֵ����
 * ˵    �������ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
 */
void OLED_MyShowChinese(int8_t X, int8_t Y, char *Hanzi, uint8_t FontSize) // ���ֵ��ִ�ӡ;
{
	uint8_t pIndex;
	for (pIndex = 0; strcmp(OLED_CF16x16[pIndex].Index, "") != 0; pIndex++)
	{
		/*�ҵ�ƥ��ĺ���*/
		if (strcmp(OLED_CF16x16[pIndex].Index, Hanzi) == 0)
		{
			break; // ����ѭ������ʱpIndex��ֵΪָ�����ֵ�����
		}
	}
	/*��������ģ��OLED_CF16x16��ָ��������16*16��ͼ���ʽ��ʾ*/
	OLED_ShowImage(X, Y, 16, 16, OLED_CF16x16[pIndex].Data);
}

/**
 * ��    ����OLED��ʾ�ַ���
 * ��    ����X ָ���ַ������Ͻǵĺ����꣬��Χ��0~127
 * ��    ����Y ָ���ַ������Ͻǵ������꣬��Χ��0~63
 * ��    ����String ָ��Ҫ��ʾ���ַ�������Χ���ֿ��ַ���ɵ��ַ���
 * ��    ����FontSize ָ�������С
 *           ��Χ��OLED_8X16		��8���أ���16����
 *                 OLED_6X8		��6���أ���8����
 * �� �� ֵ����
 * ˵    �������ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
 */
void OLED_ShowString(uint8_t X, uint8_t Y, char *String, uint8_t FontSize) // ��Ӣ�Ĵ�ӡ;
{
	uint8_t i = 0, len = 0;
	while (String[i] != '\0') // �����ַ�����ÿ���ַ�
	{
		if (String[i] == '\n')
		{
			Y += (FontSize == 8) ? 16 : 8;
			len = 0;
			i++;
		} // ���ݻ��з�
		if (X + (len + 1) * FontSize > 128)
		{
			Y += (FontSize == 8) ? 16 : 8;
			len = 0;
		} // ������Ļ�Զ�����
		if ((int8_t)Y > 64)
		{
			return;
		} //

		if (String[i] > '~') // ���������Ӣ���ַ�
		{
			char SingleChinese[4] = {0};
			SingleChinese[0] = String[i];
			i++;
			SingleChinese[1] = String[i];
			i++;
			SingleChinese[2] = String[i];

			if (FontSize == 8)
			{
				OLED_MyShowChinese(X + len * FontSize, Y, SingleChinese, FontSize);
			}
			else
			{
				OLED_MyShowChinese(X + len * FontSize, Y, SingleChinese, FontSize);
			}

			i++;
			len += 2;
		}
		else /*����OLED_ShowChar������������ʾÿ���ַ�*/
		{
			OLED_ShowChar(X + len * FontSize, Y, String[i], FontSize);
			i++;
			len++;
		}
	}
}

/**
 * ��    ����OLED������ʾ�ַ���
 * ��    ����X ָ���ַ������Ͻǵĺ����꣬��Χ��0~127
 * ��    ����Y ָ���ַ������Ͻǵ������꣬��Χ��0~63
 * ��    ����Width ָ�������ȣ���Χ��0~127
 * ��    ����Height ָ������߶ȣ���Χ��0~63
 * ��    ����String ָ��Ҫ��ʾ���ַ�������Χ���ֿ��ַ���ɵ��ַ���
 * ��    ����FontSize ָ�������С
 *           ��Χ��OLED_8X16		��8���أ���16����
 *                 OLED_6X8		��6���أ���8����
 * �� �� ֵ����
 * ˵    �������ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
 */
uint8_t OLED_ShowStringArea(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height, char *String, uint8_t FontSize) // �����ӡ��ӡ;
{
	uint8_t i = 0, len = 0;
	while (String[i] != '\0') // �����ַ�����ÿ���ַ�
	{
		if (String[i] == '\n') // ���ݻ��з�
		{
			Y += (FontSize == 8) ? 16 : 8;
			Height -= (FontSize == 8) ? 16 : 8;
			if (Height < ((FontSize == 8) ? 16 : 8))
			{
				break;
			}

			len = 0;
			i++;
		}

		if ((len + 1) * FontSize > Width) // ������Ļ�Զ�����
		{
			Y += (FontSize == 8) ? 16 : 8;
			Height -= (FontSize == 8) ? 16 : 8;
			if (Height < ((FontSize == 8) ? 16 : 8))
			{
				break;
			}

			len = 0;
		}

		if (String[i] > '~') // ���������Ӣ���ַ�
		{
			char SingleChinese[4] = {0};
			SingleChinese[0] = String[i];
			i++;
			SingleChinese[1] = String[i];
			i++;
			SingleChinese[2] = String[i];

			if (FontSize == 8)
			{
				OLED_MyShowChinese(X + len * FontSize, Y, SingleChinese, FontSize);
			}
			else
			{
				OLED_MyShowChinese(X + len * FontSize, Y, SingleChinese, FontSize);
			}

			i++;
			len += 2;
		}
		else /*����OLED_ShowChar������������ʾÿ���ַ�*/
		{
			OLED_ShowChar(X + len * FontSize, Y, String[i], FontSize);
			i++;
			len++;
		}
	}
	return len;
}

/**
 * ��    ������ת��
 * ��    ����CX ָ����תԭ��ĺ����꣬��Χ��0~127
 * ��    ����CY ָ����תԭ��������꣬��Χ��0~63
 * ��    ����PX ָ����ת��ĺ����꣬��Χ��0~127
 * ��    ����PY ָ����ת��������꣬��Χ��0~63
 * ��    ����Angle ָ����ת�Ƕȣ���Χ��-360~360
 * �� �� ֵ����
 * ˵    �������ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
 */
void OLED_Rotation_C_P(int8_t CX, int8_t CY, float *PX, float *PY, int16_t Angle) // ��ת��
{
	float Theta = (3.14 / 180) * Angle;
	float Xd = *PX - CX;
	float Yd = *PY - CY;

	*PX = (Xd)*cos(Theta) - (Yd)*sin(Theta) + CX; // + 0.5;
	*PY = (Xd)*sin(Theta) + (Yd)*cos(Theta) + CY; // + 0.5;
}
/**
 * ��    ������OLED�Դ����鲿����ת
 * ��    ����X ָ����תԭ��ĺ����꣬��Χ��0~127
 * ��    ����Y ָ����תԭ��������꣬��Χ��0~63
 * ��    ����Width ָ����ת����뾶����Χ��0~63
 * ��    ����Angle ָ����ת�Ƕȣ���Χ��-360~360
 * �� �� ֵ����
 * ˵    �������ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
 */
void OLED_Rotation_Block(int8_t X, int8_t Y, int8_t Width, int16_t Angle) // ��ת����
{
	uint8_t OLED_DpB1[8][128];
	memcpy(OLED_DpB1, OLED_DisplayBuf, 1024);

	// OLED_Clear();
	OLED_ClearArea(X - Width, Y - Width, Width * 2, Width * 2);
	float Theta = (3.14 / 180) * Angle;

	uint8_t x, y;
	for (y = Y - Width; y < Y + Width; y++) // ����ָ��ҳ
	{
		for (x = X - Width; x < X + Width; x++) // ����ָ����
		{
			//			if(x > 127) break;
			//			if(y > 63) break;
			//			if(x < 0) break;
			//			if(y < 0) break;
			x %= 128;
			y %= 64;

			if (OLED_DpB1[y / 8][x] & 0x01 << (y % 8)) // Ч��ͬif(OLED_GetPoint(x, y))
			{
				OLED_DrawPoint(
					(float)(x - X) * cos(Theta) - (float)(y - Y) * sin(Theta) + X, //+ 0.5,
					(float)(x - X) * sin(Theta) + (float)(y - Y) * cos(Theta) + Y  // + 0.5
				);
			}
		}
	}
}

void ellipse_algorithm(int8_t x0, int8_t y0, int8_t a, int8_t b)
{
	float t = 0.01;
	float d = 6.28 / ((a + b) * 2);

	int8_t x = x0;
	int8_t y = y0;

	int8_t xtemp = x;
	int8_t ytemp = y;

	x = (a * cos(t));
	y = (b * sin(t));

	while (t <= 6.28)
	{

		xtemp = x;
		ytemp = y;

		x = (a * cos(t));
		y = (b * sin(t));
		OLED_DrawLine(x0 + xtemp, y0 + ytemp, x0 + x, y0 + y);
		t += d;
		// OLED_Update();
	}
}
