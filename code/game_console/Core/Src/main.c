#include "main.h"
#include "ILI9225.h"
#include "snake.h"
#include "image.c"
SPI_HandleTypeDef hspi1;
extern const uint32_t image_data_Image[19360];
extern const uint32_t image_data_Image1[19360];
extern const uint32_t image_data_Image3[19360];
TIM_HandleTypeDef htim1;

unsigned short bird_image[0x1EE] ={
0xC7FF, 0xC7FF, 0xC7FF, 0xC7FF, 0xC7FF, 0xC7FF, 0xCFFF, 0xCFFF, 0xD7FF, 0x6410, 0x3A6A, 0x3A8A, 0x3A8A, 0x3A8A, 0x3A8A, 0x42AA,   // 0x0010 (16)
0x42AA, 0x3208, 0xA679, 0xD7FF, 0xC7FF, 0xC7FF, 0xC7FF, 0xC7FF, 0xC7FF, 0xC7FF, 0xC7FF, 0xC7FF, 0xC7FF, 0xC7FF, 0xC7FF, 0xCFFF,   // 0x0020 (32)
0xBF7D, 0xB75D, 0xC7DF, 0x3A27, 0x0000, 0x0820, 0x0820, 0x0820, 0x0840, 0x0000, 0x0000, 0x0000, 0x8534, 0xBF9E, 0xCFFF, 0xC7FF,   // 0x0030 (48)
0xC7FF, 0xC7FF, 0xC7FF, 0xC7FF, 0xC7FF, 0xC7FF, 0xC7FF, 0xC7FF, 0xCFFF, 0xE7FF, 0x1966, 0x0000, 0x0000, 0xBC60, 0xFF00, 0xFEC0,   // 0x0040 (64)
0xFEC0, 0xFEE0, 0xFFC0, 0x4180, 0x0001, 0xFFFF, 0x3165, 0x0000, 0xEFFF, 0xCFFF, 0xC7FF, 0xC7FF, 0xC7FF, 0xC7FF, 0xC7FF, 0xC7FF,   // 0x0050 (80)
0xCFFF, 0xCFFF, 0xBF7D, 0x2A09, 0x8BA2, 0xAC20, 0xA3E0, 0xE580, 0xFE20, 0xFE20, 0xFE20, 0xEDC0, 0x4160, 0x8C4E, 0xB596, 0xFFFF,   // 0x0060 (96)
0xC638, 0x9CF3, 0x29E7, 0x9E59, 0xCFFF, 0xC7FF, 0xC7FF, 0xC7FF, 0xC7FF, 0xCFFF, 0xC7FF, 0xCFFF, 0xAEFB, 0x0000, 0xBC80, 0xFEA0,   // 0x0070 (112)
0xFE80, 0xFE20, 0xFE20, 0xFE20, 0xFE40, 0xE580, 0x0000, 0xBDD7, 0xFFFF, 0xFFFF, 0xFFFF, 0xEF7D, 0x0000, 0x8555, 0xCFFF, 0xCFFF,   // 0x0080 (128)
0xC7FF, 0xC7FF, 0xD7FF, 0xB73C, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFF20, 0xFE40, 0xFE20, 0xFE20, 0xFE40, 0xE580,   // 0x0090 (144)
0x0000, 0xB5B6, 0xFFFF, 0xFFFF, 0x3186, 0x0000, 0xFFFF, 0x41E7, 0x0000, 0xDFFF, 0xC7FF, 0xC7FF, 0x7CD3, 0x534D, 0x9CB2, 0x94B2,   // 0x00A0 (160)
0x94B2, 0x94B2, 0x94B2, 0x8C70, 0x5A00, 0xD520, 0xFE40, 0xFE20, 0xFE40, 0xE580, 0x0000, 0xB5B6, 0xFFFF, 0xFFFF, 0x4228, 0x0020,   // 0x00B0 (176)
0xFFFF, 0x4A28, 0x0020, 0xDFFF, 0xC7FF, 0xC7FF, 0x3228, 0x1061, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xEF5D, 0x0000, 0xBC60,   // 0x00C0 (192)
0xFEC0, 0xFE20, 0xFE40, 0xE560, 0x0000, 0xBDF8, 0xFFFF, 0xFFFF, 0x31A6, 0x0000, 0xFFFF, 0x4A28, 0x0020, 0xDFFF, 0xC7FF, 0xC7FF,   // 0x00D0 (208)
0x3A69, 0x10A3, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x31CA, 0x0000, 0xFEC0, 0xFE20, 0xFE40, 0xFF60, 0x28E0,   // 0x00E0 (224)
0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x4A69, 0x0041, 0xEFFF, 0xCFFF, 0xC7FF, 0x3A6A, 0x1080, 0xFFB0, 0xFFBB, 0xFFFF, 0xFFFF,   // 0x00F0 (240)
0xFFFF, 0xFFDE, 0xFF8F, 0x39C4, 0x0840, 0xFEC0, 0xFE20, 0xFE20, 0xFE60, 0xA3E0, 0x7B01, 0x7C11, 0x7BEF, 0x7BEF, 0x8C51, 0x2104,   // 0x0100 (256)
0x0000, 0x6410, 0xAEBA, 0xCFFF, 0x29C7, 0x0800, 0xFF20, 0xFFD9, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFF20, 0x3140, 0x0000, 0xFEC0,   // 0x0110 (272)
0xFE20, 0xFE20, 0xFE20, 0xFF00, 0xFE60, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8DD7, 0xE7FF, 0xD7FF, 0xB75D,   // 0x0120 (288)
0x0000, 0xBC60, 0xFE80, 0xFE40, 0xFE60, 0xED80, 0x0000, 0xBC80, 0xFEC0, 0xFE20, 0xFE20, 0xFE20, 0xFEE0, 0x3140, 0x0000, 0xFBC2,   // 0x0130 (304)
0xFB81, 0xFB81, 0xFB81, 0xFB81, 0xFB81, 0xFBA2, 0x3820, 0x0041, 0xCFFF, 0xBF7D, 0x42CC, 0x8363, 0x9380, 0x9380, 0x9380, 0x8B60,   // 0x0140 (320)
0x49C0, 0xCCE0, 0xFE00, 0xF5C0, 0xF5E0, 0xEDA0, 0x8B80, 0x69E0, 0x6120, 0x81C1, 0x81C1, 0x81C1, 0x81C1, 0x81C1, 0x81C1, 0x89A0,   // 0x0150 (336)
0x62C9, 0x6430, 0xC7FF, 0xCFFF, 0xE7FF, 0x1946, 0x0000, 0x0000, 0x0000, 0x0840, 0xFE60, 0xE580, 0xE560, 0xE560, 0xE580, 0xC4C0,   // 0x0160 (352)
0x0000, 0xB241, 0xF341, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8DD7, 0xDFFF, 0xC7FF, 0xC7FF, 0xCFFF, 0xC7FF,   // 0x0170 (368)
0xC7FF, 0xD7FF, 0x29C7, 0x0800, 0xFE40, 0xEDA0, 0xEDA0, 0xE560, 0xE560, 0xE580, 0xF5C0, 0x3960, 0x0000, 0xFB81, 0xEB41, 0xEB41,   // 0x0180 (384)
0xEB41, 0xF341, 0xDB01, 0x0000, 0x8D75, 0xCFFF, 0xC7FF, 0xC7FF, 0xC7FF, 0xCFFF, 0xCFFF, 0xD7FF, 0x6410, 0x4A88, 0x9BA0, 0x9380,   // 0x0190 (400)
0x9BC0, 0xEDA0, 0xE560, 0xE560, 0xF5C0, 0x72E0, 0x49A0, 0x9A01, 0x9A01, 0x9A01, 0x9A01, 0x9A01, 0x89E1, 0x0000, 0x8D75, 0xCFFF,   // 0x01A0 (416)
0xC7FF, 0xC7FF, 0xC7FF, 0xC7FF, 0xC7FF, 0xC7FF, 0xD7FF, 0xB75D, 0x0000, 0x0000, 0x0000, 0xFE80, 0xFE00, 0xFE00, 0xFE00, 0xFE60,   // 0x01B0 (432)
0xEDA0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8534, 0xCFFF, 0xC7FF, 0xC7FF, 0xC7FF, 0xC7FF, 0xC7FF, 0xC7FF,   // 0x01C0 (448)
0xC7FF, 0xC7FF, 0xB73C, 0xBF7D, 0xA679, 0x0000, 0x0800, 0x0800, 0x0800, 0x0000, 0x18C1, 0xC7FF, 0xB75D, 0xB75D, 0xB75D, 0xB75D,   // 0x01D0 (464)
0xB75D, 0xB73C, 0xC7DF, 0xCFFF, 0xC7FF, 0xC7FF, 0xC7FF, 0xC7FF, 0xC7FF, 0xC7FF, 0xC7FF, 0xC7FF, 0xCFFF, 0xCFFF, 0xBF9E, 0x3208,   // 0x01E0 (480)
0x42AA, 0x42AA, 0x42AA, 0x3A8A, 0x4B0C, 0xDFFF, 0xCFFF, 0xCFFF, 0xCFFF, 0xCFFF, 0xCFFF, 0xCFFF, 0xCFFF, 0xC7FF, };

const unsigned char bitmap1[]={
	0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x62,0x20,0x20,0x20,0x20,
	0x20,0x20,0x20,0x20,0x20,0x20,0x63,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x64,0x20,0x20,0x20,0x20,
	0x20,0x20,0x20,0x20,0x20,0x20,0x65,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x66,0x20,0x20,0x20,0x20,
	0x20,0x20,0x20,0x20,0x20,0x67,0x68,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x69,0x6a,0x20,0x20,0x20,0x20,
	0x20,0x20,0x20,0x20,0x20,0x6b,0x6c,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x6d,0x6e,0x6f,0x20,0x20,0x20,
	0x20,0x20,0x20,0x20,0x20,0x70,0x71,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x72,0x73,0x74,0x75,0x76,0x20,0x20,
	0x20,0x20,0x20,0x77,0x78,0x79,0x7a,0x7b,0x7c,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x7d,0x7e,0x7f,0x80,0x81,0x82,0x20,0x20,
	0x20,0x20,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x20,0x20,0x20,0x20,0x20,0x20,0x8b,0x8c,0x8d,0x20,0x8e,0x8f,0x90,0x20,
	0x20,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x20,0x20,0x20,0x20,0x20,0x20,0x9a,0x9b,0x9c,0x20,0x9d,0x9e,0x20,0x20,
	0x20,0x9f,0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0x20,0x20,0x20,0x20,0x20,0xa9,0xaa,0xab,0xac,0xad,0xae,0x20,0x20,
	0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,0xb5,0xb6,0xb7,0xb8,0xb9,0x20,0x20,0x20,0x20,0x20,0xba,0xbb,0xbc,0xbd,0xbe,0xbf,0x20,0x20,
	0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0x20,0x20,0x20,0x20,0x20,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0x20,
	0xd2,0xd3,0xd4,0xd5,0xd6,0xd7,0xd8,0xd9,0xda,0xdb,0xdc,0xdd,0x20,0xde,0xdf,0xe0,0xe1,0xe2,0xe3,0xe4,0xe5,0xe6,0xe7,0xe8,
	0xe9,0xea,0xeb,0xec,0xed,0xee,0xef,0xf0,0xf1,0xf2,0xf3,0xf4,0xf5,0xf6,0x20,0xf7,0xf8,0xf9,0xfa,0xfb,0xfc,0xfd,0xfe,0xff
};

/*--------------------*/
#define WIDTH_PILL		40
#define HIDDENT		50
#define HEIGH_SCREEN 	200
#define DISTANCE		65
#define YES			1
#define NO			0
#define WIDTH_BIRD		26
#define HEIGH_BIRD 	19
#define WIDTH_LINE		176
#define HEIGH_LINE		5
#define BIRD_X			60
#define BIRD_Y			100
#define X_COM        	76
#define FALLING		0
#define RISING			1
#define X_SCORE		62
#define Y_SCORE		207
#define X_H_SCORE		90
#define X_GAME_OVER	5
#define Y_GAME_OVER	40
#define X_GAME_SCORE	30
#define Y_GAME_SCORE	90
#define X_SOCRE_END	95
#define SCORED			40
#define NOTE_DO    262
#define NOTE_RE    294
#define NOTE_MI    330
#define NOTE_FA    349
#define NOTE_SOL   392
#define NOTE_LA    440
#define NOTE_SI    494
#define NOTE_DO2   523
#define NOTE_RE2   587
#define NOTE_MI2   659
#define NOTE_FA2   698
#define NOTE_SOL2  784
#define NOTE_DO     262
#define NOTE_RE     294
#define NOTE_MI     330
#define NOTE_FA     349
#define NOTE_SOL    392
#define NOTE_LA     440
#define NOTE_SI     494
#define NOTE_DO2    523
#define NOTE_RE2    587
#define NOTE_MI2    659
#define NOTE_FA2    698
#define NOTE_SOL2   784

uint16_t melody[] = {
    NOTE_SOL, NOTE_SOL, NOTE_LA, NOTE_SOL, NOTE_DO2, NOTE_SI,
    NOTE_SOL, NOTE_SOL, NOTE_LA, NOTE_SOL, NOTE_RE2, NOTE_DO2,
    NOTE_SOL, NOTE_SOL, NOTE_SOL2, NOTE_MI2, NOTE_DO2, NOTE_SI, NOTE_LA,
    NOTE_FA2, NOTE_FA2, NOTE_MI2, NOTE_DO2, NOTE_RE2, NOTE_DO2
};

uint16_t noteDurations[] = {
    4,4,2,2,2,2,
    4,4,2,2,2,2,
    4,4,2,2,2,2,1,
    4,4,2,2,2,1
};
uint16_t mario_melody[] = {
    NOTE_MI2, NOTE_MI2, 0,
    NOTE_MI2, 0,
    NOTE_DO2, NOTE_MI2, 0,
    NOTE_SOL2, 0, 0,
    NOTE_SOL, 0, 0,

    NOTE_DO2, 0, 0,
    NOTE_SOL, 0, 0,
    NOTE_MI, 0, 0,
    NOTE_LA, 0,
    NOTE_SI, 0,
    NOTE_SI, NOTE_LA, 0,

    NOTE_SOL, NOTE_MI2, NOTE_SOL2,
    NOTE_LA, 0,
    NOTE_FA2, NOTE_SOL2, 0,
    NOTE_MI2, 0, 0,
    NOTE_DO2, NOTE_RE2, NOTE_SI,
    NOTE_DO2, 0, 0
};

uint16_t mario_duration[] = {
    8, 8, 4,
    8, 4,
    8, 8, 4,
    8, 4, 4,
    8, 4, 4,

    8, 4, 4,
    8, 4, 4,
    8, 4, 4,
    8, 4,
    8, 4,
    8, 8, 4,

    8, 8, 8,
    8, 4,
    8, 8, 4,
    8, 4, 4,
    8, 8, 8,
    8, 4, 4
};

SnakeGame snake;

uint16_t adc_x;
uint16_t adc_y;
uint16_t dem = 0;
int adc_triggered = 0; // flag
int adc_pulse = 0;
int trang_thai_menu = 1;  // 1 = menu ch?n game, 0 = dã thoát menu
int game_running = 1;
int flappy_bird = 1;

unsigned char cursorx,cursory,cursorc;
/*-----snake------------*/
unsigned char board[25][12]; //Array to place blocks
unsigned char boardchange[25][12]; //An array indicating whether the board array has changed
unsigned int score,highscore; //score, high score
unsigned int gcount=0; //Counter, used for random number seed
unsigned short keyold; //Last key input status (to prevent repeat input)
int8_t downkeyrepeat; //Down key repeat control
unsigned char next; //Next block type
unsigned char fallspeed,fallcount; //Block falling speed, counter
unsigned char level; //current level
unsigned char gamestatus;

unsigned char lines;//Cumulative number of erased lines
const unsigned int scorearray[]={40,100,300,1200};
int16_t y_bird = 0;
int c = 0, score_old = 0, game_over = NO;
uint16_t list_heigh[15];
uint16_t high_score = 0;
int16_t x1 = 0, x2 = 0;
uint16_t heigh_pill1 = 0, heigh_pill2 = 0;
uint16_t x_com = 0, h_com = 0;

int bird_left = BIRD_X;
int bird_right = BIRD_X + WIDTH_BIRD;
int bird_top = 0;
int bird_bottom = 0;


/*----------------------*/

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM1_Init(void);
void ADC_init(void)
{
	// 1. B?t clock cho ADC1 v? GPIOA
	RCC->APB2ENR |= (1 << 8);  // B?t clock cho ADC1
	RCC->AHB1ENR |= (1 << 0);  // B?t clock cho GPIOA

	// 2. C?u h?nh PA1 v? PA2 ? ch? d? Analog
	GPIOA->MODER |= (3 << (1 * 2)) | (3 << (2 * 2)); 

	// 3. C?u h?nh ADC1
	ADC1->CR1 |= (1 << 8);    // B?t ch? d? qu?t (SCAN mode)
	ADC1->CR2 |= (1 << 1);    // B?t ch? d? li?n t?c (Continuous mode

	// 4. Ch?n s? k?nh chuy?n d?i
	ADC1->SQR1 |= (1 << 20);  // select regular channel 


	// 6. B?t ADC
	ADC1->CR2 |= (1 << 0);    // B?t ADC

	// 7. B?t d?u chuy?n d?i ADC
	ADC1->CR2 |= (1 << 30);   // B?t d?u chuy?n d?i ADC

}
uint16_t Read_ADC(uint8_t channel) {
    // Ch?n k?nh ADC
    ADC1->SQR3 = channel;  

    // B?t d?u chuy?n d?i
    ADC1->CR2 |= ADC_CR2_SWSTART;  

    // Ch? chuy?n d?i ho?n t?t
    while (!(ADC1->SR & ADC_SR_EOC));  

    return (uint16_t)ADC1->DR;  // Tr? v? gi? tr? ADC
}
uint16_t Read_ADC_Avg(uint8_t channel) {
    uint32_t sum = 0;
    for (int i = 0; i < 18; i++) {
        sum += Read_ADC(channel);
    }
    return (uint16_t)sum / 18;  // L?y trung b?nh 10 l?n d?c
}

int is_button_pressed() {
    return HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_12) == GPIO_PIN_RESET; // N?u dùng nút kéo xu?ng (pull-down)
}
int is_button_pressed1() {
    return HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13) == GPIO_PIN_RESET; // N?u dùng nút kéo xu?ng (pull-down)
}
int is_button_pressed2() {
    return HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_14) == GPIO_PIN_RESET; // N?u dùng nút kéo xu?ng (pull-down)
}
int is_button_pressed3() {
    return HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_15) == GPIO_PIN_RESET; // N?u dùng nút kéo xu?ng (pull-down)
}

void Init_Heigh_Pill() {
    for (int i = 0; i < 15; i++) {
        list_heigh[i] = 150 - i * 10;
    }
}


void Draw_Pillar(int16_t x, uint16_t heigh) {
    if (x < 176) {
        // Xóa ph?n cu ? phía trên ?ng khói
        fill_rectangle(x + WIDTH_PILL, 0, x + WIDTH_PILL + 1, heigh, COLOR_WHITE);

        // Xóa ph?n cu ? phía du?i ?ng khói
        fill_rectangle(x + WIDTH_PILL, heigh + DISTANCE, x + WIDTH_PILL + 1, HEIGH_SCREEN, COLOR_WHITE);

        // V? ph?n trên
        fill_rectangle(x, 0, x + WIDTH_PILL - 1, heigh, COLOR_GREEN);

        // V? ph?n du?i
        fill_rectangle(x, heigh + DISTANCE, x + WIDTH_PILL - 1, HEIGH_SCREEN, COLOR_GREEN);
    }
}


void Print_Score(uint16_t val, uint16_t x_score, uint16_t color) {
    char string[3] = {0};
    fill_rectangle(x_score, Y_SCORE, x_score + 20, 219, 0xFFE0);
    if (val < 10) {
        draw_char(x_score, Y_SCORE, val + '0', color, 1);
    } else {
        string[0] = val / 10 + '0';
        string[1] = val % 10 + '0';
        draw_string(x_score, Y_SCORE, color, 1, string);
    }
}
void Game_Over() {
    fill_rectangle(X_GAME_OVER - 10, Y_GAME_OVER - 10, X_GAME_OVER + 100, Y_GAME_OVER + 60, COLOR_WHITE);
    draw_string(X_GAME_OVER, Y_GAME_OVER+10, 0xF800, 2, "Game Over");
    draw_string(X_GAME_SCORE, Y_GAME_SCORE, 0xF800, 1, "Score:");

    char string[3] = {0};
    if (score < 10) {
        draw_char(X_SOCRE_END, Y_GAME_SCORE, score + '0', 0xF800, 1);
    } else {
        string[0] = score / 10 + '0';
        string[1] = score % 10 + '0';
        draw_string(X_SOCRE_END, Y_GAME_SCORE, 0xF800, 1, string);
    }
    while (is_button_pressed());
    delay_ms(100);

    // Ð?i nh?n l?i d? b?t d?u
    while (!is_button_pressed());
    delay_ms(100);

}
void Init_Game() {
    Init_Heigh_Pill();
    score = 0;
    x1 = 176;
    x2 = 300;
    heigh_pill1 = list_heigh[rand() % 15];
    heigh_pill2 = 100;
    y_bird = BIRD_Y;
    x_com = 176;
    h_com = heigh_pill1;


    draw_map(BIRD_X, BIRD_Y,1,19,26, bird_image);
    fill_rectangle(0, HEIGH_SCREEN, 176, HEIGH_SCREEN + HEIGH_LINE,COLOR_YELLOWGREEN);
    fill_rectangle(0, HEIGH_SCREEN + HEIGH_LINE, 176, 220,COLOR_YELLOW);
    draw_string(5, HEIGH_SCREEN + 6,COLOR_RED, 1, "Score:");
    Print_Score(score, X_SCORE,COLOR_RED);

}
uint16_t background[WIDTH_BIRD * HEIGH_BIRD];

void Bird_Fly(uint16_t y)
{
    // M? r?ng vùng xóa màu tr?ng ra m?t chút d? bao tr?n v?t cu c?a chim
    fill_rectangle(BIRD_X - 2, y - 5, BIRD_X + WIDTH_BIRD + 2, y + HEIGH_BIRD + 5, COLOR_WHITE);
    HAL_Delay(5);
    
    // V? chim dúng t?i v? trí BIRD_X
    draw_map(BIRD_X, y, 1, HEIGH_BIRD, WIDTH_BIRD, bird_image);
}
void Buzzer_SetFrequency(uint32_t freq)
{
    uint32_t timer_clk = 100000000; // TIM1 ch?y ? 100 MHz
    uint32_t prescaler = 99;        // PSC = 99 ? timer tick = 1 MHz
    uint32_t arr;

    if (freq == 0) {
        TIM1->CCR1 = 0; // t?t âm
        return;
    }

    arr = (1000000 / freq) - 1;  // 1MHz / freq = chu k? c?a PWM
    TIM1->PSC = prescaler;
    TIM1->ARR = arr;
    TIM1->CCR1 = arr / 2;        // duty 50%
}

void Buzzer_PlayTone(uint32_t freq, uint32_t duration_ms)
{
    Buzzer_SetFrequency(freq);

    // B?t PWM
    TIM1->CCER |= TIM_CCER_CC1E;
    TIM1->CR1 |= TIM_CR1_CEN;

    // Delay tuong d?i (blocking)
    for (volatile uint32_t i = 0; i < duration_ms * 1000; i++);

    // T?t âm
    TIM1->CCER &= ~TIM_CCER_CC1E;
    TIM1->CR1 &= ~TIM_CR1_CEN;
}

int main(void)
{
  HAL_Init();
  SystemClock_Config();
	SystemCoreClockUpdate();
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_TIM1_Init();
	ADC_init();
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	game_init(&snake);
	lcd_init();
	fill_rectangle(0,0,WIDTH,HEIGHT,COLOR_WHITE);
	draw_string(15,55,COLOR_DARKRED,2,"call me");
	draw_string(60,90,COLOR_BLUE,2,"is ");
	draw_string(30,125,COLOR_DARKCYAN,2,"lan anh");
	HAL_Delay(2000);
	fill_rectangle(0,0,WIDTH,HEIGHT,COLOR_WHITE);

  while (1)
  {
		if(is_button_pressed2())
		{
			fill_rectangle(0,0,WIDTH,HEIGHT,COLOR_WHITE);
			trang_thai_menu = 1;
		}
		if(is_button_pressed1())
		{
			for (int i = 0; i < sizeof(melody)/2; i++) {
					uint16_t duration = 250 / noteDurations[i];
					Buzzer_PlayTone(melody[i], duration);   // PWM OUT
					HAL_Delay(duration * 1.3);        // ngh? 30% gi?a n?t
			}
			for (int i = 0; i < sizeof(mario_melody)/2; i++) {
					int duration = 2000 / mario_duration[i];  // càng l?n càng nhanh
					if (mario_melody[i] != 0)
							Buzzer_PlayTone(mario_melody[i], duration); // PWM OUT
					HAL_Delay(duration * 1.3);   // ngh? 30%
			}
			
		}
		if(trang_thai_menu == 1)
		{
				draw_string(35,20,COLOR_RED,1,"Chosing_game");
				draw_string(35,55,COLOR_DARKGREEN,1,"Flappy Bird");
				draw_string(35,90,COLOR_DARKGREEN,1,"Snake");
				draw_string(35,125,COLOR_DARKGREEN,1,"image");
				adc_y = Read_ADC_Avg(2);
				
				// X? lý g?t lên ch?n m?c
				if(adc_y > 3000 && adc_triggered == 0)
				{
						adc_triggered = 1;
						dem++;
						if(dem > 3) dem = 1;
				}
				else if(adc_y < 2500 && adc_y > 1500)
				{
						adc_triggered = 0;
				}
				if(adc_y < 1000 && adc_triggered == 0)
				{
						adc_triggered = 1;
						dem--;
						if(dem < 1) dem = 3;
				}				
				if(is_button_pressed3())
				{
					adc_pulse = 1;

					switch(dem)
					{
						case 1:
							fill_rectangle(0,0,WIDTH,HEIGHT,COLOR_WHITE);
							trang_thai_menu = 0;
							game_running = 0;
							flappy_bird = 1;
							break;

						case 2:
							fill_rectangle(0,0,WIDTH,HEIGHT,COLOR_WHITE);
							trang_thai_menu = 0;
							flappy_bird = 0;
							game_running = 1; // gi? s? flappy chua có game loop
							break;

						case 3:
							fill_rectangle(0,0,WIDTH,HEIGHT,COLOR_WHITE);
							draw_map(0,0,1,220,176,(uint16_t*)image_data_Image);
							HAL_Delay(1000);
							draw_map(0,0,1,220,176,(uint16_t*)image_data_Image1);
							HAL_Delay(1000);
							draw_map(0,0,1,220,176,(uint16_t*)image_data_Image3);
							trang_thai_menu = 0;
							flappy_bird = 0;
							game_running = 0;
							break;
					}
					continue;
				}
				else if(adc_y > 1500)
				{
						adc_pulse = 0;
				}
				switch(dem)
				{
						case 1:
								drawCircle(20,95,5,COLOR_WHITE,2);
								drawCircle(20,130,5,COLOR_WHITE,2);
								drawCircle(20,60,5,COLOR_CYAN,2);
								break;
						case 2:
								drawCircle(20,60,5,COLOR_WHITE,2);
								drawCircle(20,130,5,COLOR_WHITE,2);
								drawCircle(20,95,5,COLOR_CYAN,2);
								break;
						case 3:
								drawCircle(20,60,5,COLOR_WHITE,2);
								drawCircle(20,95,5,COLOR_WHITE,2);
								drawCircle(20,130,5,COLOR_CYAN,2);
								break;
				}
		}
		else if(game_running)
		{
				adc_x = Read_ADC_Avg(1);
				adc_y = Read_ADC_Avg(2);
				if(adc_x > 2300) 
						game_go_left(&snake);
				else if(adc_x < 1000)
						game_go_right(&snake);
				if(adc_y > 2500)
						game_go_down(&snake);
				else if(adc_y < 1000)
						game_go_up(&snake);
				game_move(&snake);
				game_loss_check(&snake);
				game_draw(&snake);
				HAL_Delay(150); 				
		}
		else if(flappy_bird)
		{		
			fill_rectangle(0,0,176,220,COLOR_WHITE);
			draw_string(40,80,COLOR_RED,1,"FLAPPY_BIRD");
			draw_string(20,130,COLOR_CYAN,1,"press the button");
			if(is_button_pressed())
			{		
		  	Buzzer_PlayTone(880, 300); // n?t A cao
				HAL_Delay(100);
				if(is_button_pressed()){}
				if(game_over == NO || (!is_button_pressed()))
				{
					score_old = score;
					c = 0;
					Init_Game();
					fill_rectangle(0,0,176,200,COLOR_WHITE);
					if (score_old > high_score) 
					{
						high_score = score_old;
						Print_Score(high_score, 150, COLOR_BROWN);
					}
					while(1)
					{
						bird_top = y_bird - 2;
						bird_bottom = y_bird + HEIGH_BIRD + 3;
						if (x1 == 70) {
							x2 = 176;
							heigh_pill2 = list_heigh[rand() % 15];
						}
						if (x2 == 70) {
							x1 = 176;
							heigh_pill1 = list_heigh[rand() % 15];
						}
						Draw_Pillar(x1, heigh_pill1);
						Draw_Pillar(x2, heigh_pill2);

						if (is_button_pressed()) 
						{
							Buzzer_PlayTone(880, 200); // n?t A (440Hz)
							y_bird -= 3;
							c = 1;
						} 
						else if (c) 
						{
							y_bird += 4;
						}
						if(y_bird >= 180)
							y_bird = 180;
						else if(y_bird <= 0)
							y_bird = 0;
						if (x1 > 70) 
						{
							x_com = x1;
							h_com = heigh_pill1 - 1;
						} 
						else 
						{
							x_com = x2;
							h_com = heigh_pill2 - 1;
						}
						if (bird_top <= 2 || bird_bottom >= HEIGH_SCREEN - 2) {
								game_over = YES;
								for(int i = 0;i < 1000;i+= 50)
								{
									Buzzer_PlayTone(i, 200); // n?t A (440Hz)
									HAL_Delay(50);
								}
								if(game_over == YES)
								{
									Game_Over();
									game_over = NO;
									break;
								}
							}
						// C?c 1
							if (x1 <= bird_right && x1 + WIDTH_PILL >= bird_left) {
									// Chim dang giao nhau vùng c?c
									if (bird_top <= heigh_pill1 || bird_bottom >= heigh_pill1 + DISTANCE) {
											game_over = YES;
											for(int i = 0;i < 1000;i+= 50)
												{
													Buzzer_PlayTone(i, 200); // n?t A (440Hz)
													HAL_Delay(50);
												}
											if(game_over == YES)
											{
												Game_Over();
												game_over = NO;
												break;
											}
									}
							}
							// C?c 2
							if (x2 <= bird_right && x2 + WIDTH_PILL >= bird_left) {
									if (bird_top <= heigh_pill2 || bird_bottom >= heigh_pill2 + DISTANCE) {
											game_over = YES;
											for(int i = 0;i < 1000;i+= 50)
												{
													Buzzer_PlayTone(i, 200); // n?t A (440Hz)
													HAL_Delay(50);
												}
											if(game_over == YES)
											{
												Game_Over();
												game_over = NO;
												break;
											}
									}
							}
						if (x1 == SCORED || x2 == SCORED) 
						{
							score++;
							Print_Score(score, X_SCORE, 0x001F);
						}
						if (c) 
						{
								Bird_Fly(y_bird);
								x1 -=2;
								x2 -=2;
						}
						HAL_Delay(5);
					}
				}
			}
		}		
  }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_1LINE;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 100-1;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 1000;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LCD_RST_Pin|LCD_RS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LCD_RST_Pin LCD_RS_Pin */
  GPIO_InitStruct.Pin = LCD_RST_Pin|LCD_RS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : LCD_CS_Pin */
  GPIO_InitStruct.Pin = LCD_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LCD_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : BT1_Pin BT2_Pin BT3_Pin BT4_Pin */
  GPIO_InitStruct.Pin = BT1_Pin|BT2_Pin|BT3_Pin|BT4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
