/*
This code’s still a bit messy and could definitely use some 
cleanup and restructuring. Feel free to suggest improvements 
or take a stab at reworking it!
*/
#define dat 8
#define clk 9
#define mr 10

uint8_t byte_1 = 0x00;
uint8_t byte_2 = 0x00;
uint8_t byte_3 = 0x00;
uint8_t byte_4 = 0x00;

//......................abcdefgh....ijklmdag...//The letter "a","d" and "g" have 2 segments
uint8_t letter[54] = {0b11101110, 0b00000011, //A //0
                      0b11110000, 0b10010111, //B //2
                      0b10011100, 0b00000110, //C //4
                      0b11110000, 0b10010110, //D //6
                      0b10011110, 0b00000111, //E //8
                      0b10001110, 0b00000011, //F //10
                      0b10111100, 0b00000111, //G //12
                      0b01101110, 0b00000001, //H //14
                      0b10010000, 0b10010110, //I //16
                      0b11111000, 0b00000110, //J //18
                      0b00001110, 0b01100000, //K //20
                      0b00011100, 0b00000100, //L //22
                      0b01101101, 0b01000000, //M //24
                      0b01101101, 0b00100000, //N //26
                      0b11111100, 0b00000110, //O //28
                      0b11001110, 0b00000011, //P //30
                      0b11111100, 0b00100110, //Q //32
                      0b11001110, 0b00100011, //R //34
                      0b10110110, 0b00000111, //S //36
                      0b10000000, 0b10010010, //T //38
                      0b01111100, 0b00000100, //U //40
                      0b00001100, 0b01001000, //V //42
                      0b00000001, 0b01101000, //X //44
                      0b10010000, 0b01001110, //Z //46
                      0b01101100, 0b00101000, //W //48
                      0b00000000, 0b00000000};//Space //50
//                      
//......................abcdefgh....ijklmdag...//The letter "a","d" and "g" have 2 segments
uint8_t number[22] = {0b11111100, 0b00000110, //0
                      0b01100000, 0b01000000, //1
                      0b10011010, 0b01000110, //2
                      0b11110010, 0b00000111, //3
                      0b01100110, 0b00000001, //4
                      0b10110110, 0b00000111, //5
                      0b10111110, 0b00000111, //6
                      0b11100000, 0b00000010, //7
                      0b11111110, 0b00000111, //8
                      0b11100110, 0b00000011};//9 

uint8_t msg[18] = {0b01101110, 0b00000001, //H //14 
                   0b10010000, 0b10010110, //I //16
                   0b00000000, 0b00000000, //Space //50
                   0b10001110, 0b00000011, //F //10
                   0b11111100, 0b00000110, //O //28
                   0b00011100, 0b00000100, //L //22
                   0b00001110, 0b01100000, //K //20
                   0b10110110, 0b00000111}; //S //36

void setup() {
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(mr, HIGH);

  Serial.begin(115200);
}
void serialData(uint8_t val){
  unsigned char mask = 1; //our bitmask
      for (mask = 0b00000001; mask>0; mask <<= 1) { //iterate through bit mask
      digitalWrite(clk, LOW);
      delayMicroseconds(1);
        if (val & mask){ // if bitwise AND resolves to true
          digitalWrite(dat, HIGH);
          //Serial.print(1); //Only to debug
        }
        else{ //if bitwise and resolves to false
          digitalWrite(dat, LOW);
          //Serial.print(0); //Only to debug
        }
        digitalWrite(clk, HIGH);// need invert the signal to allow 8 bits is is low only send 7 bits
        delayMicroseconds(1);
      }
  digitalWrite(clk, LOW);
  //Serial.println(); //Only to debug
}
void msgHiFolks(void){
  uint8_t pos = 14; //This is the position of the char's of msg extracted to be presented!
                    // is 8 char's, but start at "0", this means 2 bytes by char is equal to 14 address.
  //The cycle for is to define the position of the digit, offcourse we can revert one or other (addres or position)
      for(uint8_t i = 0b10000000; i > 0x00; i = i>>1 ){
          byte_3 = i;
          byte_2 = msg[pos];
          byte_1 = msg[pos+1];
          serialData(byte_1);// 
          serialData(byte_2);//  
          serialData(byte_3);//
          pos = pos -2;
          delay(3);
      }
}
void msgLetter(void){
  //This is the position of the char's of msg extracted to be presented!
  // is 26 char's with space, but start at "0", this means 2 bytes by char is equal to 50 address.
  //The cycle for is to define the position of the digit, offcourse we can revert one or other (addres or position)
  for(uint8_t s = 0; s < 54; s=s+2)
      for(uint8_t i = 0b10000000; i > 0x00; i = i>>1 ){
          byte_3 = i;
          byte_2 = letter[s];
          byte_1 = letter[s+1];
          serialData(byte_1);// 
          serialData(byte_2);//  
          serialData(byte_3);//
          if(i>1){  //I use this IF to avoid the skip of char's by the cycle FOR(i)
            s=s+2;
          } 
          delay(500);
      }
}
void msgNumber(void){
  //This is the position of the char's of msg extracted to be presented!
  // is 10 char's, but start at "0", this means 2 bytes by char is equal to 18 address.
  //The cycle for is to define the position of the digit, offcourse we can revert one or other (addres or position)
  for(uint8_t s = 0; s < 18; s=s+2)
      for(uint8_t i = 0b10000000; i > 0x00; i = i>>1 ){
          byte_3 = i;
          byte_2 = number[s];
          byte_1 = number[s+1];
          serialData(byte_1);// 
          serialData(byte_2);//  
          serialData(byte_3);//
          if(i>1){  //I use this IF to avoid the skip of char's by the cycle FOR(i)
            s=s+2;
          } 
          delay(500);
      }
}
void allOn(){
  long length32 = 0x00000000;  //Hexadecimal declaration filled.
     length32 = 0B11111111111111111111111111111111;  //Binary filled
     //length32 = 0xAAAAAAAA;
        //byte_4 = (length32 & 0xff000000) >>  24; 
        byte_3 = (length32 & 0x00ff0000) >>  16;
        byte_2 = (length32 & 0x0000ff00) >>  8;
        byte_1 = (length32 & 0x000000ff) >>  0;
    // Serial.print("lng: ");
    // Serial.println(length32, BIN);
  serialData(byte_1);// 
  serialData(byte_2);//  
  serialData(byte_3);// 
  //shiftOut(data, clock, MSBFIRST, ~byte_4);//
  delay(1);  
}
void allOff(){
  long length32 = 0x00000000;  //Hexadecimal declaration filled.
     length32 = 0B00000000000000000000000000000000;  //Binary filled
        //byte_4 = (length32 & 0xff000000) >>  24; 
        byte_3 = (length32 & 0x00ff0000) >>  16;
        byte_2 = (length32 & 0x0000ff00) >>  8;
        byte_1 = (length32 & 0x000000ff) >>  0;
    // Serial.print("lng: ");
    // Serial.println(length32, BIN);

    byte_3 = 0x30;
    byte_2 = 0xFF;
    byte_1 = 0xFF;
  serialData(byte_1);// 
  serialData(byte_2);//  
  serialData(byte_3);// 
  //serialData( ~byte_4);//
  Serial.println(); //Only to debug
  delay(1);  
}
void allTest(){
  long length32 = 0x00000000;  //Hexadecimal declaration filled.
     length32 = 0B00000000000000000000000000000000;  //Binary filled
        //byte_4 = (length32 & 0xff000000) >>  24; 
        byte_3 = (length32 & 0x00ff0000) >>  16;
        byte_2 = (length32 & 0x0000ff00) >>  8;
        byte_1 = (length32 & 0x000000ff) >>  0;
    // Serial.print("lng: ");
    // Serial.println(length32, BIN);
              for(uint8_t i = 0b10000000; i > 0x00; i = i>>1 ){
                  byte_3 = i;
                  byte_2 = number[18];
                  byte_1 = number[18+1];
                serialData(byte_1);// 
                serialData(byte_2);//  
                serialData(byte_3);//
                delay(4); 
              }
  //serialData( ~byte_4);//
  //Serial.println(); //Only to debug
  delay(1);  
}
void loop() {
  for(uint8_t i = 0x00; i < 128; i++){
    msgHiFolks();
  }
  msgNumber();
  msgLetter();
// allTest();
}
