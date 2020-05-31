
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintStream;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

public class BankDriver {
 
	public static void main(String[] args) throws FileNotFoundException, InterruptedException {
		 // feel free to create a different file with smaller/larger number of records
		 // create a file with random records 
	   createAccountsFile(1000000);
		 System.out.println("File Was Created!");
		 
		ArrayList<Customer> custList = new ArrayList<Customer>();
		// reading the info from the file and storing in the arrayList
		long currentRec=0;
		System.out.println("Reading the file \"accounts.txt\" ");
		Scanner inFile = new Scanner(new File("accounts.txt")); 
		while (inFile.hasNext()) { // while 2
			String currID = inFile.nextLine();
			double currBalance = inFile.nextDouble();
			if (inFile.hasNextLine())
				inFile.nextLine(); // dummy reading
			custList.add(new Customer(currID, currBalance));
			if (++currentRec % 30000==0)
				System.out.print(">>");
			if (currentRec % 1000000==0)
				System.out.println( );
			
		} // end of while 2

		// Counting the balances that are less than 1000$
		int lowBalances = 0;
		// --Sequential-Run--------------------------------------------------------------
		long startTime = System.currentTimeMillis();
		lowBalances = sequentialCounting(custList); // sequential run
		long estimatedTime = System.currentTimeMillis() - startTime;
		System.out.println("Number of accounts with less than 1000$ is: " + lowBalances);
		System.out.println("Sequential run took in miliseconds: " + estimatedTime);
		// --End of Sequential-Run--------------------------------------------------------
		// *******************************************************************************
		// --Parallel Run-----------------------------------------------------------------
		startTime = System.currentTimeMillis();
		int workload = custList.size() / 4;
		int sec1 = workload;
		int sec2 = workload * 2;
		int sec3 = workload * 3;
		int sec4 = custList.size();
		
		int[] array = {0, 0, 0, 0};
		
		Extended R0 = new Extended(custList, 0, sec1, 0, array);
		Extended R1 = new Extended(custList, sec1+1, sec2, 1, array);
		Extended R2 = new Extended(custList, sec2+1, sec3, 2, array);
		Extended R3 = new Extended(custList, sec3+1, sec4, 3, array);
		
		Thread th0 = new Thread(R0);
		Thread th1 = new Thread(R1);
		Thread th2 = new Thread(R2);
		Thread th3 = new Thread(R3);
		
		
		th0.start(); th1.start(); th2.start(); th3.start();
		th0.join(); th1.join(); th2.join(); th3.join();

		estimatedTime = System.currentTimeMillis() - startTime;
		R0.getTotal();
    System.out.println("Parallel run took in miliseconds: " + estimatedTime);
		// --End-of-Parallel-Run----------------------------------------------------------

	}// end of main

	static int sequentialCounting(ArrayList<Customer> myList) {
		int count = 0;
		for (int i = 0; i < myList.size(); ++i)
			if (myList.get(i).getBalance() < 1000)
				++count;
		return count;
	};

	static void createAccountsFile(int count) throws FileNotFoundException {
		File accountsFile = new File("accounts.txt");
		PrintStream outFile = new PrintStream(accountsFile);
		Random rand = new Random();
		// needed for making sure that there is no duplication in the IDs
		// ArrayList<String> tmpIDs = new ArrayList<String>();

		// generating random records IDs from XXXX0 to XXXX300000000 (non-repeating) and
		// balances 0 to 1000000
		for (int i = 0; i < count; ++i) { 
			int tempId;
			tempId = rand.nextInt(300000001);
			// try to generate a random ID with 3 random letters and a number from 0 to
			// 300000000
			String currentID = "" + ((char) ('A' + rand.nextInt(25))) + ((char) ('A' + rand.nextInt(25)))
					+ ((char) ('A' + rand.nextInt(25))) + tempId + ((char) ('A' + rand.nextInt(25)))
					+ ((char) ('A' + rand.nextInt(25))) + ((char) ('A' + rand.nextInt(25)));
			// if (tmpIDs.contains(currentID) == false) {
			// tmpIDs.add(currentID); // insert to the array list in location i
			outFile.println(currentID); // send to file
			// }
			outFile.println(rand.nextInt(1000001) / 100.0); // send to file
		}
		outFile.close();
	}

}

class Extended extends Thread {
  private int start, end;
  private ArrayList<Customer> myList;
  private int pos;
  private int[] array;
  
  Extended(ArrayList<Customer> myList, int start, int end, int pos, int[] array) {
    this.start = start;
    this.end = end;
    this.myList = myList;
    this.pos = pos;
    this.array = array;
  }
  public void run() {
	  int count = 0;
    for (int i = start; i < end; ++i) {
      if (myList.get(i).getBalance() < 1000)
        ++count;
      
    }
    
    array[pos] = count;
  }
 
  public void getTotal() {
	  int total = 0;
	  for (int i = 0; i < array.length; ++i) {
		  System.out.println("array[" + i + "]: " + array[i]);
		  total += array[i];
	  }
	  System.out.println("Number of accounts with less than 1000$ is: " + total);
  }
}
