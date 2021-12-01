#include<String.h>
#include<OneButton.h>

OneButton Button_left(A1,true);
OneButton Button_mid(A2, true);
OneButton Button_right(A3, true);
unsigned long time_now=0;
int dPin = 2;

String Data ="";
String Command="";
const int  MaxN=64;
int End[MaxN];
int Next[MaxN][2];
int created[MaxN];
int sz=0;
const int SIZE = 26;
int MODE = 0;
bool newData =false;
String received_data="";
int len=0;

/*
 * MODE 0= TX, 1=RX
 */

String ALPHA[SIZE]={
  "0", "1", "00", "01", "10", "11", "000", "001", "010", "011", "100", "101", "110", "111", "0000", "0001", "0010", "0100",
  "0110", "0111", "1000", "1001", "1010", "1011", "1100","1101"};


/*
int Indexof[SIZE]= {
  3, 20, 22, 10, 0, 16, 12, 14, 2, 19, 11, 17, 5, 4, 13, 18, 25, 8, 6, 1, 7, 15, 9, 21, 23, 24
  };
*/
int invInd[SIZE] = { 4, 19, 8, 0, 13, 12, 18, 20, 17, 22, 3, 10, 6, 14, 7, 21, 5, 11, 15, 9, 1, 23, 2, 24, 25, 16};




void insert(String s)
{
    int v=0;
    for(int i=0; i<s.length(); i++)
    {
      int c;
      char ch = s[i];
        if( ch == '0')
           {
               //cout<<s[i];
               c=0;
           }
        else if(ch=='1')
        {
            c=1;
        }
        if(!created[Next[v][c]])
        {
            Next[v][c] = ++sz;
            created[sz]=1;
        }
        v= Next[v][c];

    }
    ++End[v];
}


int search(String tmp)
{
    int v=0;
    for(int i=0; i<tmp.length(); i++)
    {
        int c;
        if(tmp[i]=='0')
            c=0;
        else if(tmp[i]=='1')
            c= 1;

        if(!created[Next[v][c] ])
            {
                return false;
            }
        v=Next[v][c];
    }
    return v;
    //return End[v]>0;
}


int lookup(int index)
{
  //int AASCII;
  
  return invInd[index];
}

void setup() {
    Serial.begin(9600);
    Button_left.attachClick(singleClick1);
    Button_left.attachLongPressStop(longClick1);
    
    Button_mid.attachClick(singleClick2);
    Button_mid.attachDoubleClick(doubleClick2);
    Button_mid.attachLongPressStop(longClick2);

    Button_right.attachClick(singleClick3);
    Button_right.attachLongPressStop(longClick3);
    
  // put your setup code here, to run once:
    for(int i=0; i< SIZE ; i++)
    {
      String s = ALPHA[i];
      insert(s);
    }
}

void longClick1()
{
  if(MODE== 0)
    Serial.println(" DEL");
}

void longClick3()
{
  ///  CAN BE USWD for OTHER  SYMBOL
}

void singleClick1()
{ 
  if(MODE==0)
  {
    Data+="0";
    len+=1;
  }
  else if(MODE==1)
  {
    Command+="REPEAT";
    Serial.println(Command);
    Command="";
  }
  
}

void singleClick3()
{
  if(MODE==0)
  {
    Data+="1";
    len+=1;
  }
  else if(MODE ==1)
  {
    Command+="NEXT";
    Serial.println(Command);
    Command ="";
  }
  
}

void singleClick2()
{
  /*char Serial.println(lookup(search(Data)-1));
   * for(int i=0; i<5; i++)
    {
      String s = lookUP[i];
      int offset = lookup( search(s)-1 );
      char ch = 'a' + offset;
      Serial.println(ch); 
    }
  */
  if(MODE == 0)
  {
    if(Data != "")
    {
      String s = Data;
      int d =search(s);
      int offset = lookup(d-1);
      char ch ='a'+offset;
      Serial.print(ch);
      //playback(Data);   //
      Data="";
      len=0;
      Serial.flush();
    }
  }
}

void  doubleClick2()
{
  if(MODE == 0)
    {
      Serial.print(" ");
    }
}

void longClick2()
{
  if(MODE==1)
      {
        
        Serial.println("MODE 0");
        MODE=0;
      }
  else if(MODE==0)
      {
        singleClick2();
        Serial.println("MODE 1");
        MODE=1;
      }
}

void playback(String s)
{
  int n=s.length();
  // to be edited  for  feedback
  Serial.println(s);
  for(int i=0; i<n; i++)
  {
    if(s[i] == '0')
    {
      digitalWrite(dPin, HIGH);
      delay(300);
      digitalWrite(dPin,LOW);
      delay(300);
    }
    else if(s[i]=='1')
    {
      digitalWrite(dPin,HIGH );
      delay(500);
      digitalWrite(dPin,LOW);
      delay(300); 
    }  
  }
}



void loop() {
  // put your main code here, to run repeatedly:
  /*
    Serial.println( (char) lookup(search("1101")-1)+ 'a');
    Serial.println(lookup(search("01")-1));
    Serial.println(lookup(search("11")-1));
    Serial.println(lookup( search("10")-1 ) );
    Serial.println( lookup( search("0")-1 ) );
  
    for(int i=0; i<5; i++)
    {
      String s = lookUP[i];
      int offset = lookup( search(s)-1 );
      char ch = 'a' + offset;
      Serial.println(ch); 
    }

    delay(100000);
    */
    Button_left.tick();
    Button_mid.tick();
    Button_right.tick();
    check_serial_if();
    if(newData == true && MODE == 1 )
    {
      Deaf_blind_output();
    } 
    //serial_state(MODE);
    delay(10);
}

void alert()
{
  int i=1;
  while(i--)
  {
      digitalWrite(dPin, HIGH);
      delay(600);
      digitalWrite(dPin,LOW);
  }
}

void check_serial_if()
{
  if(Serial.available() > 0 )
  {
    received_data = Serial.readString();
    //Serial.write("Hello");
    newData = true;
    alert();
  }
}

void Deaf_blind_output()
{
  int s_len = received_data.length();
  int Data;
  //Serial.println(received_data);
  for(int i=0; i<s_len - 1 ; i++)
  { 
    Data = received_data[i];
    Serial.println(Data);
    //Serial.println(received_data[i]);
    //Serial.println(ALPHA[invInd[Data]] );
  }
  Serial.flush();
  received_data="";
}
