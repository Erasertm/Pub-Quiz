// GPIO35 - Up-Down - Move
// GPIO32 - BTN_A - OK

#include "Adafruit_ILI9341.h"
#include "Adafruit_GFX.h"

#define TFT_BLACK 0x0000
#define TFT_BLUE 0x001F
#define TFT_RED 0xF800
#define TFT_GREEN 0x07E0
#define TFT_CYAN 0x07FF
#define TFT_MAGENTA 0xF81F
#define TFT_YELLOW 0xFFE0
#define TFT_WHITE 0xFFFF

#define TFT_DC 21  // Data/Command VIDI X zaslona spojen je na PIN 21
#define TFT_CS 5   // Chip select VIDI X zaslona spojen je na PIN 5

#define speed 15  // Less is Fasster

const int btn_uid = 35;  // gumb gore dolje
const int BTN_A = 32;    //BTN_A Button

// stvaranje TFT objekta (zaslon)
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

int answer = 0;
int score = 0;
int Quest = 1;

void setup() {
  Serial.begin(115200);

  // definiramo input pinove tj. upravljačke gumbe
  pinMode(BTN_A, INPUT_PULLUP);  // A gumb mora biti definiran kao INPUT_PULLUP
  pinMode(btn_uid, INPUT_PULLUP);

  // inicijalizacija zaslona
  tft.begin();
  // postavljamo orijentaciju ekzaslonarana
  tft.setRotation(3);
  // definiramo boju pozadine
  tft.fillScreen(ILI9341_BLACK);
  // delay(2000);
}

void question_01() {
  const char* options[] = {
    " A) Paris Hilton   ",
    " B) Richard Hilton ",
    " C) Hilton         ",
    " D) Paris          "
  };
  // Display the screen header
  tft.setCursor(0, 0);
  Screen_Header();
  // Display the question and answers
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);

  tft.println("What is the capital");
  tft.println("of France?");
  tft.println("__________________________");

  for (int i = 0; i < 4; i++) {
    if (answer == (i + 1)) {
      tft.setTextColor(TFT_RED, TFT_YELLOW);
    } else {
      tft.setTextColor(TFT_WHITE, TFT_BLUE);
    }
    tft.println(options[i]);
  }

  tft.setTextColor(TFT_WHITE, TFT_BLUE);
}

void question_02() {
  // Display the screen header
  tft.setCursor(0, 0);
  Screen_Header();
  // Display the question and answers
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);

  tft.println("Who was the first");
  tft.println("President of");
  tft.println("the United States?");
  tft.println("__________________________");

  if (answer == 1) {
    tft.setTextColor(TFT_RED, TFT_YELLOW);
  } else {
    tft.setTextColor(TFT_WHITE, TFT_BLUE);
  }
  tft.println(" A) George Washington ");
  if (answer == 2) {
    tft.setTextColor(TFT_RED, TFT_YELLOW);
  } else {
    tft.setTextColor(TFT_WHITE, TFT_BLUE);
  }
  tft.println(" B) John Adams        ");
  if (answer == 3) {
    tft.setTextColor(TFT_RED, TFT_YELLOW);
  } else {
    tft.setTextColor(TFT_WHITE, TFT_BLUE);
  }
  tft.println(" C) Thomas Jefferson  ");
  if (answer == 4) {
    tft.setTextColor(TFT_RED, TFT_YELLOW);
  } else {
    tft.setTextColor(TFT_WHITE, TFT_BLUE);
  }
  tft.println(" D) James Monroe      ");
  tft.setTextColor(TFT_WHITE, TFT_BLUE);
}

void question_03() {

  const char* options[] = {
    " A) 6 million years   ",
    " B) 6.5 million years ",
    " C) 7 million years   ",
    " D) 7.5 million years "
  };

  // Display the screen header
  tft.setCursor(0, 0);
  Screen_Header();
  // Display the question and answers
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);

  tft.println("According to the book 'The");
  tft.println("Hitchhiker's Guide to the");
  tft.println("Galaxy,' how much time did");
  tft.println("the supercomputer Deep");
  tft.println("Thought take to answer the");
  tft.println("question 'What is the");
  tft.println("meaning of life, the");
  tft.println("universe, and everything?'");
  tft.println("__________________________");

  for (int i = 0; i < 4; i++) {
    if (answer == (i + 1)) {
      tft.setTextColor(TFT_RED, TFT_YELLOW);
    } else {
      tft.setTextColor(TFT_WHITE, TFT_BLUE);
    }
    tft.println(options[i]);
  }

  tft.setTextColor(TFT_WHITE, TFT_BLUE);
}

void question_04() {
}

void go_down() {
  answer++;
  if (answer > 4) {
    answer = 4;
  }
}

void go_up() {
  answer--;
  if (answer < 1) {
    answer = 1;
  }
}

void go_OK() {
  // Ne moežemo koristiti if uvjete jer će svaki puta odgvovor biti pogrešan onoliko koliko ifobva imamo
  // ne možemo koristiti switch jer provjeravamo dvije varijable
  if (answer == 4 && Quest == 1) {
    score++;
    Screen_OK_Answer();
  } else if (answer == 1 && Quest == 2) {
    score++;
    Screen_OK_Answer();
  } else if (answer == 4 && Quest == 3) {
    score++;
    Screen_OK_Answer();
  } else {
    Screen_Wrong_Answer();
  }
  answer = 0;
  Quest++;
}

void Screen_Header() {
  tft.setTextColor(TFT_YELLOW, TFT_RED);
  tft.setTextSize(4);
  tft.setCursor(0, 0);
  tft.println("   PUB QUIZ  ");
}

void End_Screen() {
  tft.fillScreen(ILI9341_BLACK);

  Screen_Header();

  tft.setTextColor(TFT_RED);
  tft.setTextSize(3);

  if (score > 0) {
    tft.println("=================");
    tft.println("Congratulations!");
    tft.println("=================");
    tft.setTextColor(TFT_GREEN);
    tft.setTextSize(2);
    tft.println("  ");
    tft.print("Your have ");
    tft.print(score);
    tft.println(" correct");
    if (score == 1) {
      tft.println("answer!");
    } else {
      tft.println("answers!");
    }
  } else {
    tft.println("*===============*");
    tft.println(" Better luck");
    tft.println("      next time!");
    tft.println("*===============*");
    tft.setTextColor(TFT_GREEN);
    tft.setTextSize(2);
    tft.println("  ");
    tft.println("Your don't have");
    tft.println("     correct answers!");
  }
  delay(5000);
}

void Screen_OK_Answer() {
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(TFT_RED);
  tft.setTextSize(3);
  tft.setCursor(0, 0);
  tft.println("Your Answes is");
  tft.println("CORRECT !!!");

  tft.setTextColor(TFT_GREEN);
  tft.setTextSize(2);
  tft.println("  ");
  tft.print("Your have ");
  tft.print(score);
  tft.println(" correct");
  if (score == 1) {
    tft.println("answer so far.");
  } else {
    tft.println("answers so far.");
  }
  delay(3000);
  tft.fillScreen(ILI9341_BLACK);
}

void Screen_Wrong_Answer() {
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(TFT_CYAN);
  tft.setTextSize(3);
  tft.setCursor(0, 0);
  tft.println("Your Answes was");
  tft.setTextColor(TFT_RED);
  tft.print("NOT ");
  tft.setTextColor(TFT_CYAN);
  tft.println("CORRECT !!!");

  tft.setTextColor(TFT_GREEN);
  tft.setTextSize(2);
  tft.println("  ");
  tft.print("Your have ");
  tft.print(score);
  tft.println(" correct");
  if (score == 1) {
    tft.println("answer so far.");
  } else {
    tft.println("answers so far.");
  }
  delay(3000);
  tft.fillScreen(ILI9341_BLACK);
}

void loop() {
  if (analogRead(btn_uid) > 4000) { go_up(); }
  if (analogRead(btn_uid) > 1800 && analogRead(btn_uid) < 2200) { go_down(); }
  if (analogRead(BTN_A) == 0) { go_OK(); }
  delay(speed);

  switch (Quest) {
    case 1:
      //do something when var equals 1
      question_01();
      break;

    case 2:
      //do something when var equals 2
      question_02();
      break;

    case 3:
      question_03();
      break;

    default:
      End_Screen();
      break;
  }
}
