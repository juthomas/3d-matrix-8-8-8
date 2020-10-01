#include <Arduino.h>

enum  e_matrix_pin {
	//connector 1
	MATRIX_20 = 14,
	MATRIX_28 = 15,
	MATRIX_3 = 16,
	MATRIX_12 = 17,
	MATRIX_19 = 18,
	MATRIX_4 = 19,

	//connector 2
	MATRIX_18 = 22,
	MATRIX_32 = 24,
	MATRIX_24 = 26,
	MATRIX_13 = 28,
	MATRIX_27 = 30,

	//connector 3
	MATRIX_23 = 32,
	MATRIX_8 = 34,
	MATRIX_15 = 36,
	MATRIX_21 = 38,
	MATRIX_11 = 40,
	MATRIX_16 = 42,

	//connector 4
	MATRIX_30 = 23,
	MATRIX_25 = 25,
	MATRIX_7 = 27,
	MATRIX_17 = 29,
	MATRIX_2 = 31,
	MATRIX_31 = 33,

	//connector 5
	MATRIX_5 = 35,
	MATRIX_1 = 37,
	MATRIX_26 = 39,
	MATRIX_14 = 41,
	MATRIX_10 = 43,
	MATRIX_6 = 45,

	//connector 6
	MATRIX_9 = 47,
	MATRIX_29 = 49,
	MATRIX_22 = 51,
};

enum e_state_matrix_pin {
	DISCONNECTED,
	LED_LOW,
	LED_HIGH
};

typedef struct	s_matrix_table
{
	int enum_matrix_pin;
	int int_matrix_pin;
	int state_matrix_pin;

}				t_matrix_table;

static t_matrix_table g_matrix_table[32] = {
	(t_matrix_table){MATRIX_1, 1, 0},
	(t_matrix_table){MATRIX_2, 2, 0},
	(t_matrix_table){MATRIX_3, 3, 0},
	(t_matrix_table){MATRIX_4, 4, 0},
	(t_matrix_table){MATRIX_5, 5, 0},
	(t_matrix_table){MATRIX_6, 6, 0},
	(t_matrix_table){MATRIX_7, 7, 0},
	(t_matrix_table){MATRIX_8, 8, 0},
	(t_matrix_table){MATRIX_9, 9, 0},
	(t_matrix_table){MATRIX_10, 10, 0},
	(t_matrix_table){MATRIX_11, 11, 0},
	(t_matrix_table){MATRIX_12, 12, 0},
	(t_matrix_table){MATRIX_13, 13, 0},
	(t_matrix_table){MATRIX_14, 14, 0},
	(t_matrix_table){MATRIX_15, 15, 0},
	(t_matrix_table){MATRIX_16, 16, 0},
	(t_matrix_table){MATRIX_17, 17, 0},
	(t_matrix_table){MATRIX_18, 18, 0},
	(t_matrix_table){MATRIX_19, 19, 0},
	(t_matrix_table){MATRIX_20, 20, 0},
	(t_matrix_table){MATRIX_21, 21, 0},
	(t_matrix_table){MATRIX_22, 22, 0},
	(t_matrix_table){MATRIX_23, 23, 0},
	(t_matrix_table){MATRIX_24, 24, 0},
	(t_matrix_table){MATRIX_25, 25, 0},
	(t_matrix_table){MATRIX_26, 26, 0},
	(t_matrix_table){MATRIX_27, 27, 0},
	(t_matrix_table){MATRIX_28, 28, 0},
	(t_matrix_table){MATRIX_29, 29, 0},
	(t_matrix_table){MATRIX_30, 30, 0},
	(t_matrix_table){MATRIX_31, 31, 0},
	(t_matrix_table){MATRIX_32, 32, 0},
};


void setPixelOn(int a, int b)
{
	Serial.print("Pixel - :");
	Serial.println(a);
	Serial.print("Pixel + :");
	Serial.println(b);

	if (g_matrix_table[a].state_matrix_pin == DISCONNECTED && (g_matrix_table[b].state_matrix_pin == DISCONNECTED || g_matrix_table[b].state_matrix_pin == LED_HIGH))
	{
		g_matrix_table[a].state_matrix_pin = LED_LOW;
	}
	if (g_matrix_table[b].state_matrix_pin == DISCONNECTED && (g_matrix_table[a].state_matrix_pin == DISCONNECTED || g_matrix_table[a].state_matrix_pin == LED_LOW))
	{
		g_matrix_table[b].state_matrix_pin = LED_HIGH;
	}
}

int matrix_table_int_to_enum(int int_matrix_pin)
{
	return (g_matrix_table[int_matrix_pin -1].enum_matrix_pin);
}

void drawLayerPx(int x, int y, int z)
{
	int a;
	int b;

	a = (7 - x) % 4 + (7 - z) * 4;
	b = (7 - y) * 4;
	if (7 - x == 0 || 7 - x == 1)
	{
		b += 2;
	}
	else if (7 - x == 2 || 7 - x == 3)
	{
		b += 0;
	}
	else if (7 - x == 4 || 7 - x == 5)
	{
		b += 3;
	}
	else if (7 - x == 6 || 7 - x == 7)
	{
		b += 1;
	}
	setPixelOn(a, b);
}

void drawLayerPxApply(int x, int y, int z)
{
	static int tmpa = -1;
	static int tmpb = -1;
	int a;
	int b;

	a = (7 - x) % 4 + (7 - z) * 4;
	b = (7 - y) * 4;
	if (7 - x == 0 || 7 - x == 1)
	{
		b += 2;
	}
	else if (7 - x == 2 || 7 - x == 3)
	{
		b += 0;
	}
	else if (7 - x == 4 || 7 - x == 5)
	{
		b += 3;
	}
	else if (7 - x == 6 || 7 - x == 7)
	{
		b += 1;
	}

	if (tmpa > -1 && tmpb > -1)
	{
		pinMode(g_matrix_table[tmpa].enum_matrix_pin, INPUT);
		pinMode(g_matrix_table[tmpb].enum_matrix_pin, INPUT);
	}
	tmpa = a;
	tmpb = b;
	pinMode(g_matrix_table[a].enum_matrix_pin, OUTPUT);
	g_matrix_table[a].state_matrix_pin = LED_LOW;
	digitalWrite(g_matrix_table[a].enum_matrix_pin, LOW);


	pinMode(g_matrix_table[b].enum_matrix_pin, OUTPUT);
	g_matrix_table[b].state_matrix_pin = LED_HIGH;
	digitalWrite(g_matrix_table[b].enum_matrix_pin, HIGH);
}



void resetPins()
{
	for (int i = 0; i < 32; i++)
	{
		g_matrix_table[i].state_matrix_pin = DISCONNECTED;
		digitalWrite(g_matrix_table[i].enum_matrix_pin, HIGH);
	}
}

void fakePwmWave() //WIP Need changes
{
	for (int i = 0; i < 32; i++)
	{
		if (g_matrix_table[i].state_matrix_pin == LED_LOW)
		{
			pinMode(g_matrix_table[i].enum_matrix_pin, OUTPUT);
			digitalWrite(g_matrix_table[i].enum_matrix_pin, LOW);
		}
		else if (g_matrix_table[i].state_matrix_pin == LED_HIGH)
		{
			pinMode(g_matrix_table[i].enum_matrix_pin, OUTPUT);
			digitalWrite(g_matrix_table[i].enum_matrix_pin, HIGH);
		}
	}

}

void drawLayers(int layer[8][8][8])
{
	for (int z = 0; z < 8; z++)
	{
		for (int y = 0; y < 8; y++)
		{
			for (int x = 0; x < 8;x++)
			{
				if (layer[z][y][x] > 0)
				{
					drawLayerPx(7 - z, y, x);
				}
			}
		}
	}
}


void drawLayersApply(int layer[8][8][8])
{
	for (int z = 0; z < 8; z++)
	{
		for (int y = 0; y < 8; y++)
		{
			for (int x = 0; x < 8;x++)
			{
				if (layer[z][y][x] > 0)
				{
					drawLayerPxApply(7 - z, y, x);
				}
			}
		}
	}
}


int layers_test[8][8][8] {
	//1
	{{1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1}},
	//2
	{{1, 0, 0, 0, 0, 0, 0, 1},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{1, 0, 0, 0, 0, 0, 0, 1}},
	//3
	{{1, 0, 0, 0, 0, 0, 0, 1},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{1, 0, 0, 0, 0, 0, 0, 1}},
	//4
	{{1, 0, 0, 0, 0, 0, 0, 1},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{1, 0, 0, 0, 0, 0, 0, 1}},
	//5
	{{1, 0, 0, 0, 0, 0, 0, 1},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{1, 0, 0, 0, 0, 0, 0, 1}},
	//6
	{{1, 0, 0, 0, 0, 0, 0, 1},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{1, 0, 0, 0, 0, 0, 0, 1}},
	//7
	{{1, 0, 0, 0, 0, 0, 0, 1},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{1, 0, 0, 0, 0, 0, 0, 1}},
	//8
	{{1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1}},
};

void init_matrix_pins()
{
	for (int i = 0; i < 32; i++)
	{
		pinMode(g_matrix_table[i].enum_matrix_pin, INPUT);
	}
}

void setup() {
	Serial.begin(115200);
	Serial.println("Begin");
	//init_matrix_pins();
	resetPins();
	//drawLayers(layers_test);
	Serial.println("End");
}

void loop() {

	drawLayersApply(layers_test);
}