import java.util.Scanner;
import java.lang.*;

class Ertischek{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);

        int run = 1;

        int pages[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

        int pageAvailible = 16;

        int fifo = 1;

        while(run == 1)
        {
            String nums = input.nextLine();

            int jobNum;
            int bytes;

            if(nums.equals(new String("exit")) == true)
            {
                return;
            }
            else if(nums.equals(new String("print")) == true)
            {
                for(int a = 0; a < 16; a++)
                {
                    System.out.println("Frame " + (a+1) + " is assigned to job: " + pages[a]);
                }
            }
            else
            {
                String[] split = nums.split(" ");
                jobNum = Integer.parseInt(split[0]);
                bytes = Integer.parseInt(split[1]);

                int pageneed = (int)Math.ceil(bytes/4096.0);

                if(bytes == 0)
                {
                    for(int d = 0; d < 16; d++)
                    {
                        if(pages[d] == jobNum)
                        {
                            pages[d] = 0;
                            pageAvailible++;
                        }
                    }
                }
                else if(pageAvailible < pageneed)
                {
                    for(int d = 0; d < 16; d++)
                    {
                        if(pages[d] == fifo)
                        {
                            pages[d] = 0;
                            pageAvailible++;
                        }
                    }
                    fifo++;

                    for(int x = 0; x < 16; x++)
                    {
                        int count = 0;
                        for(int y = pageneed; y > 0; y--)
                        {
                            if(pages[x] != 0)
                            {
                                break;
                            }
                            else
                            {
                                count++;

                                if(count == pageneed)
                                {
                                    break;
                                }
                            }
                        }
                        if(count == pageneed)
                        {
                            for(int z = 0; z < count; z++)
                            {
                                pages[x+z] = jobNum;
                                pageAvailible--;
                            }
                            break;
                        }
                    }
                }
                else if(pageAvailible >= pageneed)
                {
                    for(int x = 0; x < 16; x++)
                    {
                        int count = 0;
                        int nc = 0;
                        for(int y = pageneed; y > 0; y--)
                        {
                            if(pages[x] != 0)
                            {
                                count = 0;
                                break;
                            }
                            else
                            {
                                count++;

                                if(count == pageneed)
                                {
                                    for(int g = 0; g < count; g++)
                                    {
                                        if(pages[x+g] != 0)
                                        {
                                            nc = 1;
                                        }
                                    }
                                    break;
                                }
                            }
                        }
                        if(nc == 0 && count == pageneed)
                        {
                            for(int z = 0; z < count; z++)
                            {
                                pages[x+z] = jobNum;
                                pageAvailible--;
                            }
                            break;
                        }
                        else if(nc == 1)
                        {
                            for(int f = 0; f < pageneed; f++)
                            {
                                for(int d = 0; d < 16; d++)
                                {
                                    if(pages[d] == fifo)
                                    {
                                        pages[d] = 0;
                                        pageAvailible++;
                                    }
                                }

                                for(int s = 0; s < 16; s++)
                                {
                                    int count2 = 0;
                                    for(int y = pageneed; y > 0; y--)
                                    {
                                        if(pages[s] != 0)
                                        {
                                            break;
                                        }
                                        else
                                        {
                                            count2++;

                                            if(count2 == pageneed)
                                            {
                                                break;
                                            }
                                        }
                                    }
                                    for(int q = 0; q < count; q++)
                                    {
                                        pages[s+q] = jobNum;
                                        pageAvailible--;
                                    }
                                    break;
                                }
                            }
                            fifo++;
                            break;
                        }
                    }
                }
            }
        }
    }
}