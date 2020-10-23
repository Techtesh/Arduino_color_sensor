

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.println("No of colors");
  while (Serial.available() == 0)   {}
  int N = Serial.read();
  N = N - 47;
  String Colors[N] = {};
  Serial.print(N); Serial.println("Colors");
  for (int i = 0; i < N; i++)
  {
    while (Serial.available() == 0) {}
    Serial.print("enter color no "); Serial.println(i);
    String temp = Serial.readString();
    Colors[i] = temp;
    Serial.print(i); Serial.print(")"); Serial.println(Colors[i]);
  }
  for (int i = 0; i < N; i++)
  {
   Serial.print(i);Serial.print("]");Serial.print(Colors[i]);
  }
  
  for (int j = 0; j < N - 1; j++)
  {
    Colors[j]=Colors[j+1];

  }
  
  for (int i = 0; i < N; i++)
  {
   Serial.print(i);Serial.print("]"); Serial.print(Colors[i]);
  }
}
