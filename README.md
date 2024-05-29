# Ovládání krokového motoru pomocí Ř-duino-LED
Cílem tohoto projektu bylo vytvořit jednoduchý způsob na ovládání krokového motoru s modulem L298N. Bude se skládat ze tří částí: Ř-duino-LED s rotačním enkodérem, modul L298N a krokový motor. Po zpuštění programu můžeme začít otáčet s rotačním enkodér a podle směru otáčení enkodéru se otočí i krokový motor. Signál z rotačního enkodéru budeme zpracovávat a posílat do modulu L298N, který ovládá krokový motor.

# Součástky
- Ř-duino-LED
- externí zdroj 12V 1,2A (min)
- krokový motor
- [rotační enkodér](https://e-shop.prokyber.cz/vstupni/rotacni-enkoder/)
- [modul L298N](https://e-shop.prokyber.cz/periferie-pro-mikrokontrolery/h-mustek/)
- [vodiče](https://e-shop.prokyber.cz/kabely--vodice/dupont-kabel/)

# Rotační enkodér
<img alt="Rotační enkóder" src="https://github.com/prokyber/r-duino-led-stepper-motor/blob/main/img/rotacni_enkoder.jpg" style="Height: 40vh;">

Jedná se o rotační vstupní součástka, která při otáčení její osou poskytuje informaci o této rotaci a také jejím směru. Zároveň tento typ rotačního enkodéru obsahuje i tlačítko, které lze aktivovat stiskem celé osy enkodéru. V kombinaci s Ř-duinem tak lze tento enkodér využít jako ovládací prvek pro všemožná zapojení, například jako ovladač pro pohyb v menu či jako digitální potenciometr pro řízení servomotorů. Velkou výhodou při srovnání s běžnými potenciometry je ten fakt, že u rotačního enkodéru není omezen počet otáček a můžeme tedy osou enkodéru otáčet donekonečna na obě strany. Enkodér má disk s kontaktními pintami rovnoměrně umístěnými od sebe. Když začneme otáčet knoflíkem, disk se také pohybuje a dostává se do kontaktu s výstupními kolíky S1 a S2 jeden po druhém, čímž generuje dvě čtvercové vlny současně. Ty mi můžeme porovnat a zjistit kterým směrem se enkodér otáčí.

# L298N
<img alt="L298N" src="https://github.com/prokyber/r-duino-led-stepper-motor/blob/main/img/L298N.webp" style="Height: 40vh;">

Jedná se o inteligentní motorový řidič (Motor Driver IC) na bázi CMOS, který je schopný řídit dva DC motory nebo jeden krokový motor, jako v našem případě. Obvod L298N je široce používán v mnoha aplikacích, jako jsou roboti, automatizované systémy, chytré domácnosti, průmyslové aplikace a mnoho dalších. Obvod L298N má několik vlastností, které ho dělají vhodným pro řízení motorů.

# Krokový motor
<img alt="Korokový motor" src="https://github.com/prokyber/r-duino-led-stepper-motor/blob/main/img/obr%C3%A1zek3.png" style="Height: 40vh;">

Známí tež jako stepper motor je typ elektrického motoru, který se používá k posunu nebo rotaci v malých úsecích, známých jako kroky. Princip fungování krokového motoru je následující: Motor obsahuje několik komutátorů, které jsou přiřazeny k jednotlivým cívkám. Cívkové pásky jsou navrženy tak, že při přiřazení komutátorů k cívkám se vytváří elektromagnetické pole. Elektromagnetické pole způsobí pohyb cívkových pásků. Při pohybu cívkových pásků se motor pohybuje krokovým způsobem, tj. v malých úsecích.

# Zapojení
<img alt="První zapojíme rotační enkodér u, kterého zapojíme zem (GND) do GND na Ř-duino a to samé s 5V podle diagramu. Poté zapojíme z enkodéru S1 a S2, tlačítko (KEY) v tomto zapojení vynecháme. S1 a S2 zapojíme do pinů 2 a 3 na pravé straně podle diagramu. Dále zapojíme vodiče mezi Ř-duino a L298N a to na piny 4, 5, 6 a 7 na pravé straně podle diagramu. Před tím než zapojíme čtyři kabely z Ř-duina zapojíme do L298N junpery, ty zapojíme do pinů ENA a ENB ty se nachází v řadě 6 pinů a mi je zapojíme do krajních pinů tak aby byla uprostřed volná řada 4 pinů a do těchto 4 pinů zapojíme naše ovládací kabely z Ř-duina. Externí zdroj na 12V zapojíme do levého konektoru na modulu L298N a mínus na prostřední podle diagramu. Na zapojení krokového motoru potřebujeme kabel na propojení z krokového motoru (vašeho výběru) a z tohoto kabelu pak do modulu L298N, kde zapojíme kabely po dvou do stran modulu a to dvojice cívek. Pokud nevíte které kabely jsou dvojice můžeme to změřit ohmmetrem nebo pípákem na multimetru. Dvojice na ohmmetru budou mít společný odpor a ty které nejsou zapojené na cívce mají odpor mimo rozsah. S pípákem je postup podobný vyzkoušíte dvojice a ty které budou pípat jsou zapojené spolu na cívce krokového motoru a tyto dvojice zapojíme do stran modulu. Poté už zbývá jen nahrát na Ř-duino program a jakmile bude program nahraný a zdroj zapnutý můžete zapojit volný jumper do modulu a začít hýbat s enkodérem a krokový motor by měl kopírovat vaše pohyby." src="https://github.com/prokyber/r-duino-led-stepper-motor/blob/main/img/Stepper_motor_zapojeni.png" style="Height: 60vh;">

(poznámka: "Enable" piny jsou společně propojené jumpery. Je jednoduché si tohoto na schématu nevšimnout.)

Po zapojení obvadu je ještě nutné připojit ke L298N externí zdroj. Připojte jej na piny +12 a GND.

# Princip zapojení
Sledujeme výstupy enkodéru a porovnáváme je spolu, na zásadě tohoto porovnání poznáme jakým směrem enkodér otáčíme a pomocí funkce attachinterrupt budeme aktivovat krokový motor pouze pokud nastane změna ve výstupu enkodéru. Jakmile pootočíme s enkodérem program rozpozná jakým směrem otáčíme enkodér a určí směr pohybu. Jeden krok se skládá ze čtyř částí z toho upravuje, ale směr pouze 2 a 4 částí a ty program mění na zásadě směru (podrobnější popis v programu). Tento pohyb odešleme L298N modulu a ten na zásadě tohoto signálu sepne cívky a krokový motor se pohne o jeden jeho krok. Tento postup se bude opakovat vždy když pohneme enkodérem.

# Kód
(soubor ke stažení výše)

``` cpp
#include <Arduino.h>

//určení pinů pro řduino
#define in1 4  //piny pro L298N modul
#define in2 5
#define in3 6
#define in4 7
#define encoder0PinA 2  //piny rotačního enkodéru
#define encoder0PinB 3

int A = HIGH;  //proměná pro změnu směru
int B = LOW;

//opakující se smyčka
void setup() {
  pinMode(in1, OUTPUT);  //definice pinů pro L298N modul
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT); 
  pinMode(encoder0PinA, INPUT);
  pinMode(encoder0PinB, INPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(encoder0PinA), doEncoder, CHANGE);  //tato část spustí "void doencoder" pouze pokud nastane změna na enkodéru
} 

//tato smyška se jednou spustí po jednom pohybu enkodéru
void doEncoder(){ 
if(digitalRead(encoder0PinB) == digitalRead(encoder0PinA)){  //tato část rozhoduje jestli se enkodér otáčí vpčed nebo vzat
    A = LOW;
    B = HIGH;
   Serial.println("vpřed");  //upravení cyklusu vpřed
  }
  else{
    A = HIGH;
    B = LOW;
    Serial.println("vzad");  //upravení cyklusu vzat
  }
   
  digitalWrite(in1, HIGH);  //cyklus krokáče který se ovlivnujě na zísadě hořejšího rozpoznání
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(5);

  digitalWrite(in1, A);
  digitalWrite(in2, B);
  digitalWrite(in3, B);
  digitalWrite(in4, A);
  delay(5);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(5);

  digitalWrite(in1, B);
  digitalWrite(in2, A);
  digitalWrite(in3, A);
  digitalWrite(in4, B);
  delay(5);
}

void loop(){}  //bez loopu arduino ide nás nenechá nahrát code, tato část nemá jiný účel}
```


# Možné problémy
Pokud krokový motor nejezdí zkontrolujte si zapojení cívek a zapojení pokud jezdí motor obráceným směrem musíte prohodit cívky v modulu. Můžeme také prohodit piny S1 a S2 nebo obrátit piny propojující Ř-duino a L298N modul. Redukce enkodéru k motoru není dokonalá 1x1 je 1x3/4 neboli jedna otáčka enkodéru se projeví jako 3/4 otáčky krokového motoru. Při velké zátěži motoru se chladič na modulu zahřívá. Pokud budeme otáčet enkodér až moc rychle Ř-duino nebude stíhat signály enkodéru a motor se bude zasekávat.
