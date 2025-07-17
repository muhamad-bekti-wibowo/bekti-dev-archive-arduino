#include <LiquidCrystal_PCF8574.h>
LiquidCrystal_PCF8574 lcd(0x27);
#include <PZEM004Tv30.h>


PZEM004Tv30 pzem(12, 13);

float Power, Energy, Voltase, Current, VA, CQ, SQ, VAR, biaya;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(20, 4);
  lcd.setBacklight(255);
  lcd.print("HELLO WORLD!");
}

void loop() {
  // put your main code here, to run repeatedly:
  Power = pzem.power();
  if (isnan(Power))
  { Serial.println ("Gagal membaca power");

  }
  else
  { Serial.print ("Power : ");
    Serial.print (Power);
    Serial.println (" W");
  }
  Energy = pzem.energy();
  if (isnan(Energy))
  { Serial.println ("Gagal membaca energi");

  }
  else
  { Serial.print ("Energy : ");
    Serial.print (Energy);
    Serial.println (" KW");
  }
  Voltase = pzem.voltage();
  if (isnan(Voltase))
  { Serial.println ("Gagal membaca voltase");

  }
  else
  { Serial.print ("Voltase : ");
    Serial.print (Voltase);
    Serial.println (" V");
  }
  Current = pzem.current();
  if (isnan(Current))
  { Serial.println ("Gagal membaca cureent");

  }
  else
  { Serial.print ("Current : ");
    Serial.print (Current);
    Serial.println (" A");
  }
  if (Current > 0 )
  { VA = Voltase * Current ;
    VAR = sqrt(pow(VA,2) - pow(Power,2));
   // biaya / H Rp1.352
   biaya = Energy * 1352 ;
    CQ = Power  / VA  ;
    SQ = 1  - CQ  ;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(millis());
    lcd.setCursor(11, 0);
    lcd.print("Rp ");
    lcd.print(biaya);
    lcd.setCursor(0, 1);
    lcd.print(VA);
    lcd.print(" VA ");
    lcd.setCursor(11, 1);
    lcd.print("CQ : ");
    lcd.print(CQ);
    lcd.setCursor(0, 2);
    lcd.print(Power);
    lcd.print(" W ");
    lcd.setCursor(11, 2);
    lcd.print(Voltase);
    lcd.print(" V ");
    lcd.setCursor(0, 3);
    lcd.print(VAR);
    lcd.print(" VAR ");
    lcd.setCursor(11, 3);
    lcd.print(Current); lcd.print(" A");

  }

  delay(1000);

}
