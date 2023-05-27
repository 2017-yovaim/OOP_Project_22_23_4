#pragma once

//TO-DO
//limits
//error codes
//file name paths

//limits
const int MAX_LATITUDE = 90; //degrees at North pole
const int MIN_LATITUDE = -90; //degrees at South pole
const int MAX_LONGITUDE = 180; //180th meridian
const int MIN_LONGITUDE = 0; //Greenwich meridian
const unsigned DEFAULT_VECTOR_CAPACITY = 8;


//error codes - 2 ^ n
const int SUCCESS = 0;
const int INVALID_DATA = 1;
const int FAIL_TO_CHANGE_MONEY_AMOUNT = 2;
const int INVALID_INDEX = -1;

