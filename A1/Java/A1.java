import java.util.*;

public class A1{

	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);

		System.out.println("Enter your test string");
		String s1 = input.nextLine();


		System.out.println("\nEnter another string and I'll tell you if it's inside your first string");
		String s2 = input.next();

		if (s1.contains(s2)) {
			System.out.println("FOUND");
		}
		else {
			System.out.println("NOT FOUND");
		}
	}

}
