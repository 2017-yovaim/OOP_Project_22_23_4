#pragma once

//limits
const int MAX_LATITUDE = 90; //degrees at North pole
const int MIN_LATITUDE = -90; //degrees at South pole
const int MAX_LONGITUDE = 180; //180th meridian
const int MIN_LONGITUDE = 0; //Greenwich meridian
const unsigned DEFAULT_VECTOR_CAPACITY = 8;
const char DEFAULT_FILE_PATH[] = "data.dat";
const char DEFAULT_EMPTY_ADD_INFO[] = "\"\"";


//error codes - prime numbers + 0 for success
const int SUCCESS = 0;
const int INVALID_INDEX = -1;
const int INVALID_ACTION = 2;
const int INVALID_DATA = 3;
const int FAIL_TO_REGISTER = 5;
const int FAIL_TO_LOG_IN = 7;
const int FAIL_TO_LOG_OUT = 9;
const int INVALID_ROLE_LOGIN = 11;
const int FAIL_TO_COMPLETE_ORDER = -13;
const int FAIL_TO_CHANGE_MONEY_AMOUNT = 17;
const int ORDER_ACCEPTED = 29;
const int ORDER_DECLINED = 31;
const int ORDER_NOT_FOUND = 37;
const int FAIL_TO_ACCEPT_ORDER = 41;
const int FAIL_TO_DECLINE_ORDER = 43;
const int FAIL_TO_CANCEL_ORDER = 47;
const int FAIL_TO_FINISH_ORDER = 53;
const int FAIL_TO_LOAD_DATA = 59;
const int FAIL_TO_SAVE_DATA = 61;
const int FAIL_TO_OPEN_FILE = 67; 
const int ORDER_NOT_ACCEPTED = 71;
const int ORDER_NOT_FINISHED = 73;
const int FAIL_TO_START_SYSTEM = 79;


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
const int RATE = 9;
const int ADD_MONEY = 10;
const int CHECK_MESSAGES = 11;
const int ACCEPT_ORDER = 12;
const int DECLINE_ORDER = 13;
const int FINISH_ORDER = 14;
const int ACCEPT_PAYMENT = 15;
const int CHECK_RATING = 16;
const int CHANGE_ADDRESS = 17;
const int CHANGE_INPUT_PATH = 18;
const int CHANGE_OUTPUT_PATH = 19;



