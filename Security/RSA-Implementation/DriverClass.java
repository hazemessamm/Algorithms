import java.util.Scanner;

public class DriverClass {
    public static void main(String[] args) throws ClassNotFoundException {
        Scanner scan = new Scanner(System.in);
        String message = scan.next();
        int e = scan.nextInt();
        int p = scan.nextInt();
        int q = scan.nextInt();

        EncryptionDriver encryptionDriver = new EncryptionDriver(message.length(), p, q, e);
        System.out.println(encryptionDriver.encrypt());
        System.out.println(encryptionDriver.decrypt());
        System.out.println("GCD between phi(n) and E is " + encryptionDriver.check_gcd());
        System.out.println("E Criteria is " + encryptionDriver.check_e_criteria());
        System.out.println("Correctness of the decryption is " + encryptionDriver.check_correctness_of_decryption());
    }
}
