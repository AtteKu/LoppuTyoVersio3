Hotellin varausjärjestelmä 

1 Ohjelman toiminta 

Ohjelma koostuu päävalikosta, sekä muutamasta eri alivalikosta. Ohjelma antaa relevantit tiedot 
varauksia tehdessä ja valikoissa voi palata taaksepäin, jos tulee esimerkiksi vahinkopainalluksia. 
Ohjelma antaa käyttäjälle varoituksia annettaessa vääriä argumentteja ja pyytää käyttäjää 
valitsemaan oikean argumentin, siirtyäkseen ohjelmassa seuraavaan vaiheeseen.  

Ohjelma luo tekstitiedoston, johon varaukset tallennetaan, jotta varaukset eivät poistu, kun ohjelma 
suljetaan. Ohjelma tukee ääkkösiä käyttöliittymässä ja varauksia voi tehdä ääkkösillä, mutta varauksia 
haettaessa varaukset.txt-tiedostosta, ohjelma ei palauta ääkkösiä oikein. Haku kumminkin toimii 
ääkkösillä. 

Kun ohjelma käynnistetään se listaa huoneiden kokonaislukumäärän sekä erityyppisten huoneiden 
määrät. 

Päävalikko koostuu kolmesta eri valinnasta: tee varaus, hae varauksia ja sulje ohjelma. Numeroita 
painamalla valikoissa voi liikkua käyttäjän haluamiin suuntiin. Valikoissa liikutaan painamalla 
toimintoa vastaavaa numeroa ja painamalla sen jälkeen Enter-näppäintä.  

Varauksia tehdessä ohjelma pyytää käyttäjän haluamaa huonetyyppiä. Tässä vaiheessa käyttäjä voi 
valita huonetyypin tai palata takaisin päävalikkoon. Kun käyttäjä on valinnut huonetyypin, hän voi 
päättää itse huonenumeron vapaista olevista huoneista tai arpoa huoneen numeron. Tämän jälkeen 
ohjelma pyytää varaajan nimeä ja vietetyiden öiden määrää. Kun vaaditut tiedot on täytetty, ohjelma 
tulostaa kokonaishinnan, mahdollisen alennuksen ja varausnumeron. Tämän jälkeen ohjelma vielä 
antaa käyttäjälle mahdollisuuden varata lisää huoneita, jos käyttäjä niin tahtoo. 

Varauksia haettaessa, käyttäjä voi hakea varauksia nimellä tai varausnumerolla. Jos samalla nimellä 
on useita eri varauksia, ohjelma tulostaa ne kaikki, sekä olennaiset varaukseen liittyvät tiedot. 


2 Aliohjelmien toiminnasta 

Ohjelma on jaettu pääohjelmaan, sekä 11 aliohjelmaan. Tässä listattuna eri aliohjelmat ja niiden 
tarkoitukset: 

luoVarauksetTiedosto: Kun pääohjelma kutsuu tätä aliohjelmaa, aliohjelma tarkistaa varaukset.txt 
tiedoston olemassaolon, jos tätä tiedostoa ei ole, aliohjelma luo varaukset.txt-tiedoston. 

muunnaPieniksiKirjaimiksi: Tämä aliohjelma muuttaa isot kirjaimet pieniksi kirjaimiksi, kun 
pääohjelma kutsuu sitä, jotta käyttäjän hakiessa varaukset.txt-tiedostosta nimellä varauksia, ei ole 
väliä antaako käyttäjä nimen pienillä vai isoilla kirjaimilla. 

tallennaVaraukset: Tämä aliohjelma tallentaa ohjelmassa tehdyt varaukset varaukset.txt-tiedostoon 
ennen ohjelma sulkua, jotta varaukset pysyvät tallennettuina myös ohjelman sulkemisen jälkeen. 

lueVaraukset: Aliohjelman tarkoitus on hakea varaukset.txt-tiedostosta relevantit tiedot ja tallentaa 
ne varaukset-vektoriin myöhempää käyttöä varten ohjelmassa. Esimerkiksi, kun käyttäjä hakee 
aikaisempien varauksien tietoja. 

onkoVarattu: Tämä aliohjelma etsii vektorista huonenumeron perusteella, onko huone jo varattu, kun 
käyttäjä yrittää varata esimerkiksi huoneen numero 2. Jos huone on jo varattu ohjelma estää huoneen 
varauksen. 

luoVarausnumero: Aliohjelma luo satunnaisen viisinumeroisen varausnumeron. 

lisaaVaraus: Kyseinen aliohjelma luo/generoi uuden varauksen Varaus-rakenteeseen sekä asettaa 
tarpeelliset muuttujat (varausnumero, varaajan nimi, öiden määrä jne.) ja poistaa varatun huoneen 
vapaiden huoneiden listalta. Se myös ilmoittaa käyttäjälle onnistuneen varauksen ja varausnumeron. 

haeVarausnumerolla: Aliohjelma hakee annettua varausnumeroa varaukset-vektorista, jos ohjelma 
löytää vastaavan varausnumeron, ohjelma palauttaa varausnumeroon liittyvät relevantit tiedot, kuten 
varaajan nimi, huonenumero jne. Jos varausta ei löydy ilmoittaa ohjelma, että varausta ei löytynyt. 

haeNimella: Tämä aliohjelma toimii samantyylisesti kuin haeVarausnumerolla-aliohjelma, mutta 
hakee varauksia varaajan nimen perusteella. Aliohjelma muuntaa sekä käyttäjän syöttämän nimen 
että varauksissa olevat nimet pieniksi kirjaimiksi helpottaakseen nimellä hakemista. Jos aliohjelma 
löytää käyttäjän pyytämän nimen, se palauttaa nimeen liitetyt relevantit tiedot, kuten varausnumeron, 
huonenumero, yöt ja hinnan. Jos varausta ei löydy, ohjelma ilmoittaa, että varausta ei löytynyt. 

lueKokonaisluku: Aliohjelman tarkoituksena on tarkistaa käyttäjän antamien syötteiden sopivuus 
tietyissä pääohjelman suoritusvaiheissa. Esimerkiksi, kun käyttäjä tekee valintaa päävalikossa, 
aliohjelma varmistaa, että syöte on kelvollinen kokonaisluku. Jos syöte ei ole kelvollinen, aliohjelma 
palauttaa virhetilan ja pyytää käyttäjää antamaan uuden syötteen. Kun syöte on kelvollinen, 
aliohjelma yhdistää sen oikeaan valintaan, kuten esimerkiksi, kun käyttäjä antaa syötteen 1 
päävalikossa, ohjelma tietää yhdistää valinnan kohtaan "Tee varaus". 

Alennus: Tämä aliohjelma arpoo käyttäjälle 0, 10 tai 20 prosentin alennuksen loppusummaan 
tilauksen yhteydessä. Tämä vielä muutetaan kertoimeksi, jota käytetään loppusummaa laskiessa.
