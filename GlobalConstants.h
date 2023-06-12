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
const int FAIL_TO_LOG_IN = 4;
const int FAIL_TO_LOG_OUT = 8;
const int FAIL_TO_COMPLETE_ORDER = 16;
const int ORDER_ACCEPTED = 32;
const int ORDER_DECLINED = 64;
const int INVALID_ACTION = 128;
const int INVALID_ROLE_LOGIN = 256;
const int ORDER_NOT_FOUND = 512;
const int FAIL_TO_ACCEPT_ORDER = 1024;
const int FAIL_TO_DECLINE_ORDER = 2048;
const int FAIL_TO_CANCEL_ORDER = 4096;
const int FAIL_TO_FINISH_ORDER = 8192;
const int INVALID_INDEX = -1;

//commands
const int EXIT = 0;
const int REGISTER_CLIENT = 1;
const int REGISTER_DRIVER = 2;
const int LOGIN = 3;
const int LOGOUT = 4;
const int MAKE_ORDER = 5;
const int CHECK_ORDER = 6;
const int CANCEL_ORDER = 7;
const int MAKE_PAYMENT = 8;
const int CHECK_MESSAGES = 9;
const int ACCEPT_ORDER = 10;
const int DECLINE_ORDER = 11;
const int FINISH_ORDER = 12;
const int ACCEPT_PAYMENT = 13;



