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

void actionHandler(int errorCode)
{
	if (errorCode == SUCCESS)
		cout << "You have successfully logged out!" << endl; //for testing purposes only
}

int registerClientMenu(TaxiService& ts)
{
	//tbi
	return 0;
}

int registerDriverMenu(TaxiService& ts)
{
	//tbi
	return 0;
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
		return INVALID_ACTION | INVALID_ROLE_LOGIN;
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
		return INVALID_ACTION | INVALID_ROLE_LOGIN;
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
			return SUCCESS;
		}
	}

	return INVALID_DATA | ORDER_NOT_FOUND;
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
		return INVALID_ACTION | INVALID_ROLE_LOGIN;
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
	
	return INVALID_DATA | ORDER_NOT_FOUND;
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
		return INVALID_ACTION | INVALID_ROLE_LOGIN;
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

	return INVALID_DATA | ORDER_NOT_FOUND;
}

int checkMessagesMenu(TaxiService& ts)
{
	/*if (ts.isSignedInAsClient())
	{
		return INVALID_ACTION | INVALID_ROLE_LOGIN;
	}*/

	if (ts.getCurrentDriverIndex() == INVALID_INDEX)
	{
		return INVALID_ACTION | INVALID_ROLE_LOGIN;
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
		return INVALID_ACTION | INVALID_ROLE_LOGIN;
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

	return INVALID_DATA | ORDER_NOT_FOUND;

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
		return INVALID_ACTION | INVALID_ROLE_LOGIN;
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

	return INVALID_DATA | ORDER_NOT_FOUND;
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
		return INVALID_ACTION | INVALID_ROLE_LOGIN;
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

	return INVALID_DATA | ORDER_NOT_FOUND;
}

int acceptPaymentMenu(TaxiService& ts)
{
	//if (ts.isSignedInAsClient())
	//	return INVALID_ACTION | INVALID_ROLE_LOGIN;

	if (ts.getCurrentDriverIndex() == INVALID_INDEX)
	{
		return INVALID_ACTION | INVALID_ROLE_LOGIN;
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

	return INVALID_DATA | ORDER_NOT_FOUND;
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
		cout << "As a client, you can enter " << MAKE_ORDER << " to make an order, " << CHECK_ORDER << " to check an order, "
			<< CANCEL_ORDER << " to cancel an order, or " << MAKE_PAYMENT << " to pay for your finished order." << endl;
		cout << "As a driver, you can enter " << CHECK_MESSAGES << " to view your messages, " << ACCEPT_ORDER << " to accept an order, "
			<< DECLINE_ORDER << " to decline an order, " << FINISH_ORDER << " to finish an order, or " << ACCEPT_PAYMENT << " to accept payment for an order." << endl;
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