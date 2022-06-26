// C++ code
//
#define BUTTON_RIGHT 8
#define BUTTON_SELECT 9
#define BUTTON_LEFT 10
#define TIME 3000
#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

void setup()
{
    lcd.begin(16, 2);
    pinMode(BUTTON_RIGHT, INPUT);
    pinMode(BUTTON_LEFT, INPUT);
    Serial.begin(9600);
}

int contador = 0;
short button_left_before = LOW;
short button_right_before = LOW;
short button_select_before = LOW;
char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
unsigned long millis_before = 0;
char guessWord[] = "PRUEBA";
int wordSize = strlen(guessWord);
char guessLetter;
short i;
short lifePoints = 3;
short correctLetter;
short totalRight;
short selected;
short gameStarted = 0;
short level = 0;
short gameLost = 0;
short flagTitle = 0;
int action = 1;



void clearCR(int col, int row)
{
    lcd.setCursor(col, row);
    lcd.print(" ");
}

void show_title()
{   
    if(flagTitle == 0)
    {
        lcd.setCursor(4, 0);
        lcd.print("AHORCADO");
        flagTitle = 1;
    }
}

void gameStart()
{ 
    if (gameStarted == 0)
    {   
        clearCR(10, 0);
        lifePoints = 3;
        show_blanks();
        contador = 0;
        gameStarted = 1;
    }
}

void show_blanks()
{
    lcd.setCursor(3, 1);
    for (i = 0; i < wordSize; i++)
    {
        lcd.print("_");
    }
}

void show_life_points()
{
    lcd.setCursor(11, 0);
    lcd.print("LP");
    switch (lifePoints)
    {
        case 3:
            lcd.print("***");
        break;

        case 2:
            clearCR(15, 0);
        break;

        case 1:
            clearCR(14, 0);
        break;
        
        case 0:
            clearCR(13, 0);
        break;
    }
}

void show_game_over()
{
    lcd.clear();
    lcd.setCursor(6,0);
    lcd.print("GAME");
    lcd.setCursor(6,1);
    lcd.print("OVER");
}

void show_leters_left()
{
    lcd.setCursor(3, 0);
    for (i = 2; i >= 1; i--)
    {
        if (contador - i >= 0)
        {
            lcd.print(letters[contador - i]);
        }
        else
        {
            if (contador == 0)
            {
                lcd.print(letters[24]);
                lcd.print(letters[25]);
                break;
            }
            else
            {
                lcd.print(letters[25]);
            }
        }
    }
}

void show_letters_right()
{
    lcd.setCursor(8, 0);
    for (i = 1; i <= 2; i++)
    {
        if (contador + i <= 25)
        {
            lcd.print(letters[contador + i]);
        }
        else
        {
            if (contador == 25)
            {
                lcd.print(letters[0]);
                lcd.print(letters[1]);
                break;
            }
            else
            {
                lcd.print(letters[0]);
            }
        }
    }
}

void show_letter()
{
    lcd.setCursor(5, 0);
    lcd.print(">");
    lcd.print(letters[contador]);
    lcd.print("<");
}

void show_last_letter()
{
    if(guessLetter != NULL)
    {
        lcd.setCursor(0, 0);
        lcd.print(guessLetter);
    }
}

void press_button_left()
{
    int button_left_now = digitalRead(BUTTON_LEFT);
    if (button_left_now == HIGH && button_left_before == LOW)
    {
        contador--;
        if (contador < 0)
        {
            contador = 25;
        }
    }
    button_left_before = button_left_now;
}

void press_button_right()
{
    int button_right_now = digitalRead(BUTTON_RIGHT);
    if (button_right_now == HIGH && button_right_before == LOW)
    {
        contador++;
        if (contador > 25)
        {
            contador = 0;
        }
    }
    button_right_before = button_right_now;
}

void press_button_select()
{
    int button_select_now = digitalRead(BUTTON_SELECT);
    if (button_select_now == HIGH && button_select_before == LOW)
    {
        guessLetter = letters[contador];
        correctLetter = 0;
        selected = 1;

        for (i = 0; i < wordSize; i++)
        {
            if (guessLetter == guessWord[i])
            {
                lcd.setCursor(i + 3, 1);
                lcd.print(guessLetter);
                correctLetter = 1;
                totalRight++;
            }
        }
    }
    button_select_before = button_select_now;
}

void actions()
{
    switch (action)
    {
    case 1:
        gameStart();
    break;

    case 2:
        clear_screen();
        show_game_over();
        gameStarted = 0;
    break;    
	case 3:
      
      break;
    }
}

void sequence()
{  
  	int retorno = 0;
    unsigned long millis_now = millis();
    if (millis_now - millis_before >= TIME)
    {
        actions();
              
        millis_before = millis_now;
    }
}

void loop()
{   
    show_title();
    sequence();  	
    if(gameStarted == 1)
    {
        show_life_points();
        press_button_left();
        press_button_select();
        press_button_right();
        show_letters_right();
        show_letter();
        show_leters_left();
      	show_last_letter();
    }

    if (selected == 1 && correctLetter == 0)
    {
        selected = 0;
        lifePoints--;
      
    }

    delay(100);
}