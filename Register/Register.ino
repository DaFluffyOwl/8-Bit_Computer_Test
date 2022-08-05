//For nano or mega
int bus[8] = {};
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
  void begin(int a, int b, int c){
    enable_pin = a;
    load_pin = b;
    reset_pin = c;
    pinMode(enable_pin, OUTPUT);
    pinMode(load_pin, OUTPUT);
    pinMode(reset_pin, OUTPUT);
  }

  void enable(bool unEnable){
    if(unEnable){
      digitalWrite(enable_pin, HIGH);
    }
    else{
      digitalWrite(enable_pin, LOW);
    }
  }

  void load(bool unLoad){
    if(unLoad){
      digitalWrite(load_pin, HIGH);
    }
    else{
      digitalWrite(load_pin, LOW);
    }
  }

  void reset(bool set){
    if(set){
      digitalWrite(reset_pin, LOW);
    }
    else{
      digitalWrite(reset_pin, HIGH);
    }
  }
};


void setup() {
  for(int i = 0; i < 8; i++){
    bus[i] = i+1;
  }
  Register registerA;
  Register registerB;
  registerA.begin(1, 2, 3);
  registerB.begin(1, 2, 3); //Not the actual numbers
}


void loop() {

}

bool test_sequential(bool a, bool b){ //Args for which registers to test
  if(a){

  }
}