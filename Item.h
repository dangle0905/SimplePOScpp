#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class Item
{
public:
	string UPC;
	string description;
	int itemMaxQuantity;
	int orderThreshold;
	int replenishmentOrderQuantity;
	int itemOnHand;
	double unitPrice;
	Item() {};
	~Item() {};
	Item(string UPC, string description, string itemMaxQuantity, string orderThreshold, string replenishmentOrderQuantity, string itemOnHand, string unitPrice)
	{
		this->UPC = UPC;
		this->description = description;
		this->itemMaxQuantity = stoi(itemMaxQuantity);
		this->orderThreshold = stoi(orderThreshold);
		this->replenishmentOrderQuantity = stoi(replenishmentOrderQuantity);
		this->itemOnHand = stoi(itemOnHand);
		this->unitPrice = stod(unitPrice);
	}
	void UpdateUnitOnHand(int itemOnHand);
};

