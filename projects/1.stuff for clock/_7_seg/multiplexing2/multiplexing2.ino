#define iArrSize 7
//counting
int iCount = 0;
int iCountMore = 0;
//delays for frames and stuff
int iDelayWrites = 0;
int iDelayDigits = 0;
int iDelayFrames = 0;
//scrolling
int iScrollSpeed = 500; //200-500
//digit select
int iDigit1 = 12;
int iDigit2 = 11;
//char CALPHA
char CALPHA[15] {'H', 'A', 'C', 'K', ' ', 'T', 'H', 'E', ' ', 'P', 'L', 'A', 'N', 'E', 'T'};

//REFERENCE {dp, d, e, c, g, f, b, a};

//characters
int CA[iArrSize] = {0, 0, 1, 1, 1, 1, 1, 1};
//int CA[iArrSize] = {1, 0, 0, 0, 0, 0, 0, 0};
int CB[iArrSize] = {0, 1, 1, 1, 1, 1, 0, 0};
//int CB[iArrSize] = {0, 1, 0, 0, 0, 0, 0, 0};
int CC[iArrSize] = {0, 1, 1, 0, 0, 1, 0, 1};
//int CC[iArrSize] = {0, 0, 1, 0, 0, 0, 0, 0};
int CD[iArrSize] = {0, 1, 1, 1, 1, 0, 1, 0};
//int CD[iArrSize] = {0, 0, 0, 1, 0, 0, 0, 0};
int CE[iArrSize] = {0, 1, 1, 0, 1, 1, 0, 1};
//int CE[iArrSize] = {0, 0, 0, 0, 1, 0, 0, 0};
int CF[iArrSize] = {0, 0, 1, 0, 1, 1, 0, 1};
//int CF[iArrSize] = {0, 0, 0, 0, 0, 1, 0, 0};
int CG[iArrSize] = {0, 1, 0, 1, 1, 1, 1, 1};
//int CG[iArrSize] = {0, 0, 0, 0, 0, 0, 1, 0};
int CH[iArrSize] = {0, 0, 1, 1, 1, 1, 0, 0};
//int CH[iArrSize] = {0, 0, 0, 0, 0, 0, 0, 1};

void setup(){
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  
  pinMode(iDigit1, OUTPUT);
  pinMode(iDigit2, OUTPUT);
}

void loop(){
  delay(iDelayFrames);
  
  iResistorRead = 0;//unused
  
  iDelayDigits = iResistorRead;
  
  if (iCountMore >= iScrollSpeed) {iCount++; iCountMore = 0;}
  iCountMore++;
  if (iCount >=19){iCount = -4;}

