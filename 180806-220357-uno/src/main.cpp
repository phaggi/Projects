#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

unsigned short int Ndatch = 1 ; //количество датчиков
unsigned short int n; //счетчик датчиков
unsigned short int td; //счетчик таймера
unsigned short int h; //значение текущего датчика, в килопопугаях
unsigned short int P = 1; //пауза между измерениями, сек
const unsigned short int HMIN[4]={1000,1000,1000,1000}; //массив минимальных значений датчиков, в килопопугаях
const unsigned short int HMAX[4]={400,400,400,520}; //массив максимальных значений датчиков, в килопопугаях
unsigned short int BASEH[4]; //база значений последнего измерения с датчиков
//signed short int BASET[4]; //база значений времени измерения

unsigned short int D=43200; //задержка между измерениями, сек

const unsigned short int X[4]={5,5,5,3}; //массив задержек на полив, сек
const unsigned short int Z[4]={120,120,120,220}; //массив задержек на промокание грунта, сек
unsigned short int nPort; // (служебный)
//unsigned short int nBase; // (служебный)
//signed short int currentTime = 0; //(служебный)
//signed short int lastTime = 0; //(служебный)

void setup(){
  
    n = 0; //обнуляем счетчик датчика
    td = 0; //обнуляем счетчик таймера
    h = 1500; //значение текущей переменной ставим в "великая сушъ"
//    lastTime = millis()/1000.0; //видимо, таймер
    Serial.begin(9600);   
//------------------------------------------    
// начало цикла инициализации портов

    while(!(((n)==(Ndatch))))
    {
  //      _loop();
        
        n += 1;
        
        nPort = ((n) * (2));//Serial.print("init port cycle ");Serial.println (n);
        pinMode((nPort),OUTPUT); //инициализируем нечетные цифровые выходы (порты питания датчиков)
        digitalWrite((nPort),0); //приводим к норме нечетные цифровые выходы (отключаем порты питания датчиков)

        delay(P*1000);//Serial.print("pause1 ");Serial.println (nPort);
        
        nPort += 1;//Serial.print("port+1 ");Serial.println (nPort); 
        pinMode((nPort),OUTPUT);//инициализируем четные цифровые выходы (порты клапанов)
        //Serial.print("off port ");Serial.println (nPort);
        digitalWrite((nPort),1);//приводим к норме четные цифровые выходы (закрываем порты клапанов)
        
        nPort = (A0+(n) - (1));//Serial.print("init input port ");Serial.println (nPort); 
        pinMode((nPort),INPUT);//инициализируем аналоговые входы, начиная с нулевого (порты данных датчиков)
        delay(P*1000);//Serial.print("pause 2 ");Serial.println (Port);
    }
// конец цикла инициализации портов    
//------------------------------------------ 
}

void loop(){
    Serial.println("--------------------------"); 
    Serial.println("nachalo pervichnogo zamera");
    td = 0; //обнуляем счетчик таймера
    n = 0;//Serial.print("sbros schetchika n=");Serial.println (n);//обнуляем счетчик
    h = 1500;//Serial.print("obnuljaem h=");Serial.println (h);//значение текущей переменной ставим в "великая сушъ"
      while(!(((n)>=(Ndatch))))//перебираем датчики
      {
          n += 1;//Serial.print("n=");Serial.println (n);//увеличиваем счетчик на 1
          nPort = ((n) * (2)); //вычисляем номер порта питания датчика
          digitalWrite((nPort),1); //включаем порт питания датчика
          delay(P*1000);//Serial.print("pause1 ");Serial.println (nPort);//пауза 
          h = 1500;//значение текущей переменной ставим в "великая сушъ"
          h = analogRead(A0+(n) - (1));//пишем в переменную значение датчика
          //Serial.print("vykl port ");Serial.println (nPort);
          digitalWrite((nPort),0);//выключаем порт питания датчика
          //Serial.print("port ");Serial.print (nPort);Serial.println(" vykluchen");
          BASEH[n-1] = h;//Serial.print("h=");Serial.println (BASEH[n-1]);//пишем текущее значение в базу
          //delay(P*1000);Serial.print("pause2 ");Serial.println (nPort);
      }
    //Serial.print("h=");Serial.println (h);
    n = 0;//Serial.print("2 sbros schetchika n=");Serial.println (n);//обнуляем счетчик
    h = 1500;//Serial.print("2 obnuljaem h=");Serial.println (h);//значение текущей переменной ставим в "великая сушъ"while(!(((n)>=(Ndatch))))//перебираем датчики
        Serial.println("konec pervichnogo zamera");
 //печатаем в терминал что получилось в базе
      while(!(((n)>=(Ndatch))))//перебираем датчики 
{
  n += 1;//увеличиваем счетчик на 1
  Serial.print("BASEH ");Serial.print(n);Serial.print(" ");Serial.println(BASEH[n-1]);
}
  Serial.println("--------------------------"); 
 Serial.println("nachalo modulja poliva");
    n = 0;Serial.print("3 sbros schetchika n=");Serial.println (n);//обнуляем счетчик
    h = 1500;Serial.print("3 obnuljaem h=");Serial.println (h);//значение текущей переменной ставим в "великая сушъ"
  Serial.println("nachalo while n");   
      while(!(((n)>=(Ndatch))))
      {
          n += 1;Serial.print("poliv ");Serial.print(n);Serial.println(" BASEH= ");Serial.print(BASEH[n-1]);Serial.print(" HMIN= ");Serial.println (HMIN[n-1]);
          if((BASEH[n-1]) > (HMIN[n-1]))
          {
              nPort = ((n) * (2));
              digitalWrite((nPort) + (1),0);Serial.print("polivaem ");Serial.println (n);
              delay(X[n]*1000);
              digitalWrite((nPort) + (1),1);
                delay(P*1000);            
              Serial.print("promokaet ");Serial.println (n);
              delay(Z[n]*1000);
              h = 1500;

              digitalWrite((nPort),1);Serial.print("vkluchaem port ");Serial.println (nPort/2);
              delay(P*1000);
              h = analogRead(A0+(n) - (1));Serial.print("h=");Serial.println (h);
              BASEH[n]=h;
              digitalWrite((nPort),0);Serial.print("vykluchaem port ");Serial.println (nPort/2);
              if((h) > (HMAX[n-1])){
                  while(!((BASEH[n-1]) < (HMAX[n-1])))
                  {
                      nPort = ((n) * (2));
                      Serial.print("BASEH ");Serial.print(n);Serial.print(" ");Serial.println(BASEH[n-1]);
                      digitalWrite((nPort) + (1),0);Serial.print("polivaem povtorno ");Serial.println (n);
                      delay(X[n]*1000);
                      digitalWrite((nPort) + (1),1);Serial.print("promokaet povtorno ");Serial.println (n);
                      delay(Z[n]*1000);
  
                      digitalWrite((nPort),1);Serial.print("vkluchaem port ");Serial.println (nPort);
                      delay(P*100);
                      h = analogRead(A0+(n) - (1));Serial.print("h=");Serial.println (h);
                      BASEH[n-1]=h;
                      digitalWrite((nPort),0);Serial.print("vykluchaem port ");Serial.println (nPort);
                  }
              }
              delay(P*1000);
          }
          else
          {Serial.print("poliv ");Serial.print(n);Serial.println(" ne nuzhen");
            }
      }
 Serial.println("konec modulja poliva"); 
 Serial.print("pause mezhdu ciklami ");
              Serial.print (D/3600);
              Serial.println (" chasov");//задержка до следующего цикла
 while(td<D)//перебираем датчики
             { Serial.print (td/3600);Serial.print (":");Serial.print (td/60);Serial.print (":");Serial.println (td);
              delay(1000);
              td+=1;
             }   
}


