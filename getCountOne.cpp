
int getCountOne(int num)
{
        int count = 0;
        int x = 1;
        int y = 10; //y = 10 * x
        do
        {
                int high = num / y;
                int low = num % y;
                count += high * x;
                if((num/x)%10 == 1)
                {
                        count += num%x + 1;
                }
                else if((num/x)%10 > 1)
                {
                        count += x;
                }
                x = y;
                y = x * 10;
        }while(num/x != 0);

        return count;
}
