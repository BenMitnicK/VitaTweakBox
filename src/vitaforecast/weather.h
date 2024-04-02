#ifndef _WEATHER_H_
#define _WEATHER_H_

extern char zip[10];

extern int CorF;

void initWeatherData();
int getWeatherZip();
int downloadWeatherData();
char * getWeatherContent(char * string, char * str1, char * str2);
double strToDouble(char * str);
double kelvinToC(double temp);
double kelvinToF(double temp);
double mToKm(double m);
double mToMph(double m);
void displayWeatherContent();

#endif
