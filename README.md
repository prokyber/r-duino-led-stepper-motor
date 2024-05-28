# Ovládání krokového motoru pomocí Ř-duino-LED
Cílem tohoto projektu bylo vytvořit jednoduchý způsob na ovládání krokového motoru s modulem L298N. Bude se skládat ze tří částí: Ř-duino-LED s rotačním enkodérem, modul L298N a krokový motor. Po zpuštění programu můžeme začít otáčet s rotačním enkodér a podle směru otáčení enkodéru se otočí i krokový motor. Signál z rotačního enkodéru budeme zpracovávat a posílat do modulu L298N, který ovládá krokový motor.

# Součástky
- Ř-duino-LED
- externí zdroj 12V 1,2A (min)
- krokový modul
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
Známí tež jako stepper motor je typ elektrického motoru, který se používá k posunu nebo rotaci v malých úsecích, známých jako kroky. Princip fungování krokového motoru je následující: Motor obsahuje několik komutátorů, které jsou přiřazeny k jednotlivým cívkám. Cívkové pásky jsou navrženy tak, že při přiřazení komutátorů k cívkám se vytváří elektromagnetické pole. Elektromagnetické pole způsobí pohyb cívkových pásků. Při pohybu cívkových pásků se motor pohybuje krokovým způsobem, tj. v malých úsecích.

# Zapojení

# Princip zapojení
Sledujeme výstupy enkodéru a porovnáváme je spolu, na zásadě tohoto porovnání poznáme jakým směrem enkodér otáčíme a pomocí funkce attachinterrupt budeme aktivovat krokový motor pouze pokud nastane změna ve výstupu enkodéru. Jakmile pootočíme s enkodérem program rozpozná jakým směrem otáčíme enkodér a určí směr pohybu. Jeden krok se skládá ze čtyř částí z toho upravuje, ale směr pouze 2 a 4 částí a ty program mění na zásadě směru (podrobnější popis v programu). Tento pohyb odešleme L298N modulu a ten na zásadě tohoto signálu sepne cívky a krokový motor se pohne o jeden jeho krok. Tento postup se bude opakovat vždy když pohneme enkodérem.

# Možné problémy
Pokud krokový motor nejezdí zkontrolujte si zapojení cívek a zapojení pokud jezdí motor obráceným směrem musíte prohodit cívky v modulu. Můžeme také prohodit piny S1 a S2 nebo obrátit piny propojující Ř-duino a L298N modul. Redukce enkodéru k motoru není dokonalá 1x1 je 1x3/4 neboli jedna otáčka enkodéru se projeví jako 3/4 otáčky krokového motoru. Při velké zátěži motoru se chladič na modulu zahřívá. Pokud budeme otáčet enkodér až moc rychle Ř-duino nebude stíhat signály enkodéru a motor se bude zasekávat.
