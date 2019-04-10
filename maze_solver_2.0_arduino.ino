#include <MPU6050_tockn.h>
#include <Wire.h>
int sensorsag1 = A2;
int sensorsol1 = A0;
int gyroLast = 0, gyroPrevious = 0;
int saniye = 0;
int sensorsag3 = A3;
int sensorsol3 = A7;
int sensoron = 2;
int pwma = 3;
int pwmb = 6;
int ain1 = 8;
int ain2 = 10;
int bin1 = 11;
int bin2 = 7;
boolean varmiyokmi = false;
boolean kavsak = true;
MPU6050 mpu6050(Wire);

char f, r, l;
int randomnum, currentplaceX = 0, currentplaceY = 0, previousX = 0, previousY = 0, gecici = 2, IsThisFinalFRf = 0,
               IsThisFinalFRr = 0, IsThisFinalFLf = 0, IsThisFinalFLl = 0, finalX = 0, finalY = 0, difference = 0,
               catalX = 0, catalY = 0,  Xtochange = -1, Ytochange = -1, ilkcatalX = -1, ilkcatalY = -1, previouscatalX = 0, previouscatalY = 0,
               anothergecici = 0, gecici2 = 0;
String directionofrob = "North", whichdirect = "";
int matris[16][16] = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
} ;

void setup() {
  // put your setup code here, to run once:
  pinMode(sensorsag3, INPUT);
  pinMode(sensorsol3, INPUT);
  pinMode(sensoron, INPUT);
  Wire.begin();
  mpu6050.begin();
  pinMode(pwma, OUTPUT);
  pinMode(pwmb, OUTPUT);
  pinMode(ain1, OUTPUT);
  pinMode(ain2, OUTPUT);
  pinMode(bin1, OUTPUT);
  pinMode(bin2, OUTPUT);
  pinMode(sensorsag1, INPUT);
  pinMode(sensorsol1, INPUT);
  mpu6050.calcGyroOffsets(true);
  goonestep(1);
  solutionwillwork();
  turnbacktostart();
}

void loop() {
 

}


void turnright(int z) {
  if (directionofrob.equals("North")) {
    directionofrob = "East";
    previousX = currentplaceX;
    previousY = 15 - currentplaceY;
    currentplaceX++;
  } else if (directionofrob.equals("East")) {
    directionofrob = "South";
    previousX = currentplaceX;
    previousY = 15 - currentplaceY;
    currentplaceY--;
  } else if (directionofrob.equals("South")) {
    directionofrob = "West";
    previousX = currentplaceX;
    previousY = 15 - currentplaceY;
    currentplaceX--;
  } else {
    directionofrob = "North";
    previousX = currentplaceX;
    previousY = 15 - currentplaceY;
    currentplaceY++;
  }
  if ( z == 1) {
    setthenumber();
  }
  else if (z == 2) {
    setthenumberturningback();
  }
  goonestep(2);
}
void turnleft(int y) {
  if (directionofrob.equals("North")) {
    directionofrob = "West";
    previousX = currentplaceX;
    previousY = 15 - currentplaceY;
    currentplaceX--;
  } else if (directionofrob.equals("East")) {
    directionofrob = "North";
    previousX = currentplaceX;
    previousY = 15 - currentplaceY;
    currentplaceY++;
  } else if (directionofrob.equals("South")) {
    directionofrob = "East";
    previousX = currentplaceX;
    previousY = 15 - currentplaceY;
    currentplaceX++;
  } else {
    directionofrob = "South";
    previousX = currentplaceX;
    previousY = 15 - currentplaceY;
    currentplaceY--;
  }
  if ( y == 1) {
    setthenumber();
  }
  else if (y == 2) {
    setthenumberturningback();
  }
  goonestep(3);
}
void gostraight(int x) {
  if (directionofrob.equals("North")) {
    previousX = currentplaceX;
    previousY = 15 - currentplaceY;
    currentplaceY++;
  } else if (directionofrob.equals("East")) {
    previousX = currentplaceX;
    previousY = 15 - currentplaceY;
    currentplaceX++;
  } else if (directionofrob.equals("South")) {
    previousX = currentplaceX;
    previousY = 15 - currentplaceY;
    currentplaceY--;
  } else {
    previousX = currentplaceX;
    previousY = 15 - currentplaceY;
    currentplaceX--;
  }
  if ( x == 1) {
    setthenumber();
  } else if (x == 2) {
    setthenumberturningback();
  }
  goonestep(1);
}
void turnback (int x) {
  if (directionofrob.equals("North")) {
    directionofrob = "South";
    previousX = currentplaceX;
    previousY = 15 - currentplaceY;
    currentplaceY--;
  } else if (directionofrob.equals("East")) {
    previousX = currentplaceX;
    previousY = 15 - currentplaceY;
    directionofrob = "West";
    currentplaceX--;
  } else if (directionofrob.equals("South")) {
    previousX = currentplaceX;
    previousY = 15 - currentplaceY;
    directionofrob = "North";
    currentplaceY++;
  } else {
    directionofrob = "East";
    previousX = currentplaceX;
    previousY = 15 - currentplaceY;
    currentplaceX++;
  }
  varmiyokmi = false;
  if (x == 1) {
    setthenumber();
  }
  goonestep(4);
}


void turnbackwhenclosed() {
  turnback(2);
  matris[previousY][previousX] = 88888;
  while (true) {

    f = onduvar();
    r = sagduvar();
    l = solduvar();


    if (f == 'C' && r == 'O' && l == 'C') {
      turnright(3);
    } else if (f == 'C' && r == 'C' && l == 'O') {
      turnleft(3);
    } else if (f == 'O' && r == 'C' && l == 'C') {
      gostraight(3);
    } else if (f == 'O' && r == 'O' && l == 'C') {
      if (frontsidevalue() == 88888 && rightsidevalue() != 88888) {
        turnright(3);
      } else if (frontsidevalue() != 88888 && rightsidevalue() == 88888) {
        gostraight(3);
      } else {
        break;
      }
    } else if (f == 'O' && r == 'C' && l == 'O') {
      if (frontsidevalue() == 88888 && leftsidevalue() != 88888) {
        turnleft(3);
      } else if (frontsidevalue() != 88888 && leftsidevalue() == 88888) {
        gostraight(3);
      } else {
        break;
      }
    } else if (f == 'C' && l == 'O' && r == 'O') {
      if (leftsidevalue() == 88888 && rightsidevalue() != 88888) {
        turnright(3);
      } else if (leftsidevalue() != 88888 && rightsidevalue() == 88888) {
        turnleft(3);
      } else {
        break;
      }
    } else if (f == 'O' && l == 'O' && r == 'O') {
      if (leftsidevalue() == 88888 && leftsidevalue() == 88888 && rightsidevalue() != 88888) {
        turnright(3);
      } else if (leftsidevalue() == 88888 && leftsidevalue() != 88888 && rightsidevalue() == 88888) {
        turnleft(3);
      } else if (leftsidevalue() != 88888 && leftsidevalue() == 88888 && rightsidevalue() == 88888) {
        gostraight(3);
      } else {
        break;
      }
    }
    matris[previousY][previousX] = 88888;
  }
  setthenumber();
}



void setthenumber() {
  if (matris[15 - currentplaceY][currentplaceX] == 88888) {
  } else if (matris[15 - currentplaceY][currentplaceX] == 0) {
    matris[15 - currentplaceY][currentplaceX] = gecici;
    gecici++;
  } else if (matris[15 - currentplaceY][currentplaceX] > matris[previousY][previousX]) {
    matris[15 - currentplaceY][currentplaceX] = matris[previousY][previousX] + 1;
    gecici = matris[15 - currentplaceY][currentplaceX] + 1;
  } else {
    gecici = matris[15 - currentplaceY][currentplaceX] + 1;
  }

}


void setthenumberturningback() {
  matris[15 - currentplaceY][currentplaceX] = gecici;
  gecici = matris[15 - currentplaceY][currentplaceX] - 1;
}
int rightsidevalue() {
  if (directionofrob.equals("North")) {
    return matris[15 - currentplaceY][currentplaceX + 1];
  } else if (directionofrob.equals("East")) {
    return matris[16 - currentplaceY][currentplaceX];
  } else if (directionofrob.equals("South")) {
    return matris[15 - currentplaceY][currentplaceX - 1];
  } else {
    return matris[14 - currentplaceY][currentplaceX];
  }
}

int leftsidevalue() {
  if (directionofrob.equals("North")) {
    return matris[15 - currentplaceY][currentplaceX - 1];
  } else if (directionofrob.equals("East")) {
    return matris[14 - currentplaceY][currentplaceX];
  } else if (directionofrob.equals("South")) {
    return matris[15 - currentplaceY][currentplaceX + 1];
  } else {
    return matris[16 - currentplaceY][currentplaceX];
  }
}

int frontsidevalue() {
  if (directionofrob.equals("North")) {
    return matris[14 - currentplaceY][currentplaceX];
  } else if (directionofrob.equals("East")) {
    return matris[15 - currentplaceY][currentplaceX + 1];
  } else if (directionofrob.equals("South")) {
    return matris[16 - currentplaceY][currentplaceX];
  } else {
    return matris[15 - currentplaceY][currentplaceX - 1];
  }
}

void solutionwillwork() {
  matris[15][0] = 1;
  while (!(IsThisFinalFRf == 5 || IsThisFinalFRr == 5 || IsThisFinalFLf == 5 || IsThisFinalFLl == 5)) {

    f = onduvar();
    r = sagduvar();
    l = solduvar();

    if (f == 'C' && l == 'C' && r == 'O') {
      if (rightsidevalue() == 88888) {
        turnbackwhenclosed();
      } else {
        IsThisFinalFRr = 0;
        IsThisFinalFLf = 0;

        if (IsThisFinalFRf >= 2) {
          IsThisFinalFRf++;
        }
        if (IsThisFinalFLl >= 2) {
          IsThisFinalFLl++;
        }
        if (rightsidevalue() == 0 || !varmiyokmi) {
          turnright(1);
        }
        else if (varmiyokmi) {
          turnback(1);
        }
      }

    } else if (f == 'C' && l == 'O' && r == 'C') {
      if (leftsidevalue() == 88888) {
        turnbackwhenclosed();
      } else {
        IsThisFinalFRf = 0;
        IsThisFinalFLl = 0;

        if (IsThisFinalFRr >= 2) {
          IsThisFinalFRr++;
        }
        if (IsThisFinalFLf >= 2) {
          IsThisFinalFLf++;
        }
        if (leftsidevalue() == 0 || !varmiyokmi ) {
          turnleft(1);
        }
        else if (varmiyokmi) {
          turnback(1);
        }
      }
    } else if (f == 'O' && l == 'C' && r == 'C') {
      if (frontsidevalue() == 88888) {
        turnbackwhenclosed();
      } else {
        IsThisFinalFRf = 0;
        IsThisFinalFRr = 0;
        IsThisFinalFLf = 0;
        IsThisFinalFLl = 0;

        if (frontsidevalue() == 0 || !varmiyokmi) {
          gostraight(1);
        }
        else if (varmiyokmi) {
          turnback(1);
        }
      }
    } else if (f == 'C' && l == 'C' && r == 'C') {
      IsThisFinalFRf = 0;
      IsThisFinalFRr = 0;
      IsThisFinalFLf = 0;
      IsThisFinalFLl = 0;
      turnbackwhenclosed();
      varmiyokmi = false;
    } else if (f == 'O' && l == 'C' && r == 'O') {
      if (kavsak) {
        ilkcatalX = currentplaceX;
        ilkcatalY = 15 - currentplaceY;
        kavsak = false;
      }
      previouscatalX = catalX;
      previouscatalY = catalY;
      catalX = currentplaceX;
      catalY = 15 - currentplaceY;
      IsThisFinalFLf = 0;
      IsThisFinalFLl = 0;
      if (frontsidevalue() == 0 || rightsidevalue() == 0) {
        varmiyokmi = true;
        if (rightsidevalue() > frontsidevalue()) {
          IsThisFinalFRf = 2;
          IsThisFinalFRr = 0;
          gostraight(1);
        } else if (rightsidevalue() < frontsidevalue()) {
          IsThisFinalFRf = 0;
          IsThisFinalFRr = 2;
          turnright(1);
        } else if (frontsidevalue() == rightsidevalue()) {
          randomnum = random(0, 2);
          switch (randomnum) {
            case 0:
              IsThisFinalFRf = 0;
              IsThisFinalFRr = 2;
              turnright(1);
              break;
            case 1:
              IsThisFinalFRf = 2;
              IsThisFinalFRr = 0;
              gostraight(1);
              break;
            default:
              break;
          }
        }
      }
      else {
        varmiyokmi = false;
        if ((currentplaceX == ilkcatalX) && (ilkcatalY == 15 - currentplaceY)) {
          turnback(1);
        } else if (rightsidevalue() > frontsidevalue()) {
          IsThisFinalFRf = 2;
          IsThisFinalFRr = 0;
          gostraight(1);
        } else if (rightsidevalue() < frontsidevalue()) {
          IsThisFinalFRf = 0;
          IsThisFinalFRr = 2;
          turnright(1);
        } else if (frontsidevalue() == rightsidevalue()) {
          if (rightsidevalue() == 88888) {
            turnbacktostart();
          } else {
            randomnum = random(0, 2);
            switch (randomnum) {
              case 0:
                IsThisFinalFRf = 0;
                IsThisFinalFRr = 2;
                turnright(1);
                break;
              case 1:
                IsThisFinalFRf = 2;
                IsThisFinalFRr = 0;
                gostraight(1);
                break;
              default:
                break;
            }
          }
        }
      }
    } else if (f == 'C' && l == 'O' && r == 'O') {
      if (kavsak) {
        ilkcatalX = currentplaceX;
        ilkcatalY = 15 - currentplaceY;
        kavsak = false;
      }
      previouscatalX = catalX;
      previouscatalY = catalY;
      catalX = currentplaceX;
      catalY = 15 - currentplaceY;
      IsThisFinalFRf = 0;
      IsThisFinalFRr = 0;
      IsThisFinalFLf = 0;
      IsThisFinalFLl = 0;
      if (rightsidevalue() == 0 || leftsidevalue() == 0) {
        varmiyokmi = true;
        if (rightsidevalue() > leftsidevalue()) {
          turnleft(1);
        } else if (rightsidevalue() < leftsidevalue()) {
          turnright(1);
        } else if (rightsidevalue() == leftsidevalue()) {
          randomnum = random(0, 2);
          switch (randomnum) {
            case 0:
              turnright(1);
              break;
            case 1:
              turnleft(1);
              break;
            default:
              break;
          }
        }
      }
      else {
        varmiyokmi = false;
        if (currentplaceX == ilkcatalX && ilkcatalY == 15 - currentplaceX) {
          turnback(1);
        }
        else if (rightsidevalue() > leftsidevalue()) {
          turnleft(1);

        } else if (rightsidevalue() < leftsidevalue()) {
          turnright(1);
        } else if (rightsidevalue() == leftsidevalue()) {
          if (rightsidevalue() == 88888) {
            turnbacktostart();
          } else {
            randomnum = random(0, 2);
            switch (randomnum) {
              case 0:
                turnright(1);
                break;
              case 1:
                turnleft(1);
                break;
              default:
                break;
            }
          }
        }
      }

    } else if (f == 'O' && l == 'O' && r == 'C') {
      if (kavsak) {
        ilkcatalX = currentplaceX;
        ilkcatalY = 15 - currentplaceY;
        kavsak = false;
      }
      previouscatalX = catalX;
      previouscatalY = catalY;
      catalX = currentplaceX;
      catalY = 15 - currentplaceY;
      IsThisFinalFRf = 0;
      IsThisFinalFRr = 0;
      if (frontsidevalue() == 0 || leftsidevalue() == 0 ) {
        varmiyokmi = true;
        if (frontsidevalue() > leftsidevalue()) {
          IsThisFinalFLf = 0;
          IsThisFinalFLl = 2;
          turnleft(1);
        } else if (frontsidevalue() < leftsidevalue()) {
          IsThisFinalFLf = 2;
          IsThisFinalFLl = 0;
          gostraight(1);
        } else if (frontsidevalue() == leftsidevalue()) {
          randomnum = random(0, 2);
          switch (randomnum) {
            case 0:
              IsThisFinalFLf = 2;
              IsThisFinalFLl = 0;
              gostraight(1);
              break;
            case 1:
              IsThisFinalFLf = 0;
              IsThisFinalFLl = 2;
              turnleft(1);
              break;
            default:
              break;
          }

        }
      }
      else {
        varmiyokmi = false;
        if (currentplaceX == ilkcatalX && ilkcatalY == 15 - currentplaceY  ) {
          turnback(1);
        }
        else if (frontsidevalue() > leftsidevalue()) {
          IsThisFinalFLf = 0;
          IsThisFinalFLl = 2;
          turnleft(1);
        } else if (frontsidevalue() < leftsidevalue()) {
          IsThisFinalFLf = 2;
          IsThisFinalFLl = 0;
          gostraight(1);
        } else if (frontsidevalue() == leftsidevalue()) {
          if (leftsidevalue() == 88888) {
            turnbacktostart();
          } else {
            randomnum = random(0, 2);
            switch (randomnum) {
              case 0:
                IsThisFinalFLf = 2;
                IsThisFinalFLl = 0;
                gostraight(1);
                break;
              case 1:
                IsThisFinalFLf = 0;
                IsThisFinalFLl = 2;
                turnleft(1);
                break;
              default:
                break;
            }

          }
        }
      }
    } else if (f == 'O' && l == 'O' && r == 'O') {
      if (kavsak) {
        ilkcatalX = currentplaceX;
        ilkcatalY = 15 - currentplaceY;
        kavsak = false;
      }
      previouscatalX = catalX;
      previouscatalY = catalY;
      catalX = currentplaceX;
      catalY = 15 - currentplaceY;
      IsThisFinalFRf = 0;
      IsThisFinalFRr = 0;
      IsThisFinalFLf = 0;
      IsThisFinalFLl = 0;
      if (frontsidevalue() == 0 || leftsidevalue() == 0 || rightsidevalue() == 0) {
        varmiyokmi = true;
        if (rightsidevalue() < leftsidevalue() && rightsidevalue() < frontsidevalue()) {

          turnright(1);

        } else if (leftsidevalue() < rightsidevalue() && leftsidevalue() < frontsidevalue()) {

          turnleft(1);

        } else if (frontsidevalue() < rightsidevalue() && frontsidevalue() < leftsidevalue()) {

          gostraight(1);
        } else if (frontsidevalue() < rightsidevalue() && frontsidevalue() == leftsidevalue()) {
          randomnum = random(0, 2);
          switch (randomnum) {
            case 0:
              gostraight(1);
              break;
            case 1:
              turnleft(1);
              break;
            default:
              break;
          }
        } else if (frontsidevalue() == rightsidevalue() && frontsidevalue() < leftsidevalue()) {
          randomnum = random(0, 2);
          switch (randomnum) {
            case 0:
              gostraight(1);
              break;
            case 1:
              turnright(1);
              break;
            default:
              break;
          }
        } else if (leftsidevalue() == rightsidevalue() && frontsidevalue() > leftsidevalue()) {
          randomnum = random(0, 2);
          switch (randomnum) {
            case 0:
              turnleft(1);
              break;
            case 1:
              turnright(1);
              break;
            default:
              break;
          }
        } else if (leftsidevalue() == frontsidevalue() && (rightsidevalue() == frontsidevalue())) {
          randomnum = random(0, 3);
          switch (randomnum) {
            case 0:
              turnleft(1);
              break;
            case 1:
              turnright(1);
              break;
            case 2:
              gostraight(1);
            default:
              break;
          }
        }
      }
    } else {

      varmiyokmi = false;

      if (currentplaceX == ilkcatalX && ilkcatalY == 15 - currentplaceY) {
        turnback(1);

      }
      else if (rightsidevalue() < leftsidevalue() && rightsidevalue() < frontsidevalue()) {

        turnright(1);

      } else if (leftsidevalue() < rightsidevalue() && leftsidevalue() < frontsidevalue()) {

        turnleft(1);

      } else if (frontsidevalue() < rightsidevalue() && frontsidevalue() < leftsidevalue()) {

        gostraight(1);
      } else if (frontsidevalue() < rightsidevalue() && frontsidevalue() == leftsidevalue()) {
        randomnum = random(0, 2);
        switch (randomnum) {
          case 0:
            gostraight(1);
            break;
          case 1:
            turnleft(1);
            break;
          default:
            break;
        }
      } else if (frontsidevalue() == rightsidevalue() && frontsidevalue() < leftsidevalue()) {
        randomnum = random(0, 2);
        switch (randomnum) {
          case 0:
            gostraight(1);
            break;
          case 1:
            turnright(1);
            break;
          default:
            break;
        }
      } else if (leftsidevalue() == rightsidevalue() && frontsidevalue() > leftsidevalue()) {
        randomnum = random(0, 2);
        switch (randomnum) {
          case 0:
            turnleft(1);
            break;
          case 1:
            turnright(1);
            break;
          default:
            break;
        }
      } else if (leftsidevalue() == frontsidevalue() && (rightsidevalue() == frontsidevalue())) {
        if (rightsidevalue() == 88888) {
          turnbacktostart();
        } else {
          randomnum = random(0, 3);
          switch (randomnum) {
            case 0:
              turnleft(1);
              break;
            case 1:
              turnright(1);
              break;
            case 2:
              gostraight(1);
            default:
              break;
          }
        }
      }
    }


  }

  finalX = currentplaceX;
  finalY = 15 - currentplaceY;
  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 16; j++) {
      if (matris[i][j] == 0 || matris[i][j] > matris[15 - currentplaceY][currentplaceX]) {
        matris[i][j] = 88888;
      }
    }
  }
  for (int k = matris[15 - currentplaceY][currentplaceX]; k > 1; k--) {
    for (int i = 1; i < 16 - 1; i++) {
      if (matris[0][i] == k) {
        if (!(i == finalX && 0 == finalY) && matris[0][i + 1] != k + 1 && matris[0][i - 1] != k + 1
            && matris[1][i] != k + 1) {
          matris[0][i] = 88888;
        }
      }
      if (matris[i][0] == k) {
        if (!(0 == finalX && i == finalY) && matris[i + 1][0] != k + 1 && matris[i - 1][0] != k + 1
            && matris[i][1] != k + 1) {
          matris[i][0] = 88888;
        }
      }
      if (matris[15][i] == k) {
        if (!(i == finalX && 15 == finalY) && matris[15][i + 1] != k + 1 && matris[15][i - 1] != k + 1
            && matris[10][i] != k + 1) {
          matris[15][i] = 88888;
        }
      }
      if (matris[i][15] == k) {
        if (!(15 == finalX && i == finalY) && matris[i + 1][15] != k + 1 && matris[i - 1][15] != k + 1
            && matris[i][10] != k + 1) {
          matris[i][15] = 88888;
        }
      }
      for (int j = 1; j < 16 - 1; j++) {
        if (matris[i][j] == k) {
          if (!(i == finalY && j == finalX) && matris[i][j + 1] != k + 1 && matris[i + 1][j] != k + 1
              && matris[i - 1][j] != k + 1 && matris[i][j - 1] != k + 1) {
            matris[i][j] = 88888;
          }
        }
      }
    }
    if (matris[0][15] == k) {
      if (matris[0][10] != k + 1 && matris[1][15] != k + 1) {
        matris[0][15] = 88888;
      }
    }
    if (matris[0][0] == k) {
      if (matris[1][0] != k + 1 && matris[0][1] != k + 1) {
        matris[0][0] = 88888;
      }
    }
    if (matris[15][15] == k) {
      if (matris[10][15] != k + 1 && matris[15][10] != k + 1) {
        matris[15][15] = 88888;
      }
    }
  }
}

void turnbacktostart() {
  gecici = matris[15 - currentplaceY][currentplaceX] - 1;
  while (currentplaceX != 0 || currentplaceY != 0) {

    f = onduvar();
    r = sagduvar();
    l = solduvar();

    if (f == 'C' && r == 'O' && l == 'C') {
      turnright(2);
    } else if (f == 'C' && r == 'C' && l == 'O') {
      turnleft(2);
    } else if (f == 'O' && r == 'C' && l == 'C') {
      gostraight(2);
    } else if (f == 'O' && r == 'O' && l == 'C') {
      if (rightsidevalue() < frontsidevalue()) {
        turnright(2);
      } else {
        gostraight(2);
      }
    } else if (f == 'O' && r == 'C' && l == 'O') {
      if (leftsidevalue() < frontsidevalue()) {
        turnleft(2);
      } else {
        gostraight(2);
      }
    } else if (f == 'C' && l == 'O' && r == 'O') {
      if (rightsidevalue() < leftsidevalue()) {
        turnright(2);
      } else {
        turnleft(2);
      }
    } else if (f == 'O' && l == 'O' && r == 'O') {
      if (rightsidevalue() < leftsidevalue() && rightsidevalue() < frontsidevalue()) {
        turnright(2);
      } else if (leftsidevalue() < frontsidevalue() && leftsidevalue() < rightsidevalue()) {
        turnleft(2);
      } else if (frontsidevalue() < rightsidevalue() && frontsidevalue() < leftsidevalue()) {
        gostraight(2);
      }
    }
  }
  for (int k = matris[15][0] + 1; k < matris[finalY][finalX]; k++) {
    for (int i = 1; i < 16 - 1; i++) {
      if (matris[0][i] == k) {
        if (matris[0][i + 1] != k - 1 && matris[0][i - 1] != k - 1 && matris[1][i] != k - 1) {
          matris[0][i] = 88888;
        }
      }
      if (matris[i][0] == k) {
        if (matris[i + 1][0] != k - 1 && matris[i - 1][0] != k - 1 && matris[i][1] != k - 1) {
          matris[i][0] = 88888;
        }
      }
      if (matris[15][i] == k) {
        if (matris[15][i + 1] != k - 1 && matris[15][i - 1] != k - 1 && matris[10][i] != k - 1) {
          matris[15][i] = 88888;
        }
      }
      if (matris[i][15] == k) {
        if (matris[i + 1][15] != k - 1 && matris[i - 1][15] != k - 1 && matris[i][10] != k - 1) {
          matris[i][15] = 88888;
        }
      }
      for (int j = 1; j < 16 - 1; j++) {
        if (matris[i][j] == k) {
          if (matris[i][j + 1] != k - 1 && matris[i + 1][j] != k - 1 && matris[i - 1][j] != k - 1
              && matris[i][j - 1] != k - 1) {
            matris[i][j] = 88888;
          }
        }
      }
    }
    if (matris[0][15] == k) {
      if (matris[0][10] != k - 1 && matris[1][15] != k - 1) {
        matris[0][15] = 88888;
      }
    }
    if (matris[0][0] == k) {
      if (matris[1][0] != k - 1 && matris[0][1] != k - 1) {
        matris[0][0] = 88888;
      }
    }
    if (matris[15][15] == k) {
      if (matris[10][15] != k - 1 && matris[15][10] != k - 1) {
        matris[15][15] = 88888;
      }
    }
  }
  difference = matris[15][0] - 1;
  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 16; j++) {
      if (matris[i][j] != 88888) {
        matris[i][j] -= difference;
      }
    }
  }
}

char sagduvar() {
  if (digitalRead(sensorsag3) == 0) {
    return 'C';
  }
  else {
    return 'O';
  }
}

char solduvar() {
  if (digitalRead(sensorsol3) == 0) {
    return 'C';
  }
  else {
    return 'O';
  }
}
char onduvar() {
  if (digitalRead(sensoron) == 0) {
    return 'C';
  }
  else {
    return 'O';
  }
}
void goonestep(int num) {
  if (num == 2) {
    gyroPrevious = gyroLast;
    while ((gyroLast - gyroPrevious) > -90) {
      mpu6050.update();
      gyroLast = mpu6050.getAngleZ();
      //solmotor 15
      //sagmotor 0

      motor(50, -50);
    }
  } else if (num == 3) {
    while ((gyroLast - gyroPrevious) > -270) {
      mpu6050.update();
      gyroLast = mpu6050.getAngleZ();
      //sagmotor 15
      //solmotor 0
      motor(50, -50);
    }
  }
  else if (num == 4) {
    while ((gyroLast - gyroPrevious) < -180) {
      mpu6050.update();
      gyroLast = mpu6050.getAngleZ();
      //solmotor 15
      //sagmotor -15
      motor(50, -50);
    }
  }
  saniye = 0;
  while (saniye < 1965) {
    if ((digitalRead(sensorsag1) == 0) && (digitalRead(sensorsol1) == 1)) {
      //sagmotor 20
      //solmotor 10

      motor(40, 55);
      delay(20);
      saniye += 20;
    }
    else if ((digitalRead(sensorsol1) == 0) && (digitalRead(sensorsag1) == 1)) {
      //solmotor 20
      //sagmotor 10
      motor(55, 40);
      delay(20);
      saniye += 20;
    }
    else {
      //solmotor 20
      //sagmotor 20
      motor(50, 50);
      delay(20);
      saniye += 20;
    }
  }
  // motora geri tepki.!! dur

  motor(0, 0);
}
void motor(int sol, int sag) {
  if (sag < 0) {
    sag = -1 * sag;
    digitalWrite(ain1, HIGH);
    digitalWrite(ain2, LOW);
    analogWrite(pwma, sag);
  }
  else {
    digitalWrite(ain2, HIGH);
    digitalWrite(ain1, LOW);
    analogWrite(pwma, sag);
  }
  if (sol < 0) {
    sol = -1 * sol;
    digitalWrite(bin2, HIGH);
    digitalWrite(bin1, LOW);
    analogWrite(pwmb, sol);
  }
  else {
    digitalWrite(bin1, HIGH);
    digitalWrite(bin2, LOW);
    analogWrite(pwmb, sol);
  }
}
