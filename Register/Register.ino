int bus[8] = {};
int data[8] = {1, 1, 0, 1, 1, 0, 0, 0};
bool enable_a = false;
bool load_a = false;
bool reset_a = false;

class Register
{
private:
public:
  int enable_pin;
  int load_pin;
  int reset_pin;
  int clock_pin;
  void begin(int a, int b, int c, int d){
    enable_pin = a;
    load_pin = b;
    reset_pin = c;
    clock_pin = d;
    pinMode(enable_pin, OUTPUT);
    pinMode(load_pin, OUTPUT);
    pinMode(reset_pin, OUTPUT);
  }

  void enable(bool Enable){
    if(!Enable){
      digitalWrite(enable_pin, HIGH);
    }
    else{
      digitalWrite(enable_pin, LOW);
    }
  }

  void load(bool Load, int *dataptr){
    if(!Load){
      digitalWrite(load_pin, HIGH);
    }
    else{
      digitalWrite(load_pin, LOW);
      for(int k = 0; k < 8; k++){
        if(*(dataptr+k) == 0){
          digitalWrite(bus[k], LOW);
        }
        else if(*(dataptr+k) == 1){
          digitalWrite(bus[k], HIGH);
        }
      }
      digitalWrite(enable_pin, HIGH);
      delay(50);
      digitalWrite(load_pin, LOW);
      delay(50);
      digitalWrite(clock_pin, HIGH);
      delay(50);
      digitalWrite(clock_pin, LOW);
    }
  }

  void reset(bool Reset){
    if(!Reset){
      digitalWrite(reset_pin, LOW);
    }
    else{
      digitalWrite(reset_pin, HIGH);
    }
  }
  bool test_data();
  void write_data(int bus_index);
};


void setup() {
  Serial.begin(9600);
  const int offset = 30;
  int x = 0;
  for(int i = 0; i < 8; i++){ //Sets up pin values for bus
    bus[i] = x+offset;
    x = x+2;
  }
  Register registerA;
  Serial.println("Beginning Testing");
  registerA.begin(2, 51, 53, 52);
  /*for(int test = 0; test < 8; test++){
      registerA.write_data(test);
  }*/
  registerA.test_data();
  //registerB.begin(1, 2, 3, 4); //Not the actual numbers
}


void loop() {

}

bool Register::test_data(){
  for(int j = 0; j < 8; j++){
    pinMode(bus[j], OUTPUT);
    if(data[j] == 1){
      digitalWrite(bus[j], HIGH);
    }
    else{
      digitalWrite(bus[j], LOW);
    }
  }
  delay(1000);
  enable(false);
  reset(true);
  delay(50);
  reset(false);
  delay(50);
  load(true, data);
  delay(100);
  enable(true);
  delay(100);
  int inc = 1;
  for(int bit_place = 0; bit_place < 8; bit_place++){
    digitalWrite(bus[bit_place], LOW);
    digitalWrite(bus[bit_place], INPUT);
  }
  load(false, NULL);
  delay(100);
  enable(true);
  delay(100);
  /*for(int index = 0; index < 8; index++){
    if(data[index] == digitalRead(bus[index])){
      inc++;
    }
    else{
      Serial.print("Register Error! Bus Index ");
      Serial.print(index);
      Serial.println();
      return false;
    }
  }*/
  if(inc == 8){
      Serial.print("Register Good");
      return true;  
  }
}

void Register::write_data(int bus_index){
  pinMode(bus[bus_index], OUTPUT);
  digitalWrite(bus[bus_index], HIGH);
  digitalWrite(enable_pin, HIGH);
  delay(100);
  delay(100);
  digitalWrite(load_pin, LOW);
  delay(100);
  digitalWrite(clock_pin, HIGH);
  delay(100);
  digitalWrite(clock_pin, LOW);
  //digitalWrite(load_pin, HIGH);
  //digitalWrite(load_pin, HIGH);
  delay(100);
}