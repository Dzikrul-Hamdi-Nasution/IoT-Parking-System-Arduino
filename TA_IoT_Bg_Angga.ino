
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>


#define FIREBASE_HOST "test-iot-kos.firebaseio.com"
#define FIREBASE_AUTH "EVxPSBXAeKBPh46gGxMdMBUYzcBF4swWVJQxp50p"
//#define WIFI_SSID "KampungTongah"
//#define WIFI_PASSWORD "sayasiapaya"

//#define WIFI_SSID "SALAM ELECTRONICS"
//#define WIFI_PASSWORD "btn-primary"

#define WIFI_SSID "OPPO Reno"
#define WIFI_PASSWORD "mackenzit"

//#define WIFI_SSID "UMANETA_WIFI"
//#define WIFI_PASSWORD "12345678"

SoftwareSerial s(4, 5);//komunikasi ke serial arduino dari esp32
String dataIn;
String dt[10];
int i, batas;
boolean parsing = false;
String data;

String reset_portal, tutup_portal, Trigger_popup, Trigger_barcode;

void setup() {
  s.begin(9600);
  Serial.begin(115200);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  pinMode(16, INPUT);//pin 22 arduino = Trigger_barcode
  pinMode(5, INPUT);//pin 24 arduino = Trigger_popup
  pinMode(4, INPUT);//pin 26 arduino = tutp_portal
  pinMode(0, INPUT);//pin 28 arduino = reset_portal




}

int kunci_popup;
void loop() {

  if (kunci_popup == 2) {
    if (digitalRead(5) == LOW) {
      Firebase.setString("notifikasi/nilai", "Q");
      kunci_popup = 1;
    }
  }
  if (digitalRead(16) == LOW) {
    Firebase.setString("data barcode/nilai", "tester");
  }
  if (digitalRead(4) == LOW) {
    Firebase.setString("portal masuk/nilai", "0");
    Firebase.setString("data barcode/nilai", "0");
  }
  if (digitalRead(2) == LOW) {
    Firebase.setString("portal keluar/nilai", "0");
  }

  if (Firebase.getString("notifikasi/nilai") == ("m")) {
    Serial.print("m/");//verifikasi yes
    Serial.print("m/");//verifikasi yes
    Serial.print("m/");//verifikasi yes
    Firebase.setString("notifikasi/nilai", "0");
    delay(100);
    kunci_popup = 2;
  }
  if (Firebase.getString("notifikasi/nilai") == ("k")) {
    Serial.print("k/");//verifikasi no
    Serial.print("k/");//verifikasi no
    Serial.print("k/");//verifikasi no
    Firebase.setString("notifikasi/nilai", "0");
    delay(100);
    kunci_popup = 2;
  }
  if (Firebase.getString("notifikasi/nilai") == ("0")) {
    kunci_popup = 2;
  }


  /*
    reset_portal = dt[3];
    tutup_portal = dt[2];
    Trigger_popup = dt[1];
    Trigger_barcode = dt[0];

      if (Trigger_popup == "1") {
        Firebase.setString("notifikasi/nilai", "Q");
      }
      if (Trigger_popup == "0") {
        Firebase.setString("notifikasi/nilai", "0");
      }

      if (Trigger_barcode == "x") {
        Firebase.setString("portal masuk/nilai", "0");
        Firebase.setString("data barcode/nilai", "tester");
      }
      if (tutup_portal == "b") {
        Firebase.setString("portal masuk/nilai", "0");
        Firebase.setString("data barcode/nilai", "0");
      }
      if (reset_portal == "c") {
        Firebase.setString("portal keluar/nilai", "0");
      }
  */

  if (Firebase.getString("portal masuk/nilai") == ("1")) {
    Serial.print("a/");//kirim data serial utk buka portal masuk ke arduino melalui software serial
    if (Firebase.getString("yang dipilih/nilai") == ("1")) {
      Serial.print("a/");
      Serial.print("1/");
      //Firebase.setString("portal masuk/nilai", "0");
    }
    if (Firebase.getString("yang dipilih/nilai") == ("2")) {
      Serial.print("a/");
      Serial.print("2/");
      Firebase.setString("portal masuk/nilai", "0");
    }
    if (Firebase.getString("yang dipilih/nilai") == ("3")) {
      Serial.print("a/");
      Serial.print("3/");
      Firebase.setString("portal masuk/nilai", "0");
    }
    if (Firebase.getString("yang dipilih/nilai") == ("4")) {
      Serial.print("a/");
      Serial.print("4/");
      Firebase.setString("portal masuk/nilai", "0");
    }
    if (Firebase.getString("yang dipilih/nilai") == ("5")) {
      Serial.print("a/");
      Serial.print("5/");
      Firebase.setString("portal masuk/nilai", "0");
    }
    if (Firebase.getString("yang dipilih/nilai") == ("6")) {
      Serial.print("a/");
      Serial.print("6/");
      Firebase.setString("portal masuk/nilai", "0");
    }
    if (Firebase.getString("yang dipilih/nilai") == ("7")) {
      Serial.print("a/");
      Serial.print("7/");
      Firebase.setString("portal masuk/nilai", "0");
    }
    if (Firebase.getString("yang dipilih/nilai") == ("8")) {
      Serial.print("a/");
      Serial.print("8/");
      Firebase.setString("portal masuk/nilai", "0");
    }
    Serial.print("a/");
  }

  if (Firebase.getString("portal keluar/nilai") == ("A")) {
    Serial.print("1/");//kirim data serial utk buka portal keluar ke arduino melalui software serial
    Firebase.setString("portal keluar/nilai", "0");
    Serial.print("1/");
  }
  if (Firebase.getString("portal keluar/nilai") == ("B")) {
    Serial.print("2/");//kirim data serial utk buka portal keluar ke arduino melalui software serial
    Firebase.setString("portal keluar/nilai", "0");
    Serial.print("2/");
  }
  if (Firebase.getString("portal keluar/nilai") == ("C")) {
    Serial.print("3/");//kirim data serial utk buka portal keluar ke arduino melalui software serial
    Firebase.setString("portal keluar/nilai", "0");
    Serial.print("3/");
  }
  if (Firebase.getString("portal keluar/nilai") == ("D")) {
    Serial.print("4/");//kirim data serial utk buka portal keluar ke arduino melalui software serial
    Firebase.setString("portal keluar/nilai", "0");
    Serial.print("4/");
  }
  if (Firebase.getString("portal keluar/nilai") == ("E")) {
    Serial.print("5/");//kirim data serial utk buka portal keluar ke arduino melalui software serial
    Firebase.setString("portal keluar/nilai", "0");
    Serial.print("5/");
  }
  if (Firebase.getString("portal keluar/nilai") == ("F")) {
    Serial.print("6/");//kirim data serial utk buka portal keluar ke arduino melalui software serial
    Firebase.setString("portal keluar/nilai", "0");
    Serial.print("6/");
  }
  if (Firebase.getString("portal keluar/nilai") == ("G")) {
    Serial.print("7/");//kirim data serial utk buka portal keluar ke arduino melalui software serial
    Firebase.setString("portal keluar/nilai", "0");
    Serial.print("7/");
  }
  if (Firebase.getString("portal keluar/nilai") == ("H")) {
    Serial.print("8/");//kirim data serial utk buka portal keluar ke arduino melalui software serial
    Firebase.setString("portal keluar/nilai", "0");
    Serial.print("8/");
  }

}


void parsingData()
{
  int j = 0;
  //kirim data yang telah diterima sebelumnya
  Serial.print("data masuk : ");
  Serial.print(dataIn);
  Serial.print("\n");
  //inisialisasi variabel, (reset isi variabel)
  dt[j] = "";
  //proses parsing data
  for (i = 1; i < dataIn.length(); i++)
  {
    //pengecekan tiap karakter dengan karakter (#) dan (,)
    if ((dataIn[i] == '#') || (dataIn[i] == ','))
    {
      //increment variabel j, digunakan untuk merubah index array penampung
      j++;
      dt[j] = ""; //inisialisasi variabel array dt[j]
    }
    else
    {
      //proses tampung data saat pengecekan karakter selesai.
      dt[j] = dt[j] + dataIn[i];
    }
  }
  //kirim data hasil parsing

}
