#include <iostream>
#include <string>
#include <ctype.h>
#include <string.h>

using namespace std;
int continumax(char ** outputStr, char * inputStr)
{
	char last = 0;
	char * startStr = inputStr;
	char * maxStr;
	int count = 0;
	int maxCount = 0;
	while(*inputStr != '\0')
	{
		if(isdigit(*inputStr))
		{
			if(!isdigit(last) || *inputStr != (last+1))
			{
				if(count > maxCount)
				{
					maxStr = startStr;
					maxCount = count;
				}
				startStr = inputStr;
				count = 1;
			}
			else
			{
				count++;
			}
		}
		else if(isdigit(last))
		{
			if(count > maxCount)
                        {
                                maxStr = startStr;
                                maxCount = count;
                        }

		}

		last= *inputStr;
		inputStr++;
	}

	if(count > maxCount)
        {
                maxStr = startStr;
                maxCount = count;
        }
	*outputStr = maxStr;
	return maxCount;
}

int main(void)
{
	const	char * c_str = "abcd12345ed125ss123456789";
	char * str = new char [128];
	char * output = NULL;
	strcpy(str, c_str);
	cout << continumax(&output, str)<<endl;

	cout << strlen(output)<<endl;
	delete [] str;
	return 0;
}
