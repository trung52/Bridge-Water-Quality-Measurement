/**
 * @file DataStructure.h
 * @author Vu Thanh Trung
 * @brief 
 * @version 0.1
 * @date 2024-03-04
 * 
 * 
*/

#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include "configs.h"
#include <Wifi.h>
#include <SPIFFS.h>

void addDataToList(String data);

void displayDataList(WiFiClient& client);

void SPIFFS_saveStringDataToFile( String fileName_string, String fileContent_string);

void SPIFFS_checkOutOfMemory();
#endif