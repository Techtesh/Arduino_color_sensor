#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8
int frequency = 0;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  Serial.begin(9600);
  Serial.println("enter no of colors");
}
int colorNUM = 0;
int j = 0;
void loop() {
  int i, aa;
  int path = 0;
  char *name[] = {"red", "green", "blue"};
  if (Serial.available() > 0)
  {  delay(750);
    i = Serial.read();
    //i = i - 48;
    colorNUM = i - 48;
    for (int temp = 0; temp < colorNUM; temp++)
    {
      Serial.print("configure for  "); Serial.println(name[temp]);
      delay(750);
      colorread(path);

    }
    path = 1;
    Serial.println("#############################################################################################");
    colorread(path);
    delay(12000);
  }
}

void colorread(int path)
{
  int arr[10][3];

  for (int i = 0; i < 10; i++)
  {
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
    frequency = pulseIn(sensorOut, LOW);
    arr[i][0] = frequency;
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    frequency = pulseIn(sensorOut, LOW);
    arr[i][1] = frequency;
    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);
    frequency = pulseIn(sensorOut, LOW);
    arr[i][2] = frequency;

  }
  for (int i = 0; i < 10; i++)


  { for (int j = 0; j < 3; j++)

    {
      Serial.print("     "); Serial.print(arr[i][j]);
    }


    Serial.println("");
  }



  int ravg, gavg, bavg;
  for (int i = 0; i < 10; i++)
  {
    ravg += arr[i][0];
    gavg += arr[i][1];
    bavg += arr[i][2];
  }

  ravg = ravg / 10;
  gavg = gavg / 10;
  bavg = bavg / 10;
  Serial.print("Ravg="); Serial.println(ravg);
  Serial.print("gavg="); Serial.println(gavg);
  Serial.print("bavg="); Serial.println(bavg);
  int path0 = path;
  colordata(ravg, gavg, bavg, path0);

}

void colordata(float r, float g , float b, int path)
{
  Serial.print("j="); Serial.println(j);
  Serial.print("glb="); Serial.println(colorNUM);
  int  n = colorNUM;
  static float vals[20][3];
  float d[20];
  int path0 = path;
  if (path0 == 0)
  {
    for (int k = j; k < n ; k++)
    {
      vals[k][0] = r;
      vals[k][1] = g;
      vals[k][2] = b;
    }
    for (int k = 0; k < n; k++)
    {
      Serial.print("   line   ");
      Serial.print(vals[k][0]);

      Serial.print("      ");
      Serial.print(vals[k][1]);

      Serial.print("      ");
      Serial.println(vals[k][2]);

      Serial.println();
    }
    j++;
    delay(5000);
  }
  if (path0 == 1)
  {
    for (int temp = 0; temp < colorNUM; temp++)
    {
      d[temp] = (vals[temp][0] - r) * (vals[temp][0] - r) + (vals[temp][1] - g) * (vals[temp][1] - g) + (vals[temp][2] - b) * (vals[temp][2] - b);
      Serial.print("D"); Serial.print(temp); Serial.print("="); Serial.println(d[temp]);
    }
    int min = 9999;
    int index = -1;
    for (int temp = 0; temp < colorNUM; temp++)
    {
      if (d[temp] < min)
      {
        min=d[temp];
        index=temp;
      }
    }
    Serial.print("min no:");Serial.println(index+1);
    if(index==0){Serial.println("RED");}
    if(index==1){Serial.println("GREEN");}
    if(index==2){Serial.println("BLUE");}
  }
}


