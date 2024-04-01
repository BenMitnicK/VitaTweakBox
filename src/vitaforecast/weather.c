#include "forecast.h"
#include "weather.h"
#include "net.h"
#include "../utils.h"
#include "../file.h"
#include "../message_dialog.h"
#include "../ime_dialog.h"
#include "../theme.h"
#include "../language.h"
#include "../main.h"


static char patch[MAX_PATH_LENGTH];

void initWeatherData()
{
	char buffer[1024], buffer2[2];
	
	if (checkFileExist("ux0:VitaTweakBox/tweaks/Forecast/zipCode.txt"))
		ReadFile("ux0:VitaTweakBox/tweaks/Forecast/zipCode.txt", zip, 12);
	else
	{
		strcpy(zip, "31100,fr");
		WriteFile("ux0:VitaTweakBox/tweaks/Forecast/zipCode.txt", zip, 12);
		downloadWeatherData();
	}
	
	if (checkFileExist("ux0:VitaTweakBox/tweaks/Forecast/weather.txt"))
		ReadFile("ux0:VitaTweakBox/tweaks/Forecast/weather.txt", buffer, 1024);
	
	if (checkFileExist("ux0:VitaTweakBox/tweaks/Forecast/metricUnits.txt"))
	{
		ReadFile("ux0:VitaTweakBox/tweaks/Forecast/metricUnits.txt", buffer2, 2);
		sscanf(buffer2, "%d", &CorF);
	}
	else
	{
		if (strcmp((getWeatherContent(buffer, "country\":\"", "\",\"sunrise")), "US") == 0)
		{
			sprintf(buffer2, "0");
			WriteFile("ux0:VitaTweakBox/tweaks/Forecast/metricUnits.txt", buffer2, 2);
			sscanf(buffer2, "%d", &CorF);
		}
		else
		{
			sprintf(buffer2, "1");
			WriteFile("ux0:VitaTweakBox/tweaks/Forecast/metricUnits.txt", buffer2, 2);
			sscanf(buffer2, "%d", &CorF);
		}
	}
}

char * urlConcat(char url[], char zipCode[], char apiKey[])
{
	static char str[100];
	strcpy(str, url);
	strcat(str, zipCode); 
	strcat(str, apiKey); 
	
	return str;
}

int downloadWeatherData()
{
	char url[100];
	strcpy(url, urlConcat("http://api.openweathermap.org/data/2.5/weather?zip=", zip, "&appid=1fbac727d98de6617dc510dd3b4aac4b"));
	while(1)
	{
		
		download(url, "ux0:VitaTweakBox/tweaks/Forecast/weather.txt");
		return 1;
	}
}

char * getWeatherContent(char * string, char * str1, char * str2) //Basically finds a string between two othe strings :D
{
	static char str[1024];
	char *begin, *end, *crawl;
	int i = 0;
	
	begin = strstr(string, str1);
	begin+=strlen(str1);
	
	end = strstr(string, str2);	
	
	for(crawl = begin; crawl < end; crawl++)
		str[i++] = *crawl;
		
	str[i] = '\0'; //add '\0' to the array so that it's a string!
	
	return str;
}

double strToDouble(char * str)
{
	double val = 0.0;
	
	sscanf(str, "%lf", &val);
	
	return val;
}

double kelvinToC(double temp)
{
	double c = (temp - 273);
	
	return c;
}	

double cToF(double temp)
{
	double c = (temp - 273);
	double f = (c * (1.8)) + 32.0;
	
	return f;
}	

double mToKm(double m)
{
	double km = (m * 3.6);
	return km;
}

double mToMph(double m)
{
	double mph = (m * 2.23694);
	return mph;
}

bool isDay()//basic assumption really
{
	SceDateTime time;
	sceRtcGetCurrentClockLocalTime(&time);
		
	if ((time.hour >= 6) && (time.hour <= 18))
		return true; //Day
	else 
		return false; //Night
}

void displayWeatherIcon(char * desc, bool day) //Uses main description
{
	float slide_y = ForeCast_menu.cur_pos - 463;
	
	if (day == true)
	{
		if (strcmp(desc, "Clear") == 0)
			vita2d_draw_texture(dClearSky, 647, 17+slide_y);
		else if (strcmp(desc, "Clouds") == 0)
			vita2d_draw_texture(dClouds, 647, 17+slide_y);
		else if ((strcmp(desc, "Rain") == 0) || (strcmp(desc, "Drizzle") == 0))
			vita2d_draw_texture(dRain, 647, 17+slide_y);
		else if ((strcmp(desc, "Thunderstorm") == 0) || (strcmp(desc, "Extreme") == 0))
			vita2d_draw_texture(dThunderstorm, 647, 17+slide_y);
		else if (strcmp(desc, "Snow") == 0)
			vita2d_draw_texture(dSnow, 647, 17+slide_y);
		else if (strcmp(desc, "Atmosphere") == 0)
			vita2d_draw_texture(mist, 647, 17+slide_y);
	}
	else
	{
		if (strcmp(desc, "Clear") == 0)
			vita2d_draw_texture(nClearSky, 647, 17+slide_y);
		else if (strcmp(desc, "Clouds") == 0)
			vita2d_draw_texture(nClouds, 647, 17+slide_y);
		else if ((strcmp(desc, "Rain") == 0) || (strcmp(desc, "Drizzle") == 0))
			vita2d_draw_texture(nRain, 647, 17+slide_y);
		else if ((strcmp(desc, "Thunderstorm") == 0) || (strcmp(desc, "Extreme") == 0))
			vita2d_draw_texture(nThunderstorm, 647, 17+slide_y);
		else if (strcmp(desc, "Snow") == 0)
			vita2d_draw_texture(nSnow, 647, 17+slide_y);
		else if (strcmp(desc, "Atmosphere") == 0)
			vita2d_draw_texture(mist, 647, 17+slide_y);
	}
}

void displayWeatherContent()
{
	char buffer[1024];
	
	double c = 0.0, cMin = 0.0, cMax = 0.0, windSpeed = 0.0;
	
	ReadFile("ux0:VitaTweakBox/tweaks/Forecast/weather.txt", buffer, 1024);
	
	float slide_y = ForeCast_menu.cur_pos - 463;
	
	if((getFileSize("ux0:VitaTweakBox/tweaks/Forecast/weather.txt")) <= 0)
	{
		infoDialog(language_container[FORECASTERRORNETWORK]);
		closeForeCastMenu();
		//openAppMenuMenu();
		sceIoRemove("ux0:VitaTweakBox/tweaks/Forecast/weather.txt");
		sceIoRemove("ux0:VitaTweakBox/tweaks/Forecast/zipCode.txt");
	}
	else if (strcmp(buffer, "{\"cod\":\"500\",\"message\":\"Internal error: 500000\"}") == 0)
	{
		infoDialog(language_container[FORECASTERRORZIPCODE]);
		closeForeCastMenu();
		//openAppMenuMenu();
		sceIoRemove("ux0:VitaTweakBox/tweaks/Forecast/zipCode.txt");
	}
	else
	{
		
		displayWeatherIcon(getWeatherContent(buffer, "main\":\"", "\",\"des"), isDay());
	
		snprintf(patch, MAX_PATH_LENGTH, "%s", getWeatherContent(buffer, "name\":\"", "\",\"cod"));
		float w = pgf_text_width(patch);
		float h = pgf_text_height(patch);
		pgf2_draw_text(280+ALIGN_CENTER(260, w), ALIGN_CENTER(37, h)+slide_y+76, FORECAST_NAME_COLOR, 1.5, patch);
	
		c = strToDouble(getWeatherContent(buffer, "temp\":", ",\"pressure"));
		cMin = strToDouble(getWeatherContent(buffer, "temp_min\":", ",\"temp_max"));
		cMax = strToDouble(getWeatherContent(buffer, "temp_max\":", "},\"visibility"));
		windSpeed = strToDouble(getWeatherContent(buffer, "speed\":", ",\"deg"));
	
		if (CorF == 0)
		{
			snprintf(patch, MAX_PATH_LENGTH, "%.0lf°F", cToF(c));
			float _w = pgf_text_width(patch);
			float _h = pgf_text_height(patch);
			pgf_draw_text(ALIGN_CENTER(121, _w)+150, ALIGN_CENTER(23, _h)+35+slide_y, FORECAST_TEMP_COLOR, patch);
			snprintf(patch, MAX_PATH_LENGTH, "Min: %.0lf°F", cToF(cMin));
			pgf_draw_text(162, 85+slide_y, FORECAST_TEMP_MIN_COLOR, patch);
			snprintf(patch, MAX_PATH_LENGTH, "Max: %.0lf°F", cToF(cMax));
			pgf_draw_text(162, 105+slide_y, FORECAST_TEMP_MAX_COLOR, patch);
			snprintf(patch, MAX_PATH_LENGTH, "%s: %.02f mph", language_container[FORECAST_WIND], mToMph(windSpeed));
			pgf_draw_text(162, 300+slide_y, FORECAST_WIND_COLOR, patch);
			
			if (pressed_pad[PAD_SELECT])
			{
				CorF = 1;
				WriteFile("ux0:data/VITAforecast/metricUnits.txt", "1", 2);
			}
		}
		else
		{
			snprintf(patch, MAX_PATH_LENGTH, "%.0lf°C", kelvinToC(c));
			float _w = pgf_text_width(patch);
			float _h = pgf_text_height(patch);
			pgf_draw_text(ALIGN_CENTER(121, _w)+154, ALIGN_CENTER(23, _h)+37+slide_y, FORECAST_TEMP_COLOR, patch);
			snprintf(patch, MAX_PATH_LENGTH, "Min: %.0lf°C", kelvinToC(cMin));
			pgf_draw_text(162, 85+slide_y, FORECAST_TEMP_MIN_COLOR, patch);
			snprintf(patch, MAX_PATH_LENGTH, "Max: %.0lf°C", kelvinToC(cMax));
			pgf_draw_text(162, 105+slide_y, FORECAST_TEMP_MAX_COLOR, patch);
			snprintf(patch, MAX_PATH_LENGTH, "%s: %.02f km/h", language_container[FORECAST_WIND], mToKm(windSpeed));
			pgf_draw_text(162, 290+slide_y, FORECAST_WIND_COLOR, patch); 
			
			if (pressed_pad[PAD_SELECT])
			{
				CorF = 0;
				WriteFile("ux0:data/VITAforecast/metricUnits.txt", "0", 2);
			}
		}
		
		snprintf(patch, MAX_PATH_LENGTH, "%s\n", getWeatherContent(buffer, "description\":\"", "\",\"icon"));
		float w_ = pgf_text_width(patch);
		float h_ = pgf_text_height(patch);
		pgf_draw_text(ALIGN_CENTER(432, w_)+150, ALIGN_CENTER(33, h_)+165+slide_y, FORECAST_DESC_COLOR, patch);
		snprintf(patch, MAX_PATH_LENGTH, "%s: %s%%", language_container[FORECAST_HUMID], getWeatherContent(buffer, "humidity\":", ",\"temp_"));
		pgf_draw_text(162, 210+slide_y, FORECAST_HUMID_COLOR, patch);
		snprintf(patch, MAX_PATH_LENGTH, "%s: %s%%", language_container[FORECAST_CLOUD], getWeatherContent(buffer, "clouds\":{\"all\":", "},\"dt"));
		pgf_draw_text(162, 250+slide_y, FORECAST_CLOUD_COLOR, patch);
		snprintf(patch, MAX_PATH_LENGTH, "%s: %s hPa", language_container[FORECAST_ATMOS], getWeatherContent(buffer, "pressure\":", ",\"humidity"));
		pgf_draw_text(162, 330+slide_y, FORECAST_ATMOS_COLOR, patch);
	}
}
