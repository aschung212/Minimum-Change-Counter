#include <stdlib.h>
#include <assert.h>
//#include <iostream>	//included for testing purposes.

/// <summary>
/// Facilitates dispensing stamps for a postage stamp machine.
/// </summary>
class StampDispenser
{
public:
					/// <summary>
					/// Initializes a new instance of the <see cref="StampDispenser"/> class that will be 
					/// able to dispense the given types of stamps.
					/// </summary>
					/// <param name="stampDenominations">
					/// The values of the types of stamps that the machine has.  
					/// Should be sorted in descending order and contain at least a 1.
					/// </param>
					/// <param name="numStampDenominations">
					/// The number of types of stamps in the stampDenominations array. 
					/// </param>
    StampDispenser(const int* stampDenominations, size_t numStampDenominations)
	{
		m_stampDenominations = stampDenominations;
		m_numStampDenominations = numStampDenominations;
	}
    
					/// <summary>
					/// Returns the minimum number of stamps that the machine can dispense to
					/// fill the given request.
					/// </summary>
					/// <param name="request">
					/// The total value of the stamps to be dispensed.
					/// </param>
					/// <returns>
					/// The minimum number of stamps needed to fill the given request.
					/// </returns>
    int CalcNumStampsToFillRequest(int request)
	{
		//if our only stamp denomination is 1, then it will take (request) number of stamps to fulfill the request
		if (m_stampDenominations[0] == 1){
			return request;
		}

		//if we have a stamp that satisfies the request by itself, then we should use that stamp
		else if (request == m_stampDenominations[0]){
			return 1;
		}

		StampDispenser temp(&m_stampDenominations[1], m_numStampDenominations-1);
		int usesStamp;
		int skipsStamp;

		//if current stamp is too large, we know we can skip it.
		if (m_stampDenominations[0] > request)
			return temp.CalcNumStampsToFillRequest(request);

		/*if the current largest stamp is used in the optimal solution, then we
		can look for the number of stamps required for the remaining portion of
		the request. The total number of stamps will be the number required for the
		remaining portion plus the one used in this step
		*/
		usesStamp = (CalcNumStampsToFillRequest(request - m_stampDenominations[0]) + 1);
		skipsStamp = temp.CalcNumStampsToFillRequest(request);

		if (usesStamp < skipsStamp){
			return usesStamp;
		}


		else
			return skipsStamp;
	}

private:
	const int* m_stampDenominations;
	size_t m_numStampDenominations;
}; 

int main()
{
    int stampDenominations[] = {90, 30, 24, 10, 6, 2, 1};
    StampDispenser stampDispenser(stampDenominations, 7);
    assert(stampDispenser.CalcNumStampsToFillRequest(18) == 3);
	
	
	//TESTS
	/*
	if (stampDispenser.CalcNumStampsToFillRequest(18) == 3)
		cout << "code is working for 18" << endl;
	if (stampDispenser.CalcNumStampsToFillRequest(92) == 2)
		cout << "code is working for 92" << endl;
	if (stampDispenser.CalcNumStampsToFillRequest(131) == 4)
		cout << "code is working for 131" << endl;
	if (stampDispenser.CalcNumStampsToFillRequest(1) == 1)
		cout << "code is working for 1" << endl;
	if (stampDispenser.CalcNumStampsToFillRequest(24) == 1)
		cout << "code is working for 24" << endl;
	if (stampDispenser.CalcNumStampsToFillRequest(540) == 6)
		cout << "code is working for 540" << endl;
	cout << "When requesting 0, my function returns " << stampDispenser.CalcNumStampsToFillRequest(0) << endl;
	cout << "When requesting -1, my function returns " << stampDispenser.CalcNumStampsToFillRequest(-1) << endl;
	cout << "When requesting -100, my function returns " << stampDispenser.CalcNumStampsToFillRequest(-100) << endl;


	//TESTS WITH DIFFERENT STAMPDENOMINATIONS
	int coins[] = {25, 10, 5, 1};
	StampDispenser coinDispenser(coins, 4);

	if (coinDispenser.CalcNumStampsToFillRequest(1) == 1)
		cout << "coin dispenser works for 1" << endl;
	if (coinDispenser.CalcNumStampsToFillRequest(-1) == -1)
		cout << "coin dispenser works for -1" << endl;
	if (coinDispenser.CalcNumStampsToFillRequest(0) == 0)
		cout << "coin dispenser works for 0" << endl;
	if (coinDispenser.CalcNumStampsToFillRequest(4) == 4)
		cout << "coin dispenser works for 4" << endl;
	if (coinDispenser.CalcNumStampsToFillRequest(9) == 5)
		cout << "coin dispenser works for 9" << endl;
	if (coinDispenser.CalcNumStampsToFillRequest(10) == 1)
		cout << "coin dispenser works for 10" << endl;
	if (coinDispenser.CalcNumStampsToFillRequest(100) == 4)
		cout << "coin dispenser works for 100" << endl;
	if (coinDispenser.CalcNumStampsToFillRequest(97) == 7)
		cout << "The least number of coins to make 97 cents is 7 coins" << endl;
	else
		cout << "The least number of coins to make 97 cents is not 7 coins" << endl;
		*/
    return 0;
}
