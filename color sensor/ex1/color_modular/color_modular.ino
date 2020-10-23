#define S0 8
#define S1 9
#define S2 10
#define S3 11
#define sensorOut 12
int frequency = 0;
void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Setting frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  Serial.begin(9600);
}


int check(int code)
{ int Low[] = {25, 30, 25};
  int High[] = {72, 90, 70};
  switch (code)
  {
    case 0:
      //Serial.print("RED");Serial.print(Low[0]);Serial.println(High[0]);
      digitalWrite(S2, LOW);
      digitalWrite(S3, LOW);
      frequency = pulseIn(sensorOut, LOW);
      frequency = map(frequency, Low[0], High[0], 255, 0);
      return frequency;
      break;

    case 1:
      //Serial.print("Green");Serial.print(Low[1]);Serial.println(High[1]);
      digitalWrite(S2, HIGH);
      digitalWrite(S3, HIGH);
      frequency = pulseIn(sensorOut, LOW);
      frequency = map(frequency, Low[1], High[1], 255, 0);
      return frequency;
      break;

    case 2:
      //Serial.print("Blue");Serial.print(Low[2]);Serial.println(High[2]);
      digitalWrite(S2, LOW);
      digitalWrite(S3, HIGH);
      frequency = pulseIn(sensorOut, LOW);
      frequency = map(frequency, Low[2], High[2], 255, 0);
      return frequency;
      break;
  }
  return 0;
}




void loop()
{
  // INITIALISING UI PART
  Serial.println("No of colors");
  while (Serial.available() == 0)   {}
  int N = Serial.read();
  N = N - 47;
  String Colors[N] = {};
  Serial.print(N - 1); Serial.println("Colors");
  for (int i = 0; i < N; i++)
  {
    while (Serial.available() == 0) {}

    //Serial.print("enter color no "); Serial.println(i);

    String temp = Serial.readString();
    Colors[i] = temp;
    Serial.print(i-1); Serial.print(")"); Serial.println(Colors[i]);



  }
  for (int j = 0; j < N - 1; j++)
  {
    Colors[j] = Colors[j + 1];

  }
  Colors[N] = "To End";
  for (int i = 0; i < N - 1; i++)
  {
    Serial.print(i); Serial.print("]"); Serial.print(Colors[i]);
  }


  // GETTING BASE DATA
  int R[N], G[N], B[N];
  int Rtemp, Gtemp, Btemp;
  for (int i = 0; i < N - 1; i++)
  { Rtemp = 0; Gtemp = 0; Btemp = 0;
    Serial.print("place "); Serial.println(Colors[i]);
    delay(5000);
    for (int j = 0; j < 10; j++)
    {
      Rtemp += check(0);
    }
    Rtemp = Rtemp / 10;
    Serial.print("R= "); Serial.print(Rtemp); Serial.println("  ");
    delay(100);
    for (int j = 0; j < 10; j++)
    {
      Gtemp += check(1);
    }
    Gtemp = Gtemp / 10;
    Serial.print("G= "); Serial.print(Gtemp); Serial.println("  ");
    delay(100);
    for (int j = 0; j < 10; j++)
    {
      Btemp += checkBlue();
    }
    Btemp = Btemp / 10;
    Serial.print("B= "); Serial.print(Btemp); Serial.println("  ");
    delay(100);
    R[i] = Rtemp;
    G[i] = Gtemp;
    B[i] = Btemp;
    Serial.print("prepare "); Serial.println(Colors[i + 1]);
  }

  //DISPLAYING BASE DATA

  for (int i = 0; i < N - 1; i++)
  {
    Serial.print(Colors[i]); Serial.print("     "); Serial.print(R[i]); Serial.print("     "); Serial.print(G[i]); Serial.print("     "); Serial.println(B[i]);
  }

  //TAKING UNKNOWN DATA
  int Rnew = 0, Gnew = 0, Bnew = 0;
  Serial.println("place unknown colors");
  delay(1500);
  for (int i = 0; i < 10; i++)
  {
    Rnew += check(0);
    Gnew += check(1);
    Bnew += checkBlue();
  }
  Rnew = Rnew / 10;
  Gnew = Gnew / 10;
  Bnew = Bnew / 10;
  Serial.print("Unknown"); Serial.print("     "); Serial.print(Rnew); Serial.print("     "); Serial.print(Gnew); Serial.print("     "); Serial.println(Bnew);

  //Distance map
  float Dist[N - 1] = {};
  for (int i = 0; i < N - 1; i++)
  {
    Dist[i] = (R[i] - Rnew) * (R[i] - Rnew) + (G[i] - Gnew) * (G[i] - Gnew) ;
    Serial.print(Colors[i]);Serial.print("      "); Serial.print("Ref dist ="); Serial.println(Dist[i]);
  }

  //Finding min distance
  int mini=0;float temp=Dist[0];
  for (int i = 0; i < N - 1; i++)
  {
    //Serial.print(i);
    if (Dist[i] < temp)
    { 
      temp=Dist[i];
      mini=i;
    }
  }
  Serial.print("MOST LIKELY COLOR : ");Serial.println(Colors[mini]);
  
}








//Alternate Functions in case check dose not work

int checkRed()
{
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  frequency = pulseIn(sensorOut, LOW);
  frequency = map(frequency, 25, 72, 255, 0);
  return frequency;
}

int checkGreen()
{

  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);
  frequency = map(frequency, 30, 90, 255, 0);
  return frequency;
}
int checkBlue()
{
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);
  frequency = map(frequency, 25, 70, 255, 0);
  return frequency;
}
