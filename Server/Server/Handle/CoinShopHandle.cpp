#include "StdAfx.h"
#include "CoinShopHandle.h"

CCoinShopHandle::CCoinShopHandle()
{
	m_iChangeNickPrice = 500;
	m_iAgingRecoveryPrice = 1000;
}
CCoinShopHandle::~CCoinShopHandle()
{

}
void CCoinShopHandle::SQLCoinLog(char * pszAccountName, char * pszDescription)
{
	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_LogDB);


	if (pcDB->Open())
	{
		if (pcDB->Prepare("INSERT INTO CoinLog([AccountName],[Description],[Date]) VALUES (?,?,GETDATE())"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_String, pszAccountName, lstrlenA(pszAccountName));
			pcDB->BindParameterInput(2, PARAMTYPE_String, pszDescription, lstrlenA(pszDescription));
			pcDB->Execute();
		}
		pcDB->Close();
	}
}
void CCoinShopHandle::LoadCoinShop(int iCoinShopID)
{
	DELET(m_pcCoinShop);

	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_GameDB);

	if (pcDB->Open())
	{
		BOOL bCoinShopLoaded = FALSE;
		int iSelectedCoinShopID;
		char szName[64];
		char szMessage[256];
		int iDiscountP;

		if (iCoinShopID != -1)
		{
			if (pcDB->Prepare("SELECT ID, Name, Message, Discount FROM CoinShop WHERE ID=?"))
			{
				//Bind Parameter
				pcDB->BindParameterInput(1, PARAMTYPE_Integer, &iCoinShopID);
			}
		}
		else
		{
			pcDB->Prepare("SELECT ID, Name, Message, Discount From CoinShop WHERE Active=1");
		}

		if (pcDB->Execute() && pcDB->Fetch())
		{
			pcDB->GetData(1, PARAMTYPE_Integer, &iSelectedCoinShopID);
			pcDB->GetData(2, PARAMTYPE_String, szName, _countof(szName));
			pcDB->GetData(3, PARAMTYPE_String, szMessage, _countof(szMessage));
			pcDB->GetData(4, PARAMTYPE_Integer, &iDiscountP);

			bCoinShopLoaded = TRUE;
		}

		if (bCoinShopLoaded)
		{
			pcDB->Clear();

			if ((iCoinShopID != -1) && (iCoinShopID == iSelectedCoinShopID))
			{
				pcDB->Prepare("UPDATE CoinShop SET Active=0");
				pcDB->Execute();
				pcDB->Clear();

				if (pcDB->Prepare("UPDATE CoinShop SET Active=1 WHERE ID=?"))
				{
					pcDB->BindParameterInput(1, PARAMTYPE_Integer, &iCoinShopID);

					pcDB->Execute();
				}
				pcDB->Clear();
			}

			m_pcCoinShop = new CCoinShop(iSelectedCoinShopID);
			m_pcCoinShop->SetName(szName);
			m_pcCoinShop->SetMessage(szMessage);
			m_pcCoinShop->SetDiscount(iDiscountP);

			//Tabs
			int lCoinShopTabID = -1;
			int lCoinShopTabParentID = 0;
			char szTabName[32];
			int iTabDiscountP = 0;
			int iTabBulk = 0;
			int iMaxTabBulk = 0;

			if (pcDB->Prepare("SELECT ID, Name, ParentID, Discount, [Bulk], MaxBulk FROM CoinShopTab WHERE CoinShopID=? ORDER BY ParentID ASC, ListOrder ASC"))
			{
				pcDB->BindParameterInput(1, PARAMTYPE_Integer, &iSelectedCoinShopID);

				if (pcDB->Execute())
				{
					while (pcDB->Fetch())
					{
						pcDB->GetData(1, PARAMTYPE_Integer, &lCoinShopTabID);
						pcDB->GetData(2, PARAMTYPE_String, szTabName, _countof(szTabName));
						pcDB->GetData(3, PARAMTYPE_Integer, &lCoinShopTabParentID);
						pcDB->GetData(4, PARAMTYPE_Integer, &iTabDiscountP);
						pcDB->GetData(5, PARAMTYPE_Integer, &iTabBulk);
						pcDB->GetData(6, PARAMTYPE_Integer, &iMaxTabBulk);

						CCoinShopTab * pcTab = new CCoinShopTab(lCoinShopTabID, szTabName, lCoinShopTabParentID, iTabBulk, iMaxTabBulk);
						pcTab->SetDiscount(iDiscountP != 0 ? iDiscountP : iTabDiscountP);

						if (pcTab->GetParentTabID() != 0)
						{
							//Has a Parent, so add it as a Child Tab of another Tab
							CCoinShopTab * pcParentTab = m_pcCoinShop->GetTabByID(pcTab->GetParentTabID());

							if (pcParentTab)
								pcParentTab->AddChildTab(pcTab);
						}
						else
						{
							//Must be a root Tab
							m_pcCoinShop->AddTab(pcTab);
						}
					}
				}
			}

			//Items
			std::vector<CCoinShopTab*> vTabs = m_pcCoinShop->GetAllTabs();
			for (std::vector<CCoinShopTab*>::iterator it = vTabs.begin(); it != vTabs.end(); it++)
			{
				pcDB->Clear();

				CCoinShopTab * pcTab = *it;

				int lTabID = pcTab->GetID();

				if (pcDB->Prepare("SELECT ID, Name, Description, Code, Image, Value, Discount,	[Bulk], MaxBulk, IsSpec, IsQuantity FROM CoinShopItem WHERE TabID=? AND Disabled=0 ORDER BY ListOrder ASC"))
				{
					pcDB->BindParameterInput(1, PARAMTYPE_Integer, &lTabID);

					if (pcDB->Execute())
					{
						while (pcDB->Fetch())
						{
							int lID;
							char szName[32];
							char szDescription[128];
							char szCode[8];
							char szImage[64];
							int iValue;
							int iDiscount;
							int iBulk;
							int iMaxBulk;
							BOOL bSpec;
							BOOL bQuantity;

							pcDB->GetData(1, PARAMTYPE_Integer, &lID);
							pcDB->GetData(2, PARAMTYPE_String, szName, _countof(szName));
							pcDB->GetData(3, PARAMTYPE_String, szDescription, _countof(szDescription));
							pcDB->GetData(4, PARAMTYPE_String, szCode, _countof(szCode));
							pcDB->GetData(5, PARAMTYPE_String, szImage, _countof(szImage));
							pcDB->GetData(6, PARAMTYPE_Integer, &iValue);
							pcDB->GetData(7, PARAMTYPE_Integer, &iDiscount);
							pcDB->GetData(8, PARAMTYPE_Integer, &iBulk);
							pcDB->GetData(9, PARAMTYPE_Integer, &iMaxBulk);
							pcDB->GetData(10, PARAMTYPE_Integer, &bSpec);
							pcDB->GetData(11, PARAMTYPE_Integer, &bQuantity);

							//Calculate real Discount
							int iRealDiscount = iDiscount;
							if (iRealDiscount == 0)
							{
								if (iDiscountP != 0)
								{
									//Use the Global Discount Percentile to Discount this Item
									iRealDiscount = (iValue * iDiscountP) / 100;
								}
							}

							//Create Item
							CCoinShopItem * pcItem = new CCoinShopItem(lID, lTabID, szName, szDescription, szCode, szImage, iValue, iRealDiscount, iBulk, iMaxBulk, bSpec, bQuantity);

							//Add Item to Tab
							pcTab->AddItem(pcItem);
						}
					}
				}
			}
		}
		pcDB->Close();
	}
}
void CCoinShopHandle::Init()
{
	if (!GAME_SERVER)
		LoadCoinShop();
}
int CCoinShopHandle::GetCoinAmount(char * pszAccountName)
{
	if ((pszAccountName == NULL) || (pszAccountName[0] == 0))
		return 0;

	int iRet = 0;

	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_UserDB);

	if (pcDB->Open())
	{
		if (pcDB->Prepare("SELECT Coins FROM UserInfo WHERE AccountName=?"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_String, pszAccountName, lstrlenA(pszAccountName));

			if (pcDB->Execute() && pcDB->Fetch())
				pcDB->GetData(1, PARAMTYPE_Integer, &iRet);
		}

		pcDB->Close();
	}

	return iRet;
}
int CCoinShopHandle::GetCoinTradeAmount(char * pszAccountName)
{
	if ((pszAccountName == NULL) || (pszAccountName[0] == 0))
		return 0;

	int iRet = 0;

	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_UserDB);

	if (pcDB->Open())
	{
		if (pcDB->Prepare("SELECT CoinsTraded FROM UserInfo WHERE AccountName=?"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_String, pszAccountName, lstrlenA(pszAccountName));

			if (pcDB->Execute() && pcDB->Fetch())
				pcDB->GetData(1, PARAMTYPE_Integer, &iRet);
		}

		pcDB->Close();
	}

	return iRet;
}
int CCoinShopHandle::GetBulkValue(CCoinShopItem * pcItem, int iQuantity)
{
	if (pcItem)
	{
		if (pcItem->GetBulk() && iQuantity >= 5)
		{
			int iValue = iQuantity / 5;
			if ((iValue*pcItem->GetBulk()) > pcItem->GetMaxBulk())
				iValue = pcItem->GetMaxBulk() / 5;

			int iPrice = (pcItem->GetDiscount() > 0 ? pcItem->GetDiscount() : pcItem->GetValue())  * iQuantity;

			return (iPrice*(pcItem->GetBulk() * iValue)) / 100;
		}
	}
	return 0;
}
int CCoinShopHandle::UseCoin(char * pszAccountName, int iCoinAmount)
{
	if (pszAccountName[0] == 0)
		return 0;

	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_UserDB);

	if (pcDB->Open())
	{
		if (pcDB->Prepare("UPDATE UserInfo SET Coins=Coins-? WHERE AccountName=?"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_Integer, &iCoinAmount);
			pcDB->BindParameterInput(2, PARAMTYPE_String, pszAccountName, lstrlenA(pszAccountName));

			if (!pcDB->Execute())
			{
				//Log Error

			}
		}

		pcDB->Close();
	}

	return GetCoinAmount(pszAccountName);
}
void CCoinShopHandle::AddTradeCoin(char * pszAccountName, int iCoinAmount)
{
	if (pszAccountName[0] == 0)
		return;

	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_UserDB);

	if (pcDB->Open())
	{
		if (pcDB->Prepare("UPDATE UserInfo SET CoinsTraded=CoinsTraded+? WHERE AccountName=?"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_Integer, &iCoinAmount);
			pcDB->BindParameterInput(2, PARAMTYPE_String, pszAccountName, lstrlenA(pszAccountName));

			if (!pcDB->Execute())
			{
				//Log Error

			}
		}

		pcDB->Close();
	}
}
int CCoinShopHandle::AddCoin(char * pszAccountName, int iCoinAmount)
{
	if (pszAccountName[0] == 0)
		return 0;

	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_UserDB);

	if (pcDB->Open())
	{
		if (pcDB->Prepare("UPDATE UserInfo SET Coins=Coins+? WHERE AccountName=?"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_Integer, &iCoinAmount);
			pcDB->BindParameterInput(2, PARAMTYPE_String, pszAccountName, lstrlenA(pszAccountName));

			if (!pcDB->Execute())
			{
				//Log Error

			}
		}

		pcDB->Close();
	}

	return GetCoinAmount(pszAccountName);
}
BOOL CCoinShopHandle::HasCoinAmount(char * pszAccountName, int iCoinAmount)
{
	int iCoins = GetCoinAmount(pszAccountName);

	if (iCoins >= iCoinAmount)
		return TRUE;

	return FALSE;
}
BOOL CCoinShopHandle::PerfectizeItem(User * pcUser, PacketCoinServiceBuy * psPacket)
{
	ItemData * pcItemData = &psPacket->ItemPerfect.cItemData;

	Item sOldItem;
	CopyMemory(&sOldItem, &pcItemData->sItem, sizeof(Item));

	//Item cannot be Perfect
	if (pcItemData->sItem.bPerfectItem == FALSE)
	{
		int iCoins = 0;

		//Set Price
		iCoins = Base::Coin::GetPerfectizePrice(&pcItemData->sItem);

		//Global Discount
		if (m_pcCoinShop->GetDiscount() > 0)
			iCoins = (m_pcCoinShop->GetDiscount() * iCoins) / 100;

		//Price setted and have Coins?
		if (iCoins > 0 && HasCoinAmount(pcUser->szAccountName, iCoins))
		{
			Item sItem;

			int iItemID = pcItemData->sItem.sItemID.ToInt();

			if ((iItemID & 0xFFFFFF00) == ITEMID_SpecStoneCode)
				iItemID += 10; // Deluxe

			DefinitionItem * psDefItem = SERVERITEM->FindItemDefByCode(iItemID);

			//Item Exists?
			if (psDefItem)
			{

				int iSpec = pcItemData->sItem.eSpecialization;

				//Check if Have Spec
				if (iSpec != 0)
				{
					int iNewSpec = 0;

					for (int i = 0; i < psDefItem->JobBitCodeRandomCount; i++)
					{
						if (psDefItem->dwJobBitCode_Random[i] == iSpec)
						{
							iNewSpec = iSpec;
							break;
						}
					}

					if (iNewSpec != iSpec)
					{
						if (psDefItem->sItem.eSpecialization != iSpec)
							iSpec = 0;
					}
				}

				//Create Perfect Item
				SERVERITEM->CreatePerfectItem(&sItem, psDefItem, ClassFlagToCharacterClass((EClassFlag)iSpec));

				//Discount Coins
				UseCoin(pcUser->szAccountName, iCoins);

				//Delete Old Item
				SERVERITEM->DeleteItemInventory(pcUser, pcItemData->sItem.sItemID.ToInt(), pcItemData->sItem.iChk1, pcItemData->sItem.iChk2);

				//Update Item
				CopyMemory(&pcItemData->sItem, &sItem, sizeof(Item));

				//Item NS?
				if (iSpec == 0)
				{
					pcItemData->sItem.eSpecialization = 0;
					ZeroMemory(&pcItemData->sItem.sSpecData, sizeof(SpecItemData));
				}

				//Upgrade Status
				SERVERITEM->UpgradeNewItem(&sOldItem, &pcItemData->sItem);

				//Name
				if ((iItemID & 0xFFFFFF00) != ITEMID_SpecStoneCode)
					STRINGCOPY(pcItemData->sItem.szItemName, sOldItem.szItemName);

				//Validate
				SERVERITEM->ValidateItem(&pcItemData->sItem);

				SERVERITEM->SaveItemData(&pcItemData->sItem);

				SERVERITEM->AddItemInventory(pcUser, pcItemData->sItem.sItemID.ToInt(), pcItemData->sItem.iChk1, pcItemData->sItem.iChk2);

				//Success
				psPacket->iRetCode = 1;

				//Send to User
				ProcessPacket(pcUser, psPacket);

				char szItemName[32] = { 0 };
				SERVERITEM->FindItemName(pcItemData->sItem.sItemID.ToInt(), szItemName);

				//Log It
				SERVERLOG->OnLogItemEx(pcUser, ITEMLOGID_PerfectizedItem, "[%s](%s) Perfectized Item ( [%s][0x%08X] %d x %d -> %d x %d )",
					pcUser->szAccountName, SERVERCHARACTER->GetCharacterName(pcUser), szItemName, pcItemData->sItem.sItemID.ToInt(),
					sOldItem.iChk1, sOldItem.iChk2, pcItemData->sItem.iChk1, pcItemData->sItem.iChk2);

				//Log It...
				SQLCoinLog(pcUser->szAccountName, (char*)FormatString("AccountName[%s] Character[%s] Bought[Perfectize] Spec[%d] Price[%d] CoinAmount[%d]",
					pcUser->szAccountName, SERVERCHARACTER->GetCharacterName(pcUser), psPacket->ItemPerfect.iSpec,
					iCoins, GetCoinAmount(pcUser->szAccountName)));

				//Success!
				return TRUE;
			}
			else
			{
				psPacket->iRetCode = -3; //Item Dont exists
				ProcessPacket(pcUser, psPacket);
			}
		}
		else
		{
			SERVERCHAT->SendChatMessageBox(pcUser, "Not enough credits!");
			SERVERCHAT->SendChat(pcUser, CHATCOLOR_Global, "> Not enough credits!");
			psPacket->iRetCode = -1; //Not coins
			ProcessPacket(pcUser, psPacket);
		}
	}
	else
	{
		psPacket->iRetCode = -4; //Already Perfect
		ProcessPacket(pcUser, psPacket);
		SERVERCHAT->SendChatMessageBox(pcUser, "This item is already perfect!");
	}
	//FAIL!
	return FALSE;
}
BOOL CCoinShopHandle::ItemSwapper(User * pcUser, PacketCoinServiceBuy * psPacket)
{
	ItemData * pcItemData = &psPacket->ItemSwapper.cItemData;

	Item sOldItem;
	CopyMemory(&sOldItem, &pcItemData->sItem, sizeof(Item));

	//Item cannot be Perfect
	if (pcItemData->sItem.bPerfectItem == TRUE)
	{
		int iCoins = 0;

		int iLevelItem = pcItemData->sItem.iLevel;
		if (pcItemData->sItem.eCraftType == ITEMCRAFTTYPE_Aging && pcItemData->sItem.sAgeLevel > 0)
		{
			int iLevelAge = Base::Coin::GetLevelItemEachAge(&pcItemData->sItem);

			if (iLevelAge > 0)
				iLevelItem -= (pcItemData->sItem.sAgeLevel / iLevelAge);
		}


		//Set Price
		iCoins = Base::Coin::GetSwapperPrice(&pcItemData->sItem, psPacket->ItemSwapper.iItemBase);

		//Global Discount
		if (m_pcCoinShop->GetDiscount() > 0)
			iCoins = (m_pcCoinShop->GetDiscount() * iCoins) / 100;

		//Price setted and have Coins?
		if (iCoins > 0 && HasCoinAmount(pcUser->szAccountName, iCoins))
		{
			Item sItem;
			DefinitionItem * psDefItem = SERVERITEM->FindItemDefByLevelBase(psPacket->ItemSwapper.iItemBase, iLevelItem);

			//Item Exists?
			if (psDefItem)
			{

				int iSpec = pcItemData->sItem.eSpecialization;

				//Check if Have Spec
				if (iSpec != 0)
				{
					int iNewSpec = 0;

					for (int i = 0; i < psDefItem->JobBitCodeRandomCount; i++)
					{
						if (psDefItem->dwJobBitCode_Random[i] == iSpec)
						{
							iNewSpec = iSpec;
							break;
						}
					}

					if (iNewSpec != iSpec)
					{
						if (psDefItem->sItem.eSpecialization != iSpec)
							iSpec = 0;
					}
				}

				//Create Perfect Item
				SERVERITEM->CreatePerfectItem(&sItem, psDefItem, ClassFlagToCharacterClass((EClassFlag)iSpec));

				//Discount Coins
				UseCoin(pcUser->szAccountName, iCoins);

				SERVERITEM->DeleteItemInventory(pcUser, pcItemData->sItem.sItemID.ToInt(), pcItemData->sItem.iChk1, pcItemData->sItem.iChk2);

				//Update Item
				CopyMemory(&pcItemData->sItem, &sItem, sizeof(Item));

				//Item NS?
				if (iSpec == 0)
				{
					pcItemData->sItem.eSpecialization = 0;
					ZeroMemory(&pcItemData->sItem.sSpecData, sizeof(SpecItemData));
				}

				//Upgrade Status
				SERVERITEM->UpgradeNewItem(&sOldItem, &pcItemData->sItem);

				//Validate
				SERVERITEM->ValidateItem(&pcItemData->sItem);

				SERVERITEM->SaveItemData(&pcItemData->sItem);

				SERVERITEM->AddItemInventory(pcUser, pcItemData->sItem.sItemID.ToInt(), pcItemData->sItem.iChk1, pcItemData->sItem.iChk2);

				//Success
				psPacket->iRetCode = 1;

				//Send to User
				ProcessPacket(pcUser, psPacket);

				char szItemName[32] = { 0 };
				SERVERITEM->FindItemName(pcItemData->sItem.sItemID.ToInt(), szItemName);

				//Log It
				SERVERLOG->OnLogItemEx(pcUser, ITEMLOGID_SwappedItem, "[%s](%s) Swapped Item ( [%s][0x%08X] %d x %d -> %d x %d )",
					pcUser->szAccountName, SERVERCHARACTER->GetCharacterName(pcUser), szItemName, pcItemData->sItem.sItemID.ToInt(),
					sOldItem.iChk1, sOldItem.iChk2, pcItemData->sItem.iChk1, pcItemData->sItem.iChk2);

				//Log It...
				SQLCoinLog(pcUser->szAccountName, (char*)FormatString("AccountName[%s] Character[%s] Bought[ItemSwapper] Spec[%d] Price[%d] CoinAmount[%d]",
					pcUser->szAccountName, SERVERCHARACTER->GetCharacterName(pcUser), psPacket->ItemPerfect.iSpec,
					iCoins, GetCoinAmount(pcUser->szAccountName)));

				//Success!
				return TRUE;
			}
			else
			{
				psPacket->iRetCode = -3; //Item Dont exists
				ProcessPacket(pcUser, psPacket);
			}
		}
		else
		{
			SERVERCHAT->SendChatMessageBox(pcUser, "Not enough credits!");
			SERVERCHAT->SendChat(pcUser, CHATCOLOR_Global, "> Not enough credits!");
			psPacket->iRetCode = -1;
			ProcessPacket(pcUser, psPacket);
		}
	}
	else
	{
		psPacket->iRetCode = -2; //Must be perfect
		ProcessPacket(pcUser, psPacket);
	}

	//FAIL!
	return FALSE;
}
BOOL CCoinShopHandle::ChangeNick(User * pcUser, PacketCoinServiceBuy * psPacket)
{
	if (HasCoinAmount(pcUser->szAccountName, m_iChangeNickPrice))
	{
		if (SERVERCHARACTER->SQLGetCharacterClanID(psPacket->ChangeNick.szNewCharacterName) == (-1))
		{

			for (int i = 0; i < _countof(pszaNotAllowedNamesChangeNick); i++)
			{
				if (strstr(MakeLower(psPacket->ChangeNick.szNewCharacterName).c_str(), pszaNotAllowedNamesChangeNick[i]))
				{
					SERVERCHAT->SendChatMessageBox(pcUser, "Character Name not allowed! choose other!");
					SERVERCHAT->SendChat(pcUser, CHATCOLOR_Global, "> Character Name not allowed! choose other!");

					psPacket->iRetCode = -3;
					ProcessPacket(pcUser, psPacket);
					return FALSE;
				}
			}

			SERVERCOMMAND->AddCommand(SQLSERVERCOMMAND_ChangeCharacterName, SERVERCHARACTER->GetCharacterName(pcUser), psPacket->ChangeNick.szNewCharacterName, "");

			UseCoin(pcUser->szAccountName, m_iChangeNickPrice);

			//Log It...
			SQLCoinLog(pcUser->szAccountName, (char*)FormatString("AccountName[%s] Character[%s] Bought[ChangeCharacterName] NewCharacterName[%s] Coins[%d]",
				pcUser->szAccountName, SERVERCHARACTER->GetCharacterName(pcUser), psPacket->ChangeNick.szNewCharacterName, m_iChangeNickPrice));

			psPacket->iRetCode = 1;
			ProcessPacket(pcUser, psPacket);
		}
		else
		{
			SERVERCHAT->SendChatMessageBox(pcUser, "Character Name already exists!");
			SERVERCHAT->SendChat(pcUser, CHATCOLOR_Global, "> Character Name already exists!");
			psPacket->iRetCode = -2;
			ProcessPacket(pcUser, psPacket);
			return FALSE;
		}
	}
	else
	{
		SERVERCHAT->SendChatMessageBox(pcUser, "Not enough credits!");
		SERVERCHAT->SendChat(pcUser, CHATCOLOR_Global, "> Not enough credits!");
		psPacket->iRetCode = -1;
		ProcessPacket(pcUser, psPacket);
		return FALSE;
	}

	return TRUE;
}
BOOL CCoinShopHandle::AgingRecovery(User * pcUser, PacketCoinServiceBuy * psPacket)
{
	if (HasCoinAmount(pcUser->szAccountName, m_iAgingRecoveryPrice))
	{
		Item sItem;

		if (AGEHANDLE->GetItemDataBroke(pcUser, &sItem, psPacket->AgingRecovery.iID))
		{
			UseCoin(pcUser->szAccountName, m_iAgingRecoveryPrice);

			SERVERITEM->AddItemInventory(pcUser, sItem.sItemID.ToInt(), sItem.iChk1, sItem.iChk2);

			CopyMemory(&psPacket->AgingRecovery.cItemData.sItem, &sItem, sizeof(Item));

			//Log It...
			SQLCoinLog(pcUser->szAccountName, (char*)FormatString("AccountName[%s] Character[%s] Bought[AgingRecovery] ItemName[%s] ItemID[0x%08X] Code1[%d] Code2[%d] Coins[%d]",
				pcUser->szAccountName, SERVERCHARACTER->GetCharacterName(pcUser), sItem.szItemName, sItem.sItemID.ToInt(), sItem.iChk1, sItem.iChk2, m_iAgingRecoveryPrice));

			AGEHANDLE->SQLItemBrokeRecovered(pcUser, psPacket->AgingRecovery.iID);

			psPacket->iRetCode = 1;
			ProcessPacket(pcUser, psPacket);
		}
	}
	else
	{
		SERVERCHAT->SendChatMessageBox(pcUser, "Not enough credits!");
		SERVERCHAT->SendChat(pcUser, CHATCOLOR_Global, "> Not enough credits!");
		psPacket->iRetCode = -1;
		ProcessPacket(pcUser, psPacket);
	}

	return TRUE;
}
BOOL CCoinShopHandle::ChangeClass(User * pcUser, PacketCoinServiceBuy * psPacket)
{
	int iCoins = 0;

	//Set Price
	iCoins = psPacket->ChangeClass.bPremiumChangeClass == TRUE ? 6500 : 3500;

	//Global Discount
	if (m_pcCoinShop->GetDiscount() > 0)
		iCoins = (m_pcCoinShop->GetDiscount() * iCoins) / 100;

	//Price setted and have Coins?
	if (iCoins > 0 && HasCoinAmount(pcUser->szAccountName, iCoins))
	{
		if (SERVERCOMMAND->SQLReadFromCharacter(SERVERCHARACTER->GetCharacterName(pcUser), SQLSERVERCOMMAND_ChangeCharacterClass, SQLServerCommand()))
		{
			SERVERCHAT->SendChatMessageBox(pcUser, "You have a change class in the queue!");
			SERVERCHAT->SendChat(pcUser, CHATCOLOR_Global, "> You have a change class in the queue!");
			psPacket->iRetCode = -4;
			ProcessPacket(pcUser, psPacket);
			return FALSE;
		}

		if (psPacket->ChangeClass.szNewCharacterName[0] != 0)
		{
			if (SERVERCHARACTER->SQLGetCharacterClanID(psPacket->ChangeClass.szNewCharacterName) == (-1))
			{
				for (int i = 0; i < _countof(pszaNotAllowedNamesChangeNick); i++)
				{
					if (strstr(MakeLower(psPacket->ChangeClass.szNewCharacterName).c_str(), pszaNotAllowedNamesChangeNick[i]))
					{
						SERVERCHAT->SendChatMessageBox(pcUser, "Character Name not allowed! choose other!");
						SERVERCHAT->SendChat(pcUser, CHATCOLOR_Global, "> Character Name not allowed! choose other!");

						psPacket->iRetCode = -3;
						ProcessPacket(pcUser, psPacket);
						return FALSE;
					}
				}

				SERVERCOMMAND->AddCommand(SQLSERVERCOMMAND_ChangeCharacterName, SERVERCHARACTER->GetCharacterName(pcUser), psPacket->ChangeClass.szNewCharacterName, "");

				//Log It...
				SQLCoinLog(pcUser->szAccountName, (char*)FormatString("AccountName[%s] Character[%s] Bought[ChangeCharacterName] NewCharacterName[%s] Change Class",
					pcUser->szAccountName, SERVERCHARACTER->GetCharacterName(pcUser), psPacket->ChangeClass.szNewCharacterName));
			}
			else
			{
				SERVERCHAT->SendChatMessageBox(pcUser, "Character Name already exists!");
				SERVERCHAT->SendChat(pcUser, CHATCOLOR_Global, "> Character Name already exists!");
				psPacket->iRetCode = -2;
				ProcessPacket(pcUser, psPacket);
				return FALSE;
			}
		}
		else
			STRINGCOPY(psPacket->ChangeClass.szNewCharacterName, SERVERCHARACTER->GetCharacterName(pcUser));

		char szClass[32] = { 0 };
		STRINGFORMAT(szClass, "%d", psPacket->ChangeClass.iClass);

		char szItemID[32] = { 0 };
		STRINGFORMAT(szItemID, "JV1%d", psPacket->ChangeClass.iClass + 10);

		UseCoin(pcUser->szAccountName, iCoins);

		SERVERCOMMAND->AddCommand(SQLSERVERCOMMAND_ChangeCharacterClass, psPacket->ChangeClass.szNewCharacterName, szClass, SERVERCHARACTER->GetCharacterName(pcUser));

		if (psPacket->ChangeClass.bPremiumChangeClass)
			DISTRIBUTORHANDLE->AddItemOpenBox(pcUser->szAccountName, szItemID, 0, 8);

		//Log It...
		SQLCoinLog(pcUser->szAccountName, (char*)FormatString("AccountName[%s] Character[%s] Bought[ChangeCharacterClass] NewClass[%d] Premium[%s]",
			pcUser->szAccountName, psPacket->ChangeClass.szNewCharacterName, psPacket->ChangeClass.iClass, psPacket->ChangeClass.bPremiumChangeClass ? "Yes" : "No"));

		psPacket->iRetCode = 1;
		ProcessPacket(pcUser, psPacket);
	}

	return TRUE;
}
void CCoinShopHandle::ProcessPacket(User * pcUser, PacketCoinServiceBuy * psPacket)
{
	psPacket->iLength = sizeof(PacketCoinServiceBuy);
	psPacket->iHeader = PKTHDR_CoinServiceBuy;
	SENDPACKET(pcUser, psPacket, TRUE);
}
void CCoinShopHandle::ProcessPacket(User * pcUser, PacketCoinShopNPC * psPacket)
{
	psPacket->iLength = sizeof(PacketCoinShopNPC);
	psPacket->iHeader = PKTHDR_CoinShopNPC;
	SENDPACKET(pcUser, psPacket);
}
void CCoinShopHandle::ProcessPacket(User * pcUser, PacketCoinAmount * psPacket)
{
	psPacket->iLength = sizeof(PacketCoinAmount);
	psPacket->iHeader = PKTHDR_CoinShopAmount;
	SENDPACKET(pcUser, psPacket);
}
void CCoinShopHandle::ProcessPacket(User * pcUser, PacketCoinOpenTab * psPacket)
{
	psPacket->iLength = sizeof(PacketCoinOpenTab);
	psPacket->iHeader = PKTHDR_CoinShopOpenTab;
	SENDPACKET(pcUser, psPacket);
}
void CCoinShopHandle::ProcessPacket(User * pcUser, PacketCoinTab * psPacket)
{
	psPacket->iLength = sizeof(PacketCoinTab);
	psPacket->iHeader = PKTHDR_CoinShopTab;
	SENDPACKET(pcUser, psPacket);
}
void CCoinShopHandle::ProcessPacket(User * pcUser, PacketCoinItemData * psPacket)
{
	psPacket->iLength = sizeof(PacketCoinItemData);
	psPacket->iHeader = PKTHDR_CoinShopItemData;
	SENDPACKET(pcUser, psPacket);
}
void CCoinShopHandle::HandlePacket(User * pcUser, PacketCoinShopNPC * psPacket)
{
	if (psPacket->iLength != sizeof(PacketCoinShopNPC))
		return;

	if (GAME_SERVER)
		return;

	if (!pcUser->IsInGame())
		return;

	if (m_pcCoinShop == NULL)
		return;

	//Fill Packet

	psPacket->sPacketNumber = 0;
	psPacket->sPacketMax = (short)(m_pcCoinShop->GetTabs().size() / MAX_COINSHOPTABS) + 1;

	//ID
	psPacket->iID = m_pcCoinShop->GetID();

	//Message
	STRINGCOPY(psPacket->szName, m_pcCoinShop->GetName());
	STRINGCOPY(psPacket->szMessage, m_pcCoinShop->GetMessage());

	//Discount Percentile
	psPacket->iDiscount = m_pcCoinShop->GetDiscount();

	//Tabs
	psPacket->iTabs = 0;

	std::vector<CCoinShopTab*> & vTabs = m_pcCoinShop->GetTabs();
	for (std::vector<CCoinShopTab*>::iterator it = vTabs.begin(); it != vTabs.end(); it++)
	{
		CCoinShopTab * pcTab = *it;

		//Add Tab to the Packet
		int iTab = psPacket->iTabs;
		if (iTab >= MAX_COINSHOPTABS)
		{
			psPacket->sPacketNumber++;

			//Send Packet
			ProcessPacket(pcUser, psPacket);

			//Reset Packet
			iTab = psPacket->iTabs = 0;
		}

		if (iTab < MAX_COINSHOPTABS)
		{
			psPacket->aTabs[iTab].iID = pcTab->GetID();
			psPacket->aTabs[iTab].iParentTabID = pcTab->GetParentTabID();

			STRINGCOPY(psPacket->aTabs[iTab].szName, pcTab->GetName());

			psPacket->aTabs[iTab].iDiscount = pcTab->GetDiscount();
			psPacket->aTabs[iTab].iBulk = pcTab->GetBulk();
			psPacket->aTabs[iTab].iMaxBulk = pcTab->GetMaxBulk();

			psPacket->iTabs++;
		}

		//Add Child Tabs to the Packet
		std::vector<CCoinShopTab*> & vChildTabs = pcTab->GetChildTabs();
		for (std::vector<CCoinShopTab*>::iterator it = vChildTabs.begin(); it != vChildTabs.end(); it++)
		{
			CCoinShopTab * pcChildTab = *it;

			int iParentTab = psPacket->iTabs;
			if (iParentTab >= MAX_COINSHOPTABS)
			{
				psPacket->sPacketNumber++;

				//Send Packet
				ProcessPacket(pcUser, psPacket);

				//Reset Packet
				iParentTab = psPacket->iTabs = 0;
			}

			if (iParentTab < MAX_COINSHOPTABS)
			{
				psPacket->aTabs[iParentTab].iID = pcChildTab->GetID();
				psPacket->aTabs[iParentTab].iParentTabID = pcChildTab->GetParentTabID();

				STRINGCOPY(psPacket->aTabs[iParentTab].szName, pcChildTab->GetName());

				psPacket->aTabs[iParentTab].iDiscount = pcChildTab->GetDiscount();
				psPacket->aTabs[iParentTab].iBulk = pcChildTab->GetBulk();
				psPacket->aTabs[iParentTab].iMaxBulk = pcChildTab->GetMaxBulk();

				psPacket->iTabs++;
			}
		}
	}

	psPacket->sPacketNumber++;

	//Send Packet
	ProcessPacket(pcUser, psPacket);
}
void CCoinShopHandle::HandlePacket(User * pcUser, PacketCoinOpenTab * psPacket)
{
	if (psPacket->iLength != sizeof(PacketCoinOpenTab))
		return;

	if (GAME_SERVER)
		return;

	if (!pcUser->IsInGame())
		return;

	if (m_pcCoinShop == NULL)
		return;

	CCoinShopTab * pcTab = m_pcCoinShop->GetTabByID(psPacket->iID);

	if (pcTab == NULL)
	{
		psPacket->iReturnCode = -1;
		ProcessPacket(pcUser, psPacket);

		return;
	}

	PacketCoinTab sPacket;

	//Fill Packet

	sPacket.sPacketNumber = 0;
	sPacket.sPacketMax = (short)(pcTab->GetItems().size() / MAX_COINSHOPITEMS) + 1;

	//ID
	sPacket.iID = pcTab->GetID();

	//Items
	sPacket.iItems = 0;

	std::vector<CCoinShopItem*> & vItems = pcTab->GetItems();
	for (std::vector<CCoinShopItem*>::iterator it = vItems.begin(); it != vItems.end(); it++)
	{
		CCoinShopItem * pcItem = *it;

		//Add Item to the Packet
		int iItem = sPacket.iItems;
		if (iItem >= MAX_COINSHOPITEMS)
		{
			sPacket.sPacketNumber++;

			//Send Packet
			ProcessPacket(pcUser, &sPacket);

			//Reset
			iItem = sPacket.iItems = 0;
		}

		if (iItem < MAX_COINSHOPITEMS)
		{
			sPacket.aItems[iItem].iID = pcItem->GetID();
			STRINGCOPY(sPacket.aItems[iItem].szName, pcItem->GetName());
			STRINGCOPY(sPacket.aItems[iItem].szDescription, pcItem->GetDescription());
			STRINGCOPY(sPacket.aItems[iItem].szCode, pcItem->GetCode());
			STRINGCOPY(sPacket.aItems[iItem].szImage, pcItem->GetImage());
			sPacket.aItems[iItem].iValue = pcItem->GetValue();
			sPacket.aItems[iItem].iDiscount = pcItem->GetDiscount();
			sPacket.aItems[iItem].iBulk = pcItem->GetBulk();
			sPacket.aItems[iItem].iMaxBulk = pcItem->GetMaxBulk();

			sPacket.iItems++;
		}
	}

	sPacket.sPacketNumber++;

	//Send Packet
	ProcessPacket(pcUser, &sPacket);
}

void CCoinShopHandle::HandlePacket(User * pcUser, PacketCoinAmount * psPacket)
{
	psPacket->iCoinAmount = GetCoinAmount(pcUser->szAccountName);
	ProcessPacket(pcUser, psPacket);
}

void CCoinShopHandle::HandlePacket(User * pcUser, PacketCoinOpenItemData * psPacket)
{
	CCoinShopTab * pcTab = m_pcCoinShop->GetTabByID(psPacket->iTabID);
	if (pcTab)
	{
		CCoinShopItem * pcItem = pcTab->GetItemByID(psPacket->iID);

		if (pcItem)
		{
			int iPrice = pcItem->GetDiscount() > 0 ? pcItem->GetDiscount() : pcItem->GetValue();

			//Perfectize?
			if (STRINGCOMPAREI(pcItem->GetCode(), "Perf"))
			{
				PacketCoinOpenService s;
				s.iLength = sizeof(PacketCoinOpenService);
				s.iHeader = PKTHDR_CoinServiceOpen;
				s.iID = ITEMCOIN_ItemPerfect;
				s.iPrice = iPrice;
				SENDPACKET(pcUser, &s, TRUE);
				return;
			}

			//Swap?
			if (STRINGCOMPAREI(pcItem->GetCode(), "Swap"))
			{
				PacketCoinOpenService s;
				s.iLength = sizeof(PacketCoinOpenService);
				s.iHeader = PKTHDR_CoinServiceOpen;
				s.iID = ITEMCOIN_ItemSwapper;
				s.iPrice = iPrice;
				SENDPACKET(pcUser, &s, TRUE);
				return;
			}

			//ChangeNick?
			if (STRINGCOMPAREI(pcItem->GetCode(), "CNick"))
			{
				PacketCoinOpenService s;
				s.iLength = sizeof(PacketCoinOpenService);
				s.iHeader = PKTHDR_CoinServiceOpen;
				s.iID = ITEMCOIN_ChangeNick;
				s.iPrice = iPrice;
				m_iChangeNickPrice = iPrice;
				SENDPACKET(pcUser, &s, TRUE);
				return;
			}

			//Aging Recovery?
			if (STRINGCOMPAREI(pcItem->GetCode(), "AgeRec"))
			{
				PacketOpenAgingRecoveryService s;
				s.iLength = sizeof(PacketOpenAgingRecoveryService);
				s.iHeader = PKTHDR_CoinServiceAgingRecoveryOpen;
				s.iPrice = iPrice;
				m_iAgingRecoveryPrice = iPrice;

				std::vector<AgingRecoveryDataHandle> vData = AGEHANDLE->SQLGetBrokeItems(pcUser->szAccountName);

				s.iCount = 0;
				s.sPacketNumber = 0;
				s.sPacketMax = (short)(vData.size() / MAX_AGINGRECOVERY_PER_PACKET) + 1;

				for (UINT i = 0; i < vData.size(); i++)
				{
					CopyMemory(&s.saData[s.iCount], &vData[i], sizeof(AgingRecoveryDataHandle));
					s.iCount++;

					if (s.iCount >= MAX_AGINGRECOVERY_PER_PACKET)
					{
						s.sPacketNumber++;

						SENDPACKET(pcUser, &s, TRUE);

						s.iCount = 0;
					}
				}

				s.sPacketNumber++;

				SENDPACKET(pcUser, &s, TRUE);

				return;
			}

			//Change Class?
			if (STRINGCOMPAREI(pcItem->GetCode(), "CClass"))
			{
				PacketCoinOpenService s;
				s.iLength = sizeof(PacketCoinOpenService);
				s.iHeader = PKTHDR_CoinServiceOpen;
				s.iID = ITEMCOIN_ChangeClass;
				s.iPrice = iPrice;
				SENDPACKET(pcUser, &s, TRUE);
				return;
			}

			PacketCoinItemData sPacket;
			sPacket.iID = psPacket->iID;
			sPacket.iTabID = psPacket->iTabID;
			sPacket.iType = ITEMCOIN_Normal;

			// Find Item Data by Code
			DefinitionItem * psItemDef = SERVERITEM->FindItemDefByCode(pcItem->GetCode());
			if (psItemDef)
			{
				// Create Item Data
				CopyMemory(&sPacket.sItemDefinition, psItemDef, sizeof(DefinitionItem));
				sPacket.iType = ITEMCOIN_Data;
			}

			sPacket.bSpec = pcItem->GetIsSpec();
			sPacket.bQuantity = pcItem->GetIsQuantity();

			ProcessPacket(pcUser, &sPacket);
		}
	}
}

void CCoinShopHandle::HandlePacket(User * pcUser, struct PacketCoinBuy * psPacket)
{
	PacketCoinAmount sPacketCoinAmount;
	CCoinShopTab * pcTab = m_pcCoinShop->GetTabByID(psPacket->iTabID);
	psPacket->iReturnCode = 0;
	if (pcTab)
	{
		CCoinShopItem * pcItem = pcTab->GetItemByID(psPacket->iID);
		if (pcItem)
		{
			int iValue = pcItem->GetDiscount() > 0 ? pcItem->GetDiscount() : pcItem->GetValue();

			if (pcItem->GetIsQuantity())
			{
				if (psPacket->iParam2 <= 0)
					psPacket->iParam2 = 1;

				int iBulk = GetBulkValue(pcItem, psPacket->iParam2);

				if (HasCoinAmount(pcUser->szAccountName, (iValue * psPacket->iParam2) - iBulk))
				{
					DISTRIBUTORHANDLE->AddItemOpenBox(pcUser, pcItem->GetCode(), pcItem->GetIsSpec() == TRUE ? psPacket->iParam1 : 0, psPacket->iParam2);
					sPacketCoinAmount.iCoinAmount = UseCoin(pcUser->szAccountName, (iValue * psPacket->iParam2) - iBulk);
					// Log
					SQLCoinLog(pcUser->szAccountName, (char*)FormatString("AccountName[%s] Bought[%s] Spec[%d] Quantity[%d] Price[%d] CoinAmount[%d]",
						pcUser->szAccountName, pcItem->GetCode(), pcItem->GetIsSpec() == TRUE ? psPacket->iParam1 : 0,
						psPacket->iParam2, (iValue * psPacket->iParam2) - iBulk, sPacketCoinAmount.iCoinAmount));


					psPacket->iReturnCode = 1;
				}
			}
			else
			{
				if (HasCoinAmount(pcUser->szAccountName, iValue))
				{
					DISTRIBUTORHANDLE->AddItemOpenBox(pcUser, pcItem->GetCode(), pcItem->GetIsSpec() == TRUE ? psPacket->iParam1 : 0);
					sPacketCoinAmount.iCoinAmount = UseCoin(pcUser->szAccountName, iValue);

					// Log
					SQLCoinLog(pcUser->szAccountName, (char*)FormatString("AccountName[%s] Bought[%s] Spec[%d] Price[%d] CoinAmount[%d]",
						pcUser->szAccountName, pcItem->GetCode(), pcItem->GetIsSpec() == TRUE ? psPacket->iParam1 : 0,
						iValue, sPacketCoinAmount.iCoinAmount));


					psPacket->iReturnCode = 1;
				}
			}
		}
		else
			psPacket->iReturnCode = -2;
	}
	else
		psPacket->iReturnCode = -1;

	SENDPACKET(pcUser, psPacket);

	// Coin Amount
	if (psPacket->iReturnCode == 1)
		ProcessPacket(pcUser, &sPacketCoinAmount);

}

void CCoinShopHandle::HandlePacket(User * pcUser, PacketCoinServiceBuy * psPacket)
{
	if (pcUser)
	{
		switch (psPacket->iType)
		{
		case ITEMCOIN_ItemSwapper:
			ItemSwapper(pcUser, psPacket);
			break;
		case ITEMCOIN_ItemPerfect:
			PerfectizeItem(pcUser, psPacket);
			break;
		case ITEMCOIN_ChangeNick:
			ChangeNick(pcUser, psPacket);
			break;
		case ITEMCOIN_AgingRecovery:
			AgingRecovery(pcUser, psPacket);
			break;
		case ITEMCOIN_ChangeClass:
			ChangeClass(pcUser, psPacket);
			break;
		default:
			break;
		}

		//Update Coins
		ProcessPacket(pcUser, &PacketCoinAmount(GetCoinAmount(pcUser->szAccountName)));
	}
}

void CCoinShopHandle::HandlePacket(User * pcUser, PacketTradeCoinSet * psPacket)
{
	if (psPacket->iCoins >= 0)
	{
		if (HasCoinAmount(pcUser->szAccountName, psPacket->iCoins))
		{
			pcUser->iTradeCoin = psPacket->iCoins;

			User * pcPartner = SERVERUSER->GetUser(psPacket->iID);

			if (pcPartner)
				SENDPACKET(pcPartner, psPacket);
		}
	}
}