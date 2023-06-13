#include <iostream>
#include "TaxiService.h"

using std::cout;
using std::cin;
using std::endl;

/*
* The taxi service viewer includes the main function and manages the operations
* Also acts as a user interface
*/

/*
* TO-DO:
* - extremely unoptimized. Fix when code works as intended
*	specifically implement higher-order functions for this
*/

namespace
{
	void getUniversalUserData(MyString& username, MyString& password, MyString& firstname, MyString& lastname)
	{
		cout << "Please enter your username: " << endl;
		char buff[1024];
		cin.getline(buff, 1024);
		username.setString(buff);

		cout << "Please enter your password: " << endl;
		cin.getline(buff, 1024);
		password.setString(buff);

		cout << "Please enter your first name: " << endl;
		cin.getline(buff, 1024);
		firstname.setString(buff);

		cout << "Please enter your last name: " << endl;
		cin.getline(buff, 1024);
		lastname.setString(buff);
	}
}

void actionHandler(int errorCode)
{
	cout << endl;
	//successes
	if (errorCode == SUCCESS)
	{
		cout << "Task completed successfully!" << endl;
		cout << endl;
		return;
	}
	if (errorCode == ORDER_ACCEPTED)
	{
		cout << "The order has been accepted!" << endl;
		cout << endl;
		return;
	}
	if (errorCode == ORDER_DECLINED)
	{
		cout << "The order has been declined!" << endl;
		cout << endl;
		return;
	}

	//errors
	if (errorCode % INVALID_DATA == 0)
	{
		cout << "There has been invalid data." << endl;
	}
	if (errorCode % FAIL_TO_CHANGE_MONEY_AMOUNT == 0)
	{
		cout << "Fail during money transfer." << endl;
	}
	if (errorCode % FAIL_TO_LOG_IN == 0)
		cout << "Failed to log in." << endl;
	if (errorCode % FAIL_TO_LOG_OUT == 0)
		cout << "Failed to log out." << endl;
	if (errorCode % INVALID_ACTION == 0)
		cout << "You do not have the right to this action." << endl;
	if (errorCode % INVALID_ROLE_LOGIN == 0)
		cout << "This action requires a different login." << endl;
	if (errorCode % ORDER_NOT_FOUND == 0)
		cout << "No order with such id found." << endl;

	cout << endl;
}


int registerClientMenu(TaxiService& ts)
{
	cin.ignore();
	MyString username;
	MyString password;
	MyString firstname;
	MyString lastname;
	getUniversalUserData(username, password, firstname, lastname);
	return ts.registerClient(username, password, firstname, lastname);
}

int registerDriverMenu(TaxiService& ts)
{
	cin.ignore();
	MyString username;
	MyString password;
	MyString firstname;
	MyString lastname;
	getUniversalUserData(username, password, firstname, lastname);

	cout << "Please enter your car number: " << endl;
	char buff[2014];
	cin.getline(buff, 1024);
	MyString carnumber(buff);

	cout << "Please enter your phone number: " << endl;
	cin.getline(buff, 1024);
	MyString phonenumber(buff);

	return ts.registerDriver(username, password, firstname, lastname, carnumber, phonenumber);
}

int loginMenu(TaxiService& ts)
{
	cin.ignore();
	cout << "Please enter your user name: " << endl;
	char buff[1024];
	cin.getline(buff, 1024);
	MyString username(buff);
	cout << "Please enter your password: " << endl;
	cin.getline(buff, 1024);
	MyString password(buff);
	return ts.login(username, password);
}

int logoutMenu(TaxiService& ts)
{
	return ts.logout();
}

int makeOrderMenu(TaxiService& ts)
{
	/*if (!ts.isSignedInAsClient())
	{
		cout << "Sorry, you have to be signed as a client to make orders." << endl;
		return INVALID_ACTION | INVALID_ROLE_LOGIN;
	}*/
	if (ts.getCurrentClientIndex() == INVALID_INDEX)
	{
		cout << "Sorry, you have to be signed as a client to make orders." << endl;
		return INVALID_ACTION * INVALID_ROLE_LOGIN;
	}

	
	cin.ignore();
	cout << "Please enter the name of the initial address: " << endl;
	char buff[1024];
	cin.getline(buff, 1024);
	
	MyString fromName(buff);
	cout << "Please enter the coordinates of the initial address: " << endl;
	int fromx;
	cin >> fromx;
	int fromy;
	cin >> fromy;

	cin.ignore();
	cout << "Please enter any additional info of the initial address (if there isn't any, enter \"\"" << endl;
	cin.getline(buff, 1024);
	MyString fromAddInfo(buff);
	Address from(fromName.c_str(), fromx, fromy, fromAddInfo.c_str());

	cout << "Please enter the name of the destionation address: " << endl;
	cin.getline(buff, 1024);
	MyString toName(buff);
	cout << "Please enter the coordinates of the destination address: " << endl;
	int tox;
	cin >> tox;
	int toy;
	cin >> toy;

	cin.ignore();
	cout << "Please enter any additional info of the destination address (if there isn't any, enter \"\"" << endl;
	cin.getline(buff, 1024);
	MyString toAddInfo(buff);
	Address to(toName.c_str(), tox, toy, toAddInfo.c_str());

	unsigned passengers;
	cout << "Please enter the number of passengers." << endl;
	cin >> passengers;

	unsigned idoforder = ts.order(from, to, passengers);
	cout << "Order made! Your order's id is: " << idoforder << endl;
	return SUCCESS;
}

int checkOrderMenu(TaxiService& ts)
{
	/*if (!ts.isSignedInAsClient())
	{
		cout << "Sorry, you have to be signed as a client to check orders." << endl;
		return INVALID_ACTION | INVALID_ROLE_LOGIN;
	}*/

	if (ts.getCurrentClientIndex() == INVALID_INDEX)
	{
		cout << "Sorry, you have to be signed as a client to check orders." << endl;
		return INVALID_ACTION * INVALID_ROLE_LOGIN;
	}

	cout << "Please enter the order id." << endl;
	unsigned orderid;
	cin >> orderid;

	size_t ordersSize = ts.getOrders().getSize();
	for (size_t i = 0; i < ordersSize; i++)
	{
		if (ts.getOrders()[i].getOrderID() == orderid)
		{
			if (ts.getCurrentClientIndex() != ts.getOrders()[i].getClientID())
				return INVALID_ACTION;
			ts.getOrders()[i].describeOrder();
			if (ts.getOrders()[i].isAccepted())
				ts.getDrivers()[ts.getOrders()[i].getDriverID()].describeDriver();
			return SUCCESS;
		}
	}

	return INVALID_DATA * ORDER_NOT_FOUND;
}

int cancelOrderMenu(TaxiService& ts)
{
	/*if (!ts.isSignedInAsClient())
	{
		cout << "Sorry, you have to be signed as a client to cancel orders." << endl;
		return INVALID_ACTION | INVALID_ROLE_LOGIN;
	}*/

	if (ts.getCurrentClientIndex() == INVALID_INDEX)
	{
		cout << "Sorry, you have to be signed as a client to cancel orders." << endl;
		return INVALID_ACTION * INVALID_ROLE_LOGIN;
	}
	

	cout << "Please enter the order id." << endl;
	unsigned orderid;
	cin >> orderid;

	size_t ordersSize = ts.getOrders().getSize();
	for (size_t i = 0; i < ordersSize; i++)
	{
		if (ts.getOrders()[i].getOrderID() == orderid)
		{
			if (ts.getCurrentClientIndex() != ts.getOrders()[i].getClientID())
				return INVALID_ACTION;
			ts.cancelOrder(i);
			return SUCCESS;
		}
	}
	
	return INVALID_DATA * ORDER_NOT_FOUND;
}

int makePaymentMenu(TaxiService& ts)
{
	/*if (!ts.isSignedInAsClient())
	{
		cout << "Sorry, you have to be signed as a client to make payments." << endl;
		return INVALID_ACTION | INVALID_ROLE_LOGIN;
	}*/

	if (ts.getCurrentClientIndex() == INVALID_INDEX)
	{
		cout << "Sorry, you have to be signed as a client to make payments." << endl;
		return INVALID_ACTION * INVALID_ROLE_LOGIN;
	}
	

	cout << "Please enter the order id." << endl;
	unsigned orderid;
	cin >> orderid;

	cout << "Please enter the amount." << endl;
	double amount;
	cin >> amount;

	size_t ordersSize = ts.getOrders().getSize();
	for (size_t i = 0; i < ordersSize; i++)
	{
		if (ts.getOrders()[i].getOrderID() == orderid)
		{
			if (ts.getCurrentClientIndex() != ts.getOrders()[i].getClientID())
				return INVALID_ACTION;
			return ts.pay(i, amount);
		}
	}

	return INVALID_DATA * ORDER_NOT_FOUND;
}

int rateMenu(TaxiService& ts)
{
	if (ts.getCurrentClientIndex() == INVALID_INDEX)
	{
		return INVALID_ACTION * INVALID_ROLE_LOGIN;
	}

	cout << "Please enter the order id: " << endl;
	unsigned orderid;
	cin >> orderid;

	cout << "Please enter a rating from 1 to 5: " << endl;
	unsigned rating;
	cin >> rating;

	while (rating < 1 || rating > 5)
	{
		cout << "This is not a valid rating. Please enter a rating from 1 to 5: " << endl;
		cin >> rating;
	}

	size_t ordersSize = ts.getOrders().getSize();
	for (size_t i = 0; i < ordersSize; i++)
	{
		if (ts.getOrders()[i].getOrderID() == orderid)
		{
			if (ts.getCurrentClientIndex() != ts.getOrders()[i].getClientID())
				return INVALID_ACTION;
			return ts.rate(i, rating);
		}
	}

	cout << "ERROR! REACHED END OF RATE MENU! THIS SHOULD NOT HAPPEN!" << endl;
	return INVALID_DATA * ORDER_NOT_FOUND;
}

int checkMessagesMenu(TaxiService& ts)
{
	/*if (ts.isSignedInAsClient())
	{
		return INVALID_ACTION | INVALID_ROLE_LOGIN;
	}*/

	if (ts.getCurrentDriverIndex() == INVALID_INDEX)
	{
		return INVALID_ACTION * INVALID_ROLE_LOGIN;
	}
	

	ts.getDrivers()[ts.getCurrentDriverIndex()].checkMessages();
	return SUCCESS;
}

int acceptOrderMenu(TaxiService& ts)
{
	/*if (ts.isSignedInAsClient())
	{
		cout << "Sorry, you have to be signed as a driver to accept orders." << endl;
		return INVALID_ACTION | INVALID_ROLE_LOGIN;
	}*/

	if (ts.getCurrentDriverIndex() == INVALID_INDEX)
	{
		return INVALID_ACTION * INVALID_ROLE_LOGIN;
	}

	
	cout << "Please enter the order id." << endl;
	int orderID = INVALID_INDEX;
	cin >> orderID;
	size_t orderCount = ts.getOrders().getSize();
	for (size_t i = 0; i < orderCount; i++)
	{
		if (ts.getOrders()[i].getOrderID() == orderID)
		{
			return ts.acceptOrder(i);
			//return SUCCESS;
		}
	}

	return INVALID_DATA * ORDER_NOT_FOUND;

}

int declineOrderMenu(TaxiService& ts)
{
	/*if (ts.isSignedInAsClient())
	{
		cout << "Sorry, you have to be signed as a driver to decline orders." << endl;
		return INVALID_ACTION | INVALID_ROLE_LOGIN;
	}*/

	if (ts.getCurrentDriverIndex() == INVALID_INDEX)
	{
		return INVALID_ACTION * INVALID_ROLE_LOGIN;
	}
	

	cout << "Please enter the order id." << endl;
	int orderID = INVALID_INDEX;
	cin >> orderID;

	size_t orderCount = ts.getOrders().getSize();
	for (size_t i = 0; i < orderCount; i++)
	{
		if (ts.getOrders()[i].getOrderID() == orderID)
		{
			return ts.declineOrder(i);
		}
	}

	return INVALID_DATA * ORDER_NOT_FOUND;
}

int finishOrderMenu(TaxiService& ts)
{
	/*if (ts.isSignedInAsClient())
	{
		cout << "Sorry, you have to be signed as a driver to decline orders." << endl;
		return INVALID_ACTION | INVALID_ROLE_LOGIN;
	}*/

	if (ts.getCurrentDriverIndex() == INVALID_INDEX)
	{
		return INVALID_ACTION * INVALID_ROLE_LOGIN;
	}
	

	cout << "Please enter the order id." << endl;
	int orderID = INVALID_INDEX;
	cin >> orderID;

	size_t orderCount = ts.getOrders().getSize();
	for (size_t i = 0; i < orderCount; i++)
	{
		if (ts.getOrders()[i].getOrderID() == orderID)
		{
			return ts.finishOrder(i);
		}
	}

	return INVALID_DATA * ORDER_NOT_FOUND;
}

int acceptPaymentMenu(TaxiService& ts)
{
	//if (ts.isSignedInAsClient())
	//	return INVALID_ACTION | INVALID_ROLE_LOGIN;

	if (ts.getCurrentDriverIndex() == INVALID_INDEX)
	{
		return INVALID_ACTION * INVALID_ROLE_LOGIN;
	}

	cout << "Please enter the order id." << endl;
	int orderID = INVALID_INDEX;
	cin >> orderID;

	cout << "Please enter the amount." << endl;
	double amount;
	cin >> amount;

	size_t orderCount = ts.getOrders().getSize();
	for (size_t i = 0; i < orderCount; i++)
	{
		if (ts.getOrders()[i].getOrderID() == orderID)
		{
			return ts.acceptPayment(i, amount);
		}
	}

	return INVALID_DATA * ORDER_NOT_FOUND;
}

int checkRatingMenu(const TaxiService& ts)
{
	if (ts.getCurrentDriverIndex() == INVALID_INDEX)
		return INVALID_ACTION * INVALID_ROLE_LOGIN;

	cout << "Your current rating is " << ts.checkRating() << endl;
	return SUCCESS;
}


int menu(TaxiService& ts)
{
	cout << "Welcome to the taxi service!" << endl;
	int action = 0, actionResult = 0;
	do
	{
		cout << "Please select what action you would like to do: " << endl;
		cout << "Enter " << REGISTER_CLIENT << " to register as a client, " << REGISTER_DRIVER << " to register as a driver, "
			<< LOGIN << " to log in, or " << LOGOUT << " to log out." << endl;
		cout << endl;

		cout << "As a client, you can enter " << MAKE_ORDER << " to make an order, " << CHECK_ORDER << " to check an order, "
			<< CANCEL_ORDER << " to cancel an order, " << MAKE_PAYMENT << " to pay for your finished order, or " 
			<< RATE << " to rate your driver." << endl;
		cout << endl;

		cout << "As a driver, you can enter " << CHECK_MESSAGES << " to view your messages, " << ACCEPT_ORDER << " to accept an order, "
			<< DECLINE_ORDER << " to decline an order, " << FINISH_ORDER << " to finish an order" << ACCEPT_PAYMENT << " to accept payment for an order, or " 
			<< CHECK_RATING << " to check your rating." << endl;
		cout << endl;

		cout << "Or you can enter " << EXIT << " to exit the program." << endl;
		cin >> action;
		if (action == EXIT)
			break;

		switch (action)
		{
		case REGISTER_CLIENT:
			actionResult = registerClientMenu(ts);
			break;
		case REGISTER_DRIVER:
			actionResult = registerDriverMenu(ts);
			break;
		case LOGIN:
			actionResult = loginMenu(ts);
			break;
		case LOGOUT:
			actionResult = logoutMenu(ts);
			break;
		case MAKE_ORDER:
			actionResult = makeOrderMenu(ts);
			break;
		case CHECK_ORDER:
			actionResult = checkOrderMenu(ts);
			break;
		case CANCEL_ORDER:
			actionResult = cancelOrderMenu(ts);
			break;
		case MAKE_PAYMENT:
			actionResult = makePaymentMenu(ts);
			break;
		case RATE:
			actionResult = rateMenu(ts);
			break;
		case CHECK_MESSAGES:
			actionResult = checkMessagesMenu(ts);
			break;
		case ACCEPT_ORDER:
			actionResult = acceptOrderMenu(ts);
			break;
		case DECLINE_ORDER:
			actionResult = declineOrderMenu(ts);
			break;
		case FINISH_ORDER:
			actionResult = finishOrderMenu(ts);
			break;
		case ACCEPT_PAYMENT:
			actionResult = acceptPaymentMenu(ts);
			break;
		case CHECK_RATING:
			actionResult = checkRatingMenu(ts);
			break;
		default:
			actionResult = INVALID_ACTION;
			break;
		}
		actionHandler(actionResult);
	} while (action != EXIT);

	cout << "You have exited the programme. Thank you for using it! Have a great day! " << endl;
	return SUCCESS;
}

int main()
{
	TaxiService ts;
	return menu(ts);
}