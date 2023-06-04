import java.io.*;
import java.util.*;

class Node 
{
    String name, address;
    int pin, balance = 0, transactionLimit = 10000;
    long accountNumber, aadharNumber, phoneNumber;
}

class Bank extends Node
{
    Scanner scanner = new Scanner(System.in);

    List<Node> nodes = new ArrayList<>();

    void lobby() {
        System.out.println("Welcome to Demo Bank of India");
        System.out.println("--------------------");
        System.out.println("1. Create an Account");
        System.out.println("2. Login");
        System.out.println("3. Admin Login");
        System.out.println("4. Exit");

        System.out.print("Enter your choice: ");
        int choice = scanner.nextInt();

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                long accountNumber = login();
                if (accountNumber != 0) {
                    userMenu(accountNumber);
                }
                break;
            case 3:
                adminLogin();
                break;
            case 4:
                System.out.println("Thank you for using XYZ Bank. Goodbye!");
                System.exit(0);
                break;
            default:
                System.out.println("Invalid choice. Please try again.");
                lobby();
                break;
        }
    }

    void createAccount() {
        Node newNode = new Node();

        System.out.println("Account Creation");
        System.out.println("----------------");

        scanner.nextLine(); // Consume the remaining newline character

        System.out.print("Enter your name: ");
        newNode.name = scanner.nextLine();

        System.out.print("Enter your address: ");
        newNode.address = scanner.nextLine();

        System.out.print("Enter your 6-digit PIN: ");
        newNode.pin = scanner.nextInt();

        System.out.print("Enter your 12-digit Aadhar number: ");
        newNode.aadharNumber = scanner.nextLong();

        System.out.print("Enter your 10-digit phone number: ");
        newNode.phoneNumber = scanner.nextLong();

        newNode.accountNumber = findLastAccountNumber() + 1;

        nodes.add(newNode);

        System.out.println("Account created successfully.");
        System.out.println("Your account number is: " + newNode.accountNumber);

        lobby();
    }

    void deposit(long accountNumber) {
        int amount;

        System.out.print("Enter the amount to deposit: ");
        amount = scanner.nextInt();

        for (Node node : nodes) {
            if (node.accountNumber == accountNumber) {
                node.balance += amount;
                System.out.println("Deposit successful. Current balance: " + node.balance);
                saveTransactionHistory(accountNumber, accountNumber, "Deposit", node.name, amount, node.balance);
                break;
            }
        }

        userMenu(accountNumber);
    }

    void withdraw(long accountNumber) {
        int amount;

        System.out.print("Enter the amount to withdraw: ");
        amount = scanner.nextInt();

        for (Node node : nodes) {
            if (node.accountNumber == accountNumber) {
                if (node.balance >= amount && amount <= node.transactionLimit) {
                    node.balance -= amount;
                    System.out.println("Withdrawal successful. Current balance: " + node.balance);
                    saveTransactionHistory(accountNumber, accountNumber, "Withdrawal", node.name, amount, node.balance);
                } else {
                    System.out.println("Insufficient balance or transaction limit exceeded.");
                }
                break;
            }
        }

        userMenu(accountNumber);
    }

    long login() {
        long accountNumber;

        System.out.print("Enter your account number: ");
        accountNumber = scanner.nextLong();

        if (findAccount(accountNumber)) {
            return accountNumber;
        } else {
            System.out.println("Invalid account number. Please try again.");
            return 0;
        }
    }

    void userMenu(long accountNumber) {
        System.out.println("User Menu");
        System.out.println("---------");
        System.out.println("1. Deposit");
        System.out.println("2. Withdraw");
        System.out.println("3. Check Balance");
        System.out.println("4. View Transaction History");
        System.out.println("5. Logout");

        System.out.print("Enter your choice: ");
        int choice = scanner.nextInt();

        switch (choice) {
            case 1:
                deposit(accountNumber);
                break;
            case 2:
                withdraw(accountNumber);
                break;
            case 3:
                checkBalance(accountNumber);
                break;
            case 4:
                viewTransactionHistory(accountNumber);
                break;
            case 5:
                System.out.println("Logged out successfully.");
                lobby();
                break;
            default:
                System.out.println("Invalid choice. Please try again.");
                userMenu(accountNumber);
                break;
        }
    }

    void checkBalance(long accountNumber) {
        for (Node node : nodes) {
            if (node.accountNumber == accountNumber) {
                System.out.println("Your current balance is: " + node.balance);
                break;
            }
        }

        userMenu(accountNumber);
    }

    void viewTransactionHistory(long accountNumber) {
        System.out.println("Transaction History");
        System.out.println("-------------------");

        for (Node node : nodes) {
            if (node.accountNumber == accountNumber) {
                try {
                    File file = new File("transaction_history_" + accountNumber + ".txt");
                    Scanner fileReader = new Scanner(file);

                    while (fileReader.hasNextLine()) {
                        String data = fileReader.nextLine();
                        System.out.println(data);
                    }

                    fileReader.close();
                } catch (FileNotFoundException e) {
                    System.out.println("Transaction history not found.");
                }
                break;
            }
        }

        userMenu(accountNumber);
    }

    long findLastAccountNumber() {
        long lastAccountNumber = 0;

        for (Node node : nodes) {
            if (node.accountNumber > lastAccountNumber) {
                lastAccountNumber = node.accountNumber;
            }
        }

        return lastAccountNumber;
    }

    boolean findAccount(long accountNumber) {
        for (Node node : nodes) {
            if (node.accountNumber == accountNumber) {
                return true;
            }
        }
        return false;
    }

    void saveTransactionHistory(long senderAccountNumber, long receiverAccountNumber, String transactionType,
            String name, int amount, int balance) {
        try {
            FileWriter fileWriter = new FileWriter("transaction_history_" + senderAccountNumber + ".txt", true);
            PrintWriter printWriter = new PrintWriter(fileWriter);

            printWriter.println("Transaction Type: " + transactionType);
            printWriter.println("Account Number: " + senderAccountNumber);
            printWriter.println("Recipient Account Number: " + receiverAccountNumber);
            printWriter.println("Name: " + name);
            printWriter.println("Amount: " + amount);
            printWriter.println("Balance: " + balance);
            printWriter.println();

            printWriter.close();
        } catch (IOException e) {
            System.out.println("An error occurred while saving the transaction history.");
        }
    }

    void adminLogin() {
        int adminPIN;

        System.out.print("Enter the admin PIN: ");
        adminPIN = scanner.nextInt();

        // TODO: Implement admin login functionality

        lobby();
    }

    public static void main(String[] args) 
    {
        Bank bank = new Bank();
        bank.lobby();
    }
}
