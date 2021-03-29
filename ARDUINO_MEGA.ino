#include <Servo.h>
Servo portal_ma;
Servo portal_A1;
Servo portal_A2;
Servo portal_B1;
#include <ThreeWire.h>
#include <RtcDS1302.h>

ThreeWire myWire(4, 5, 2); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);
#define countof(a) (sizeof(a) / sizeof(a[0]))

int jam, menit, detik;

int tutup_A1, tutup_A2, tutup_A3, tutup_A4;
int tutup_B1, tutup_B2, tutup_B3, tutup_B4;
String data, data2;
char c;

const int sensor_utama =  43;
const int sensor_a1 =  35;
const int sensor_a2 =  31;
const int sensor_b1 =  47;


int mulai_timer = 70, waktu, verifikasi_yes;
int a1_kunci = 1;
int x, x1;
String reset_portal, tutup_portal, Trigger_popup, Trigger_barcode;

void setup() {
  Serial.begin(9600);
  Serial3.begin(115200);
  Serial.print("tester/");
  portal_ma.attach(45);
  portal_A1.attach(37);
  portal_A2.attach(33);
  portal_B1.attach(49);

  Rtc.Begin();
  pinMode(sensor_utama, INPUT);//portal utama
  pinMode(sensor_a1, INPUT);//portal a1
  pinMode(sensor_a2, INPUT);//portal a2
  pinMode(sensor_b1, INPUT);//portal b1



  portal_ma.write(150);
  portal_A1.write(150);
  portal_A2.write(150);
  portal_B1.write(100);



  delay(2000);
  portal_ma.write(100);
  portal_A1.write(100);
  portal_A2.write(100);
  portal_B1.write(150);

  tutup_A1 = 0;
  tutup_A2 = 0;
  tutup_B1 = 0;
  Trigger_popup = "0";
  reset_portal = "0";

  pinMode(22, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(28, OUTPUT);
  digitalWrite(22, HIGH);
  digitalWrite(24, HIGH);
  digitalWrite(26, HIGH);
  digitalWrite(28, HIGH);

}



void loop() {


  if (Serial3.available() > 0) {
    char c = Serial3.read();
    if (c != '/') {
      data += c;
    }
    else {
      data = "";
    }
  }

  RtcDateTime now = Rtc.GetDateTime();
  printDateTime(now);
  Serial.print(detik);
  Serial.print("*");
  Serial.print(Trigger_barcode);
  Serial.print(",");
  Serial.print(Trigger_popup);
  Serial.print(",");
  Serial.print(tutup_portal);
  Serial.print(",");
  Serial.print(reset_portal);
  Serial.println("#");



  if (detik == mulai_timer ) {
    Serial.println("twaktu tunggu habis");
    Serial.println("mengirim pop up");
    Trigger_popup = "1";
    digitalWrite(24, LOW);
    mulai_timer = 70;  //kasih nilai ambang
    a1_kunci = 2;
    //delay(1000);
    Serial.println("mereset pop up");
    //digitalWrite(24, HIGH);
    //Trigger_popup = "0";
  }


  if (data == "k") {//menerima pop up verifikasi no
    Serial.println("kendaraan A1 tidak jadi masuk");
    portal_A1.write(100);//portal A1 tertutup
    tutup_A1 = 0;
    Trigger_popup = "0";
    digitalWrite(24, HIGH);
    a1_kunci = 1;
  }
  if (data == "m") {//menerima pop up verifikasi yes
    verifikasi_yes = 1;
    Trigger_popup = "0";
    digitalWrite(24, HIGH);
  }
  if (verifikasi_yes == 1) {
    Serial.println("kendaraan A1 jadi masuk cuman lama");
    if (digitalRead(sensor_a1) == 0) {
      delay(100);
      if (digitalRead(sensor_a1) == 1) {
        Serial.println("kendaraan A1 masuk");
        portal_A1.write(100);//portal A1 tertutup
        tutup_A1 = 2;
        a1_kunci = 2;
      }
    }
    verifikasi_yes = 0;
  }





  if (data == "1") {
    if (a1_kunci == 1) {
      if (detik > 54) {
        x = 60 - detik;
        x1 = 5 - x;
        mulai_timer = x1;
      }
      else {
        mulai_timer = detik + 5;
      }
    }
    if (tutup_A1 == 0) {
      if (digitalRead(sensor_a1) == 1) {
        delay(100);
        //Serial.print("kendaraan A1 masuk/");
        if (digitalRead(sensor_a1) == 1) {
          portal_A1.write(150);//portal A1 terbuka
          tutup_A1 = 1;
        }
      }
    }
    if (tutup_A1 == 2) {
      if (digitalRead(sensor_a1) == 1) {
        delay(100);
        if (digitalRead(sensor_a1) == 1) {
          portal_A1.write(150);//portal A1 terbuka
          tutup_A1 = 3;
        }
      }
    }
  }




  if (data == "2") {
    if (tutup_A2 == 0) {
      if (digitalRead(sensor_a2) == 1) {
        delay(100);
        if (digitalRead(sensor_a2) == 1) {
          portal_A2.write(150);//portal A1 terbuka
          //Serial.print("kendaraan A2 masuk/");
          tutup_A2 = 1;
        }
      }
    }
    if (tutup_A2 == 2) {
      if (digitalRead(sensor_a2) == 1) {
        delay(100);
        if (digitalRead(sensor_a2) == 1) {
          portal_A2.write(150);//portal A1 terbuka
          tutup_A2 = 3;
        }
      }
    }
  }




  if (data == "5") {
    if (tutup_B1 == 0) {
      if (digitalRead(sensor_b1) == 1) {
        delay(100);
        //Serial.print("kendaraan B1 masuk/");
        if (digitalRead(sensor_b1) == 1) {
          portal_B1.write(100);//portal A1 terbuka
          tutup_B1 = 1;
        }
      }
    }
    if (tutup_B1 == 2) {
      if (digitalRead(sensor_b1) == 1) {
        delay(100);
        if (digitalRead(sensor_b1) == 1) {
          portal_B1.write(100);//portal A1 terbuka
          tutup_B1 = 3;
        }
      }
    }
  }








  if (digitalRead(sensor_utama) == 0) {
    Trigger_barcode = "x";
    tutup_portal = "B";
    digitalWrite(22, LOW);
    digitalWrite(26, HIGH);
    if (data == "a") {
      portal_ma.write(150);//portal utama terbuka
    }
  }


  if (digitalRead(sensor_utama) == 1) {
    portal_ma.write(100);//portal utama tertutup
    tutup_portal = "b";
    Trigger_barcode = "X";
    digitalWrite(22, HIGH);
    digitalWrite(26, LOW);
  }







  if (tutup_A1 == 1) {
    if (digitalRead(sensor_a1) == 0) {
      delay(100);
      if (digitalRead(sensor_a1) == 1) {
        Serial.println("kendaraan A1 masuk");
        portal_A1.write(100);//portal A1 tertutup
        tutup_A1 = 2;
        a1_kunci = 2;
      }
    }
  }
  if (tutup_A1 == 3) {
    if (digitalRead(sensor_a1) == 0) {
      delay(100);
      if (digitalRead(sensor_a1) == 1) {
        Serial.println("kendaraan A1 keluar");
        portal_A1.write(100);//portal A1 tertutup
        reset_portal = "c";
        digitalWrite(28, LOW);
        tutup_A1 = 0;
        a1_kunci = 1;
      }
    }
  }



  if (tutup_A2 == 1) {
    if (digitalRead(sensor_a2) == 0) {
      delay(100);
      if (digitalRead(sensor_a2) == 1) {
        Serial.println("kendaraan A2 masuk");
        portal_A2.write(100);//portal A1 tertutup
        tutup_A2 = 2;
      }
    }
  }
  if (tutup_A2 == 3) {
    if (digitalRead(sensor_a2) == 0) {
      delay(100);
      if (digitalRead(sensor_a2) == 1) {
        Serial.println("kendaraan A2 keluar");
        portal_A2.write(100);//portal A1 tertutup
        reset_portal = "c";
        digitalWrite(28, LOW);
        tutup_A2 = 0;
      }
    }
  }




  if (tutup_B1 == 1) {
    if (digitalRead(sensor_b1) == 0) {
      delay(100);
      if (digitalRead(sensor_b1) == 1) {
        Serial.println("kendaraan B1 masuk");
        portal_B1.write(150);//portal A1 tertutup
        tutup_B1 = 2;
      }
    }
  }
  if (tutup_B1 == 3) {
    if (digitalRead(sensor_b1) == 0) {
      delay(100);
      if (digitalRead(sensor_b1) == 1) {
        Serial.println("kendaraan B1 keluar");
        portal_B1.write(150);//portal A1 tertutup
        reset_portal = "c";
        digitalWrite(28, LOW);
        tutup_B1 = 0;
      }
    }
  }


}












void printDateTime(const RtcDateTime& dt)
{
  char datestring[20];
  snprintf_P(datestring,
             countof(datestring),
             PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
             dt.Month(),
             dt.Day(),
             dt.Year(),
             dt.Hour(),
             dt.Minute(),
             dt.Second() );

  detik = dt.Second();
  //Serial.print(datestring);
}
