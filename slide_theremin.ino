long result_1;   //variable for the result of the tx_rx measurement.
long result_2;
float result;
int analog_pin_1 = A3;
int tx_pin_1 = 4;
int tx_pin_2 = 7;
int lightPin = 3;
int analog_pin_2 = A1;

int signal_1;
int signal_2;
int pitch_min = 130;
int pitch_max = 1050;

int max_1 = 0;
int min_1 = 100000;
int max_2 = 0;
int min_2 = 100000;

int get_rgb(float pitch) {
  
}

void setup() {
    pinMode(tx_pin_1, OUTPUT);      //Pin 4 provides the voltage step
    pinMode(tx_pin_2, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    result_1 = tx_rx(tx_pin_1, analog_pin_1);

    if (result_1 > max_1){
      max_1 = result_1;
    } else if (result_1 < min_1) {
      min_1 = result_1;
    }

    result_2 = tx_rx(tx_pin_2, analog_pin_2);

    if (result_2 > max_2){
      max_2 = result_2;
    } else if (result_2 < min_2) {
      min_2 = result_2;
    }

    signal_1 = map(result_1, min_1, max_1, 0, 255);
    signal_2 = map(result_2, min_2, max_2, 0, 255);

    // result = float(result_1 + result_2) / 2.0;
    // result = float(result_1 - result_2);

    // int size = map(result, 0, 100, 0, 255);
    // analogWrite(lightPin, size);
    Serial.print(signal_1);
    Serial.print("   |   ");
    Serial.println(result_1);
    // Serial.println(result);
}


long tx_rx(int tx_pin, int analog_pin){         // Function to execute rx_tx algorithm and return a value
                      // that depends on coupling of two electrodes.
                      // Value returned is a long integer.
  int read_high;
  int read_low;
  int diff;
  long int sum;
  int N_samples = 10;    // Number of samples to take.  Larger number slows it down, but reduces scatter.

  sum = 0;

  for (int i = 0; i < N_samples; i++){
   digitalWrite(tx_pin,HIGH);              // Step the voltage high on conductor 1.
   read_high = analogRead(analog_pin);     // Measure response of conductor 2.
   delayMicroseconds(100);                 // Delay to reach steady state.
   digitalWrite(tx_pin,LOW);               // Step the voltage to zero on conductor 1.
   read_low = analogRead(analog_pin);      // Measure response of conductor 2.
   diff = read_high - read_low;            // desired answer is the difference between high and low.
   sum += diff;                            // Sums up N_samples of these measurements.
 }
  return sum;
}   
