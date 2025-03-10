#include "Arduino.h"
#include "esp_log.h"
#include "U8g2lib.h"
#include "SPI.h"
#include "icons.h"

//Display
#define SPI_CLK 2
#define SPI_MOSI 15
#define SPI_CS 25
#define DC 4
#define RESET 26

//Teclado
#define TC_ESQ 27
#define TC_DIR 12
#define TC_CON 14
#define TC_CAN 13

U8G2_ST7565_ERC12864_ALT_F_4W_SW_SPI u8g2(U8G2_R0, SPI_CLK, SPI_MOSI, SPI_CS, DC, RESET);

static const char *TAG = "Setup";

int8_t selecionado = 0;

void inicializacao()
{
    pinMode(TC_ESQ, INPUT_PULLUP);
    pinMode(TC_DIR, INPUT_PULLUP);
    pinMode(TC_CON, INPUT_PULLUP);
    pinMode(TC_CAN, INPUT_PULLUP);

    u8g2.begin();
    u8g2.setContrast(80);
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_6x10_tr);
}

void desenhaIcon()
{
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_6x10_tr);
    u8g2.drawXBMP(1, 20, 34, 34, custom_char);
    u8g2.drawXBMP(47, 20, 34, 34, custom_char);
    u8g2.drawXBMP(93, 20, 34, 34, custom_char);

    switch (selecionado)
    {
    case 0:
        u8g2.drawStr(0, 10, " Instrumental Desemb. ");
        u8g2.drawXBMP(2, 21, 32, 32, epd_bitmap_Instrumental_Desembalado_Selected);
        u8g2.drawXBMP(48, 21, 32, 32, epd_bitmap_Instrumental_Embalado);
        u8g2.drawXBMP(94, 21, 32, 32, epd_bitmap_Kit_Cirurgico);
        break;
    case 1:
        u8g2.drawStr(0, 10, "Instrumental Embalado");
        u8g2.drawXBMP(2, 21, 32, 32, epd_bitmap_Instrumental_Desembalado);
        u8g2.drawXBMP(48, 21, 32, 32, epd_bitmap_Instrumental_Embalado_Selected);
        u8g2.drawXBMP(94, 21, 32, 32, epd_bitmap_Kit_Cirurgico);
        break;
    case 2:
        u8g2.drawStr(0, 10, " Kit Cirurgico e Tec. ");
        u8g2.drawXBMP(2, 21, 32, 32, epd_bitmap_Instrumental_Desembalado);
        u8g2.drawXBMP(48, 21, 32, 32, epd_bitmap_Instrumental_Embalado);
        u8g2.drawXBMP(94, 21, 32, 32, epd_bitmap_Kit_Cirurgico_Selected);
        break;
    case 3:
        u8g2.drawStr(0, 10, "  Plastico e Algodao  ");
        u8g2.drawXBMP(2, 21, 32, 32, epd_bitmap_Plastico_Algodao_Selected);
        u8g2.drawXBMP(48, 21, 32, 32, epd_bitmap_Liquidos);
        u8g2.drawXBMP(94, 21, 32, 32, epd_bitmap_Rec_Adicionais);
        break;
    case 4:
        u8g2.drawStr(0, 10, "       Liquidos       ");
        u8g2.drawXBMP(2, 21, 32, 32, epd_bitmap_Plastico_Algodao);
        u8g2.drawXBMP(48, 21, 32, 32, epd_bitmap_Liquidos_Selected);
        u8g2.drawXBMP(94, 21, 32, 32, epd_bitmap_Rec_Adicionais);

        break;
    case 5:
        u8g2.drawStr(0, 10, " Recursos Adicionais  ");
        u8g2.drawXBMP(2, 21, 32, 32, epd_bitmap_Plastico_Algodao);
        u8g2.drawXBMP(48, 21, 32, 32, epd_bitmap_Liquidos);
        u8g2.drawXBMP(94, 21, 32, 32, epd_bitmap_Rec_Adicionais_Selected);
        break;
    }

    u8g2.drawXBMP(57, 59, 6, 5, selecionado < 3 ? selectDot : dot);
    u8g2.drawXBMP(68, 59, 6, 5, selecionado >= 3 ? selectDot : dot);

    u8g2.sendBuffer();
}

void setup()
{
    ESP_LOGI(TAG, "Initializing");

    inicializacao();

    desenhaIcon();
}

void loop()
{
    if (!digitalRead(TC_DIR))
    {
        selecionado++;
        if (selecionado > 5)
            selecionado = 0;
        desenhaIcon();
        vTaskDelay(500);
    }
    if (!digitalRead(TC_ESQ))
    {
        selecionado--;
        if (selecionado < 0)
            selecionado = 5;
        desenhaIcon();
        vTaskDelay(500);
    }
    vTaskDelay(10);
}