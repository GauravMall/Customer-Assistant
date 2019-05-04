class Map {
    int tokensLength; // The length of the tokens ARRAY.
    int right;
    int left;
    boolean turnedRight = false;
    boolean turnedLeft = false;

  public:
    Map(int tokenLength) {
      tokensLength = tokenLength;
      left = 0;
      right = 0;
    }

    void drawMap(MCUFRIEND_kbv tft, String tokens[]) {
      int i = 1;

      while (i < tokensLength / 2 - 1) {
        int x1;
        int y1;
        int x2;
        int y2;

        x1 = tokens[i * 7 - 7].toInt();
        y1 = tokens[i * 7 - 6].toInt();
        x2 = tokens[i * 7 - 5].toInt();
        y2 = tokens[i * 7 - 4].toInt();

        for (uint16_t a = 0; a < 5; a++)
        {
          tft.drawLine(x1 + 50 + a, y1 + 50, x2 + 50 + a, y2 + 50, WHITE);
        }
        for (uint16_t a = 0; a < 5; a++)
        {
          tft.drawLine(x1 + 50, y1 + 50 + a, x2 + 50, y2 + 50 + a, WHITE);
        }

        i++;
      }
    }

    void drawRobot(MCUFRIEND_kbv tft, Robot robotPosition) {
      tft.fillCircle(robotPosition.X + 50, robotPosition.Y + 50, 5, RED);
    }

    void driveTo(Robot rP, String destinationLabel, String tokens[]) {
      int i = 0;
      int destinationX;
      int destinationY;

      while (i < tokensLength) {
        if (tokens[i].substring(0) == destinationLabel) {
          String tokenX = tokens[i - 2];
          String tokenY = tokens[i - 1];
          destinationX = tokenX.toInt();
          destinationY = tokenY.toInt();
          i = tokensLength;
        }
        i++;
      }

      if (destinationX == rP.X && destinationY == rP.Y) {
        Reset();
        isNavigating = false;
      } else {
        if (!detected) {
          int opposite = destinationX - robotPosition.X;
          int adjacent = destinationY - robotPosition.Y;

          int angle = round( atan2 (opposite, adjacent) * 180 / 3.14159265 );

          if (angle == 90) {
            moveForward(true, rP);
          }
          else if (angle < 90 && angle > 0) {
            moveRight(true, rP);
          }
          else if (angle < 180 && angle > 90) {
            moveLeft(true, rP);
          }
          else if (angle < 0) {
            moveRight(true, rP);
          }
          else if (angle == 180) {
            moveLeft(true, rP);
          }
          else {
            moveBack(true, rP);
          }
        }

        else {
          Stop();
          delay(500);
          moveBack(true, rP);
          delay(500);
          
          if (CheckLeft()) {
            moveLeft(false, rP);
            delay(500);
            Stop();
            delay(50);
            moveForward(false, rP);
            delay(50);
            Stop();
          }

          else {
            if (CheckRight()) {
              moveRight(false, rP);
              delay(500);
              Stop();
              delay(50);
              moveForward(false, rP);
              delay(50);
              Stop();
            }
            else {
              Stop();
            }
          }
          
        }
      }

    }

    //Motor Functions
    void moveForward(boolean isMovingTowardsDestination, Robot _robotPosition) {
      digitalWrite(MotorForward, HIGH);
      delay(50);
      digitalWrite(MotorForward, LOW);
      delay(200);
      digitalWrite(MotorBack, LOW);

      if (isMovingTowardsDestination) {
        robotPosition.X = _robotPosition.X + 1;
      }
    }

    void moveRight(boolean isMovingTowardsDestination, Robot _robotPosition) {
      Stop();
      delay(50);
      moveForward(isMovingTowardsDestination, _robotPosition);
      delay(50);

      if (isMovingTowardsDestination) {
        robotPosition.Y = _robotPosition.Y + 1;

        if (!turnedRight) {
          digitalWrite(MotorRight, HIGH);
          delay(400);
          digitalWrite(MotorRight, LOW);
          delay(200);
          turnedRight = true;
        }
      } else {
        digitalWrite(MotorRight, HIGH);
        delay(400);
        digitalWrite(MotorRight, LOW);
        delay(200);
      }
    }

    void moveLeft(boolean isMovingTowardsDestination, Robot _robotPosition) {
      Stop();
      delay(50);
      moveForward(isMovingTowardsDestination, _robotPosition);
      delay(50);

      if (isMovingTowardsDestination) {
        robotPosition.Y = _robotPosition.Y - 1;

        if (!turnedLeft) {
          digitalWrite(MotorLeft, HIGH);
          delay(400);
          digitalWrite(MotorLeft, LOW);
          delay(200);
          turnedLeft = true;
        }
      } else {
        digitalWrite(MotorLeft, HIGH);
        delay(400);
        digitalWrite(MotorLeft, LOW);
        delay(200);
      }
    }

    void moveBack(boolean isMovingTowardsDestination, Robot _robotPosition) {
      if (CheckBack()) {
        if (isMovingTowardsDestination) {
          robotPosition.X = _robotPosition.X - 1;

          digitalWrite(MotorBack, HIGH);

          digitalWrite(MotorForward, LOW);
          digitalWrite(MotorRight, LOW);
          digitalWrite(MotorLeft, LOW);
        }
      }
      else {
        Stop();
      }
    }

    void Stop() {
      digitalWrite(MotorForward, LOW);
      digitalWrite(MotorBack, LOW);
    }

    void Reset() {
      digitalWrite(MotorForward, LOW);
      digitalWrite(MotorBack, LOW);
      digitalWrite(MotorRight, LOW);
      digitalWrite(MotorLeft, LOW);

      left = 0;
      right = 0;
    }

    //Sensor Functions
    boolean Detect() {
      forwardDistance = ReadDistance(trig_pin_forward, echo_pin_forward);
      forwardDistanceTop = ReadDistance(trig_pin_top, echo_pin_top);

      if (forwardDistance < 40) {
        return true;
      }

      if (forwardDistanceTop < 40) {
        return true;
      } else {
        return false;
      }
    }

    int ReadDistance(int trigPin, int echoPin) {
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);

      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);

      digitalWrite(trigPin, LOW);

      int duration = pulseIn(echoPin, HIGH);

      //This gives us the _distance in cm.
      int distance = duration / 58.2;
      return distance;
    }

    boolean CheckRight() {
      right = ReadDistance(trig_pin_right, echo_pin_right);

      if (right < 30) {
        return false;
      }
      else {
        return true;
      }
    }

    boolean CheckLeft() {
      left = ReadDistance(trig_pin_right, echo_pin_right);

      if (left < 30) {
        return false;
      }
      else {
        return true;
      }
    }

    boolean CheckBack() {
      int distanceBackTop = ReadDistance(trig_pin_backTop, echo_pin_backTop);
      delay(100);
      int distanceBackDown = ReadDistance(trig_pin_backBottom, echo_pin_backBottom);
      delay(100);
      int distanceBackRight = ReadDistance(trig_pin_backRight, echo_pin_backRight);
      delay(100);
      int distanceBackLeft = ReadDistance(trig_pin_backLeft, echo_pin_backLeft);

      if (distanceBackTop < 40) {
        return false;
      }

      if (distanceBackDown < 40) {
        return false;
      }

      if (distanceBackRight < 30) {
        return false;
      }

      if (distanceBackLeft < 30) {
        return false;
      } else {
        return true;
      }
    }
};
