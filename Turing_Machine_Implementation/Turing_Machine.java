package turing.machine;
import java.util.Scanner;

public class TuringMachine {

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int state = 0, alpha = 0;
        System.out.println("Enter Number of states");
        state = scan.nextInt();
        System.out.println("Enter states");
        String []states = new String[state];
        for(int i = 0; i < state; i++)
        {
            states[i] = scan.next();
        }
        System.out.println("Enter Number of alphabets");
        alpha = scan.nextInt();
        String []alphas = new String[alpha];
        System.out.println("Enter alphabets");
         for(int i = 0; i < alpha; i++)
        {
            alphas[i] = scan.next();
        }
        System.out.println("Enter Number of transitions");
        int numTrans = scan.nextInt();
        System.out.println("Enter Transitions");
        String [][]trans = new String[numTrans][5];
        for(int i = 0; i < numTrans; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                trans[i][j] = scan.next();
            }
        }
        System.out.println("Enter Length of string");
        int length = 0;
        length = scan.nextInt();
        length *= 2;
        String []s = new String[length];
        System.out.println("Enter String");
        for (int i = 0; i < length/2; i++)
        {
            s[i] = scan.next();
        }
        for (int i = 0; i < length; i++)
        {
            if(s[i] == null)
            {
                s[i] = "e";
            }
        }
        //Inputs order: Current Node -> Read -> next node -> update -> direction
        int j = 0,head=0;
        String currentState = trans[0][0];
        for(j = 0; j<numTrans; j++)
        {
            if(s[head].equalsIgnoreCase(trans[j][1]) && currentState.equalsIgnoreCase(trans[j][0]))
            {
                s[head] = trans[j][3];
                currentState = trans[j][2];
                if(trans[j][4].equalsIgnoreCase("r"))
                {
                    if(head == s.length-1)
                    {
                        head = head;
                    }
                    else
                    {
                        head++;
                    }
                }
                else
                {
                    if(trans[j][4].equalsIgnoreCase("l") && head == 0)
                    {
                        head = 0;
                    }
                    else
                    {
                        head--;
                    }
                }
                if(trans[j][2].equalsIgnoreCase("qaccept"))
                {
                    System.out.println("Accepted");
                    break;
                }
                else if(trans[j][2].equalsIgnoreCase("qreject"))
                {
                    System.out.println("Rejected");
                    break;
                }
            }
        }
        for(int i = 0; i < length; i++)
        {
            System.out.println(s[i]);
        }
}
}
